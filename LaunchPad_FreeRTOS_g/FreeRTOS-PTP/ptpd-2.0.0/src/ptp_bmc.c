#include "ptp_bmc.h"
#include "ptp_protocol.h"

ForeignMasterRecord ptpForeignRecords[DEFAULT_MAX_FOREIGN_RECORDS];

#define A_better_then_B               1
#define B_better_then_A              -1
#define A_better_by_topology_then_B   1
#define B_better_by_topology_then_A  -1
#define ERROR_1                       0
#define ERROR_2                      -0


#define COMPARE_AB_RETURN_BETTER(cond, msg)                                     \
    if ((announceA->cond) > (announceB->cond)) {                                \
        return B_better_then_A;                                                 \
    }                                                                           \
    if ((announceB->cond) > (announceA->cond)) {                                \
        return A_better_then_B;                                                 \
    }                                                                           \


void EUI48toEUI64(const char * eui48, char * eui64)
{
    eui64[0] = eui48[0];
    eui64[1] = eui48[1];
    eui64[2] = eui48[2];
    eui64[3] = 0xff;
    eui64[4] = 0xfe;
    eui64[5] = eui48[3];
    eui64[6] = eui48[4];
    eui64[7] = eui48[5];
}

bool isSamePortIdentity(const PortIdentity * A, const PortIdentity * B)
{
    if(0 == memcmp(A->clockIdentity, B->clockIdentity, CLOCK_IDENTITY_LENGTH)
            && (A->portNumber == B->portNumber))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void copyD0(MsgHeader *header, MsgAnnounce *announce, PtpClock *ptpClock)
{
    announce->grandmasterPriority1 = ptpClock->portDS.priority1;
    memcpy(announce->grandmasterIdentity, ptpClock->portDS.clockIdentity, CLOCK_IDENTITY_LENGTH);
    announce->grandmasterClockQuality.clockClass = ptpClock->portDS.clockQuality.clockClass;
    announce->grandmasterClockQuality.clockAccuracy = ptpClock->portDS.clockQuality.clockAccuracy;
    announce->grandmasterClockQuality.offsetScaledLogVariance = ptpClock->portDS.clockQuality.offsetScaledLogVariance;
    announce->grandmasterPriority2 = ptpClock->portDS.priority2;
    announce->stepsRemoved = 0;
    memcpy(header->sourcePortIdentity.clockIdentity, ptpClock->portDS.clockIdentity, CLOCK_IDENTITY_LENGTH);
}

/* Local clock is synchronized to Ebest Table 16 (9.3.5) of the spec */
void s1(PtpClock *ptpClock, const MsgHeader *header, const MsgAnnounce *announce)
{
    bool isFromCurrentParent;

    ptpClock->portDS.stepsRemoved = announce->stepsRemoved + 1;

    isFromCurrentParent = isSamePortIdentity(&ptpClock->parentDS.parentPortIdentity, &header->sourcePortIdentity);

    if (!isFromCurrentParent)
    {
        setFlag(ptpClock->events, MASTER_CLOCK_CHANGED);
    }

    /* Parent DS */
    memcpy(ptpClock->parentDS.parentPortIdentity.clockIdentity, header->sourcePortIdentity.clockIdentity, CLOCK_IDENTITY_LENGTH);
    ptpClock->parentDS.parentPortIdentity.portNumber = header->sourcePortIdentity.portNumber;
    memcpy(ptpClock->parentDS.grandmasterIdentity, announce->grandmasterIdentity, CLOCK_IDENTITY_LENGTH);
    ptpClock->parentDS.grandmasterClockQuality.clockAccuracy = announce->grandmasterClockQuality.clockAccuracy;
    ptpClock->parentDS.grandmasterClockQuality.clockClass = announce->grandmasterClockQuality.clockClass;
    ptpClock->parentDS.grandmasterClockQuality.offsetScaledLogVariance = announce->grandmasterClockQuality.offsetScaledLogVariance;
    ptpClock->parentDS.grandmasterPriority1 = announce->grandmasterPriority1;
    ptpClock->parentDS.grandmasterPriority2 = announce->grandmasterPriority2;

    /* Timeproperties DS */
    ptpClock->timePropertiesDS.currentUtcOffset = announce->currentUtcOffset;
    ptpClock->timePropertiesDS.currentUtcOffsetValid = getFlag(header->flagField[1], FLAG1_UTC_OFFSET_VALID);
    ptpClock->timePropertiesDS.leap59 = getFlag(header->flagField[1], FLAG1_LEAP59);
    ptpClock->timePropertiesDS.leap61 = getFlag(header->flagField[1], FLAG1_LEAP61);
    ptpClock->timePropertiesDS.timeTraceable = getFlag(header->flagField[1], FLAG1_TIME_TRACEABLE);
    ptpClock->timePropertiesDS.frequencyTraceable = getFlag(header->flagField[1], FLAG1_FREQUENCY_TRACEABLE);
    ptpClock->timePropertiesDS.ptpTimescale = getFlag(header->flagField[1], FLAG1_PTP_TIMESCALE);
    ptpClock->timePropertiesDS.timeSource = announce->timeSource;
}

/* Local clock is becoming Master. Table 13 (9.3.5) of the spec.*/
void m1(PtpClock *ptpClock)
{
    /* Current data set update */
    ptpClock->portDS.stepsRemoved = 0;
    ptpClock->offsetFromMaster.seconds = ptpClock->offsetFromMaster.nanoseconds = 0;
    ptpClock->meanPathDelay.seconds = ptpClock->meanPathDelay.nanoseconds = 0;

    /* Parent data set */
    memcpy(ptpClock->parentDS.parentPortIdentity.clockIdentity, ptpClock->portDS.clockIdentity, CLOCK_IDENTITY_LENGTH);
    ptpClock->parentDS.parentPortIdentity.portNumber = 0;
    ptpClock->parentDS.parentStats = DEFAULT_PARENTS_STATS;
    ptpClock->parentDS.observedParentClockPhaseChangeRate = 0;
    ptpClock->parentDS.observedParentOffsetScaledLogVariance = 0;
    memcpy(ptpClock->parentDS.grandmasterIdentity, ptpClock->portDS.clockIdentity, CLOCK_IDENTITY_LENGTH);
    ptpClock->parentDS.grandmasterClockQuality.clockAccuracy = ptpClock->portDS.clockQuality.clockAccuracy;
    ptpClock->parentDS.grandmasterClockQuality.clockClass = ptpClock->portDS.clockQuality.clockClass;
    ptpClock->parentDS.grandmasterClockQuality.offsetScaledLogVariance = ptpClock->portDS.clockQuality.offsetScaledLogVariance;
    ptpClock->parentDS.grandmasterPriority1 = ptpClock->portDS.priority1;
    ptpClock->parentDS.grandmasterPriority2 = ptpClock->portDS.priority2;

    /* Time Properties data set */
    ptpClock->timePropertiesDS.currentUtcOffset = DEFAULT_UTC_OFFSET;
    ptpClock->timePropertiesDS.currentUtcOffsetValid = DEFAULT_UTC_VALID;
    ptpClock->timePropertiesDS.leap59 = false;
    ptpClock->timePropertiesDS.leap61 = false;
    ptpClock->timePropertiesDS.timeTraceable = DEFAULT_TIME_TRACEABLE;
    ptpClock->timePropertiesDS.frequencyTraceable = DEFAULT_FREQUENCY_TRACEABLE;
    ptpClock->timePropertiesDS.ptpTimescale = (bool)(DEFAULT_TIMESCALE == PTP_TIMESCALE);
    ptpClock->timePropertiesDS.timeSource = DEFAULT_TIME_SOURCE;
}
void addForeign(PtpClock *ptpClock, const MsgHeader *header, const MsgAnnounce * announce)
{
    int i, j;
    bool found = false;

    j = ptpClock->foreignMasterDS.best;

    /* Check if Foreign master is already known */
    for (i = 0; i < ptpClock->foreignMasterDS.count; i++)
    {
        if (isSamePortIdentity(&header->sourcePortIdentity, &ptpClock->foreignMasterDS.records[j].foreignMasterPortIdentity))
        {
            /* Foreign Master is already in Foreignmaster data set */
            ptpClock->foreignMasterDS.records[j].foreignMasterAnnounceMessages++;
            found = true;
            
            ptpClock->foreignMasterDS.records[j].header = *header;
            ptpClock->foreignMasterDS.records[j].announce = *announce;
            break;
        }

        j = (j + 1) % ptpClock->foreignMasterDS.count;
    }

    /* New Foreign Master */
    if (!found)
    {
        if (ptpClock->foreignMasterDS.count < ptpClock->foreignMasterDS.capacity)
        {
            ptpClock->foreignMasterDS.count++;
        }

        j = ptpClock->foreignMasterDS.i;

        /* Copy new foreign master data set from Announce message */
        memcpy(ptpClock->foreignMasterDS.records[j].foreignMasterPortIdentity.clockIdentity, header->sourcePortIdentity.clockIdentity, CLOCK_IDENTITY_LENGTH);
        ptpClock->foreignMasterDS.records[j].foreignMasterPortIdentity.portNumber = header->sourcePortIdentity.portNumber;
        ptpClock->foreignMasterDS.records[j].foreignMasterAnnounceMessages = 0;

        /* Header and announce field of each Foreign Master are usefull to run Best Master Clock Algorithm */
        ptpClock->foreignMasterDS.records[j].header = *header;
        ptpClock->foreignMasterDS.records[j].announce = *announce;


        ptpClock->foreignMasterDS.i = (ptpClock->foreignMasterDS.i + 1) % ptpClock->foreignMasterDS.capacity;
    }
}



/* Init ptpClock with run time values (initialization constants are in constants.h) */
void initData(PtpClock *ptpClock)
{
	ptpClock->portDS.versionNumber = VERSION_PTP;
	ptpClock->portDS.domainNumber = DEFAULT_DOMAIN_NUMBER;
	ptpClock->portDS.numberPorts = NUMBER_PORTS;
        ptpClock->portDS.twoStepFlag = DEFAULT_TWO_STEP_FLAG;
	ptpClock->portDS.slaveOnly = SLAVE_ONLY;
	//ptpClock->portDS.portState = PTP_INITIALIZING;
	ptpClock->portDS.delayMechanism = DEFAULT_DELAY_MECHANISM;
    if ((CLOCK_IDENTITY_LENGTH == 8) && (PTP_UUID_LENGTH == 6))
    {
        EUI48toEUI64(ptpClock->portUuidField, ptpClock->portDS.clockIdentity);
    }
    memcpy(ptpClock->portDS.portIdentity.clockIdentity, ptpClock->portDS.clockIdentity, CLOCK_IDENTITY_LENGTH);
    ptpClock->portDS.portIdentity.portNumber = NUMBER_PORTS;
    ptpClock->portDS.clockQuality.clockAccuracy = DEFAULT_CLOCK_ACCURACY;
    ptpClock->portDS.clockQuality.clockClass = DEFAULT_CLOCK_CLASS_SLAVE_ONLY;
    ptpClock->portDS.clockQuality.offsetScaledLogVariance = DEFAULT_CLOCK_VARIANCE;
    ptpClock->portDS.priority1 = DEFAULT_PRIORITY1;
    ptpClock->portDS.priority2 = DEFAULT_PRIORITY2;
	
    ptpClock->portDS.announceReceiptTimeout = DEFAULT_ANNOUNCE_RECEIPT_TIMEOUT;
	ptpClock->portDS.logAnnounceInterval = DEFAULT_ANNOUNCE_INTERVAL;
	ptpClock->portDS.logSyncInterval = DEFAULT_SYNC_INTERVAL;
    ptpClock->portDS.logMinDelayReqInterval = DEFAULT_DELAYREQ_INTERVAL;
	
	ptpClock->offsetFromMaster.seconds = 0;
	ptpClock->offsetFromMaster.nanoseconds = 0;
	ptpClock->meanPathDelay.seconds = 0;
	ptpClock->meanPathDelay.nanoseconds = 0;
	ptpClock->timeLock = false;

    ptpClock->foreignMasterDS.count = 0;
    ptpClock->foreignMasterDS.capacity = DEFAULT_MAX_FOREIGN_RECORDS;
	ptpClock->foreignMasterDS.records = ptpForeignRecords;

    ptpClock->inboundLatency.nanoseconds = DEFAULT_INBOUND_LATENCY;
    ptpClock->outboundLatency.nanoseconds = DEFAULT_OUTBOUND_LATENCY;

    ptpClock->servo.sDelay = DEFAULT_DELAY_S;
    ptpClock->servo.sOffset = DEFAULT_OFFSET_S;
    ptpClock->servo.ai = DEFAULT_AI;
    ptpClock->servo.ap = DEFAULT_AP;
    ptpClock->servo.noAdjust = NO_ADJUST;
    ptpClock->servo.noResetClock = DEFAULT_NO_RESET_CLOCK;
}

/* Data set comparison bewteen two foreign masters (9.3.4 fig 27) return similar to memcmp() */
int8_t bmcDataSetComparison(MsgHeader *headerA, MsgAnnounce *announceA,
                            MsgHeader *headerB, MsgAnnounce *announceB, PtpClock *ptpClock)
{
    int32_t grandmasterIdentityComp;
    short comp = 0;
    /* Identity comparison */
    grandmasterIdentityComp = memcmp(announceA->grandmasterIdentity, announceB->grandmasterIdentity, CLOCK_IDENTITY_LENGTH);
    if (0 != grandmasterIdentityComp)
    {
        /* Algoritgm part 1 - Figure 27 */
        COMPARE_AB_RETURN_BETTER(grandmasterPriority1,"grandmaster.Priority1");
        COMPARE_AB_RETURN_BETTER(grandmasterClockQuality.clockClass,"grandmaster.clockClass");
        COMPARE_AB_RETURN_BETTER(grandmasterClockQuality.clockAccuracy,"grandmaster.clockAccuracy");
        COMPARE_AB_RETURN_BETTER(grandmasterClockQuality.offsetScaledLogVariance,"grandmaster.Variance");
        COMPARE_AB_RETURN_BETTER(grandmasterPriority2,"grandmaster.Priority2");

        if (grandmasterIdentityComp > 0)
        {
            return B_better_then_A;
        }
        else if (grandmasterIdentityComp < 0)
        {
            return A_better_then_B;
        }
    }
    /* Algoritgm part 2 - Figure 28 */
    if ((announceA->stepsRemoved) > (announceB->stepsRemoved + 1))
    {
        return B_better_then_A;
    }
    if ((announceB->stepsRemoved) > (announceA->stepsRemoved + 1))
    {
        return A_better_then_B;
    }
    if ((announceA->stepsRemoved) > (announceB->stepsRemoved))
    {
        comp = memcmp(headerA->sourcePortIdentity.clockIdentity,
                      ptpClock->portDS.portIdentity.clockIdentity, CLOCK_IDENTITY_LENGTH);
        if (comp > 0)
        {
            return B_better_then_A;
        }
        else if (comp < 0)
        {
            return B_better_by_topology_then_A;
        }
        else
        {
            return ERROR_1;
        }
    }
    else if ((announceA->stepsRemoved) < (announceB->stepsRemoved))
    {
        comp = memcmp(headerB->sourcePortIdentity.clockIdentity,
                      ptpClock->portDS.portIdentity.clockIdentity, CLOCK_IDENTITY_LENGTH);
        if (comp > 0)
        {
            return A_better_then_B;
        }
        else if (comp < 0)
        {
            return A_better_by_topology_then_B;
        }
        else
        {
            return ERROR_1;
        }
    }
    comp = memcmp(headerA->sourcePortIdentity.clockIdentity, headerB->sourcePortIdentity.clockIdentity, CLOCK_IDENTITY_LENGTH);
    if (comp > 0)
    {
        return B_better_by_topology_then_A;
    }
    else if (comp < 0)
    {
        return A_better_by_topology_then_B;
    }
    return ERROR_2;
}

/* State decision algorithm 9.3.3 Fig 26 */
uint8_t bmcStateDecision(MsgHeader *header, MsgAnnounce *announce, PtpClock *ptpClock)
{
    int comp;
    if ((!ptpClock->foreignMasterDS.count) && (ptpClock->portDS.portState == PTP_LISTENING))
    {
        return PTP_LISTENING;
    }
    copyD0(&ptpClock->msgTmpHeader, &ptpClock->msgTmp.announce, ptpClock);
    comp = bmcDataSetComparison(&ptpClock->msgTmpHeader, &ptpClock->msgTmp.announce, header, announce, ptpClock);

	if (ptpClock->portDS.clockQuality.clockClass < 128)
	{
		if (A_better_then_B == comp)
	    {
	        m1(ptpClock);
	        return PTP_MASTER;
	    }
	    else
	    {
	        //s1(ptpClock, header, announce);
	        return PTP_PASSIVE;
	    }
	}
	else
	{
		if (A_better_then_B == comp)
	    {
	        m1(ptpClock);
	        return PTP_MASTER;
	    }
	    else
	    {
	        s1(ptpClock, header, announce);
	        return PTP_SLAVE;
	    }
	}

}

uint8_t bmc(PtpClock *ptpClock)
{
    int16_t i, best;
    /* Starting from i = 1, not necessery to test record[i = 0] against record[best = 0] -> they are the same */
    for (i = 1, best = 0; i < ptpClock->foreignMasterDS.count; i++)
    {
        if ((bmcDataSetComparison(&ptpClock->foreignMasterDS.records[i].header, &ptpClock->foreignMasterDS.records[i].announce,
                                  &ptpClock->foreignMasterDS.records[best].header, &ptpClock->foreignMasterDS.records[best].announce, ptpClock)) < 0)
        {
            best = i;
        }
    }
    ptpClock->foreignMasterDS.best = best;

    return bmcStateDecision(&ptpClock->foreignMasterDS.records[best].header, &ptpClock->foreignMasterDS.records[best].announce, ptpClock);
}

