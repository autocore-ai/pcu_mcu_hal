/*********************2020.02.23-alex********************/
#include "ptp_msg.h"

#if ( MACHINE_ENDIAN == 0)
#define flip16(x) ( (uint16_t) ( ( ( x ) << 8U ) | ( ( x ) >> 8U ) ) )
#define flip32(x)                                                      \
        (                                                              \
            ( uint32_t )                                               \
            (                                                          \
                ( ( ( ( uint32_t ) ( x ) )                ) << 24  ) | \
                ( ( ( ( uint32_t ) ( x ) ) & 0x0000ff00UL ) <<  8  ) | \
                ( ( ( ( uint32_t ) ( x ) ) & 0x00ff0000UL ) >>  8  ) | \
                ( ( ( ( uint32_t ) ( x ) )                ) >> 24  )   \
            )                                                          \
        )
#else
#define flip16( x ) ( ( uint16_t ) ( x ) )
#define flip32( x ) ( ( uint32_t ) ( x ) )
#endif

void msgPackHeader(const PtpClock *ptpClock, char *buf)
{
    uint8_t transport = 0x80; //(spec annex D)
    *(uint8_t*)(buf + 0) = transport;
    *(uint8_t*)(buf  + 1) = ptpClock->portDS.versionNumber;
    *(uint8_t*)(buf + 4) = ptpClock->portDS.domainNumber;
    if (ptpClock->portDS.twoStepFlag)
    {
        *(uint8_t*)(buf + 6) = FLAG0_TWO_STEP;
    }
    //*(uint8_t*)(buf + 6) = *(uint8_t*)(buf + 6) | FLAG0_UNICAST;
    memset((buf + 8), 0, 8);
    memcpy((buf + 20), ptpClock->portDS.portIdentity.clockIdentity, CLOCK_IDENTITY_LENGTH);
    *(int16_t*)(buf + 28) = flip16(ptpClock->portDS.portIdentity.portNumber);
    *(uint8_t*)(buf + 33) = 0x7F; //Default value (spec Table 24)
}

void msgUnpackHeader(const char *buf, MsgHeader *header)
{
    int32_t msb;
    uint32_t lsb;

    header->transportSpecific = (*(uint8_t*)(buf + 0)) >> 4;
    header->messageType = (*(uint8_t*)(buf + 0)) & 0x0F;
    header->versionPTP = (*(uint8_t*)(buf  + 1)) & 0x0F; //force reserved bit to zero if not
    header->messageLength = flip16(*(int16_t*)(buf  + 2));
    header->domainNumber = (*(uint8_t*)(buf + 4));
    memcpy(header->flagField, (buf + 6), FLAG_FIELD_LENGTH);
    memcpy(&msb, (buf + 8), 4);
    memcpy(&lsb, (buf + 12), 4);
    header->correctionfield = flip32(msb);
    header->correctionfield <<= 32;
    header->correctionfield += flip32(lsb);
    memcpy(header->sourcePortIdentity.clockIdentity, (buf + 20), CLOCK_IDENTITY_LENGTH);
    header->sourcePortIdentity.portNumber = flip16(*(int16_t*)(buf  + 28));
    header->sequenceId = flip16(*(int16_t*)(buf + 30));
    header->controlField = (*(uint8_t*)(buf + 32));
    header->logMessageInterval = (*(int8_t*)(buf + 33));
}

void msgUnpackAnnounce(const char *buf, MsgAnnounce *announce)
{
    announce->originTimestamp.secondsField.msb = flip16(*(int16_t*)(buf + 34));
    announce->originTimestamp.secondsField.lsb = flip32(*(uint32_t*)(buf + 36));
    announce->originTimestamp.nanosecondsField = flip32(*(uint32_t*)(buf + 40));
    announce->currentUtcOffset = flip16(*(int16_t*)(buf + 44));
    announce->grandmasterPriority1 = *(uint8_t*)(buf + 47);
    announce->grandmasterClockQuality.clockClass = *(uint8_t*)(buf + 48);
    announce->grandmasterClockQuality.clockAccuracy = *(uint8_t*)(buf + 49);
    announce->grandmasterClockQuality.offsetScaledLogVariance = flip16(*(int16_t*)(buf  + 50));
    announce->grandmasterPriority2 = *(uint8_t*)(buf + 52);
    memcpy(announce->grandmasterIdentity, (buf + 53), CLOCK_IDENTITY_LENGTH);
    announce->stepsRemoved = flip16(*(int16_t*)(buf + 61));
    announce->timeSource = *(uint8_t*)(buf + 63);
}

void msgUnpackSync(const char *buf, MsgSync *sync)
{
    sync->originTimestamp.secondsField.msb = flip16(*(int16_t*)(buf + 34));
    sync->originTimestamp.secondsField.lsb = flip32(*(uint32_t*)(buf + 36));
    sync->originTimestamp.nanosecondsField = flip32(*(uint32_t*)(buf + 40));
}

void msgUnpackFollowUp(const char *buf, MsgFollowUp *follow)
{
    follow->preciseOriginTimestamp.secondsField.msb = flip16(*(int16_t*)(buf  + 34));
    follow->preciseOriginTimestamp.secondsField.lsb = flip32(*(uint32_t*)(buf + 36));
    follow->preciseOriginTimestamp.nanosecondsField = flip32(*(uint32_t*)(buf + 40));
}


void msgPackDelayReq(const PtpClock *ptpClock, char *buf, const Timestamp *originTimestamp)
{
    /* Changes in header */
    *(char*)(buf + 0) = *(char*)(buf + 0) & 0xF0; //RAZ messageType
    *(char*)(buf + 0) = *(char*)(buf + 0) | DELAY_REQ; //Table 19
    *(int16_t*)(buf + 2)  = flip16(DELAY_REQ_LENGTH);
    *(int16_t*)(buf + 30) = flip16(ptpClock->sentDelayReqSequenceId);
    *(uint8_t*)(buf + 32) = CTRL_DELAY_REQ; //Table 23
    *(int8_t*)(buf + 33) = 0x7F; //Table 24
    memset((buf + 8), 0, 8);

    /* delay_req message */
    *(int16_t*)(buf + 34) = flip16(originTimestamp->secondsField.msb);
    *(uint32_t*)(buf + 36) = flip32(originTimestamp->secondsField.lsb);
    *(uint32_t*)(buf + 40) = flip32(originTimestamp->nanosecondsField);
}

void msgUnpackDelayResp(const char *buf, MsgDelayResp *resp)
{
    resp->receiveTimestamp.secondsField.msb = flip16(*(int16_t*)(buf  + 34));
    resp->receiveTimestamp.secondsField.lsb = flip32(*(uint32_t*)(buf + 36));
    resp->receiveTimestamp.nanosecondsField = flip32(*(uint32_t*)(buf + 40));
    memcpy(resp->requestingPortIdentity.clockIdentity, (buf + 44), CLOCK_IDENTITY_LENGTH);
    resp->requestingPortIdentity.portNumber = flip16(*(int16_t*)(buf  + 52));
}

void msgPackAnnounce(const PtpClock *ptpClock, char *buf)
{
    /* Changes in header */
    *(char*)(buf + 0) = *(char*)(buf + 0) & 0xF0; //RAZ messageType
    *(char*)(buf + 0) = *(char*)(buf + 0) | ANNOUNCE; //Table 19
    *(int16_t*)(buf + 2)  = flip16(ANNOUNCE_LENGTH);
    *(int16_t*)(buf + 30) = flip16(ptpClock->sentAnnounceSequenceId);
    *(uint8_t*)(buf + 32) = CTRL_OTHER; /* Table 23 - controlField */
    *(int8_t*)(buf + 33) = ptpClock->portDS.logAnnounceInterval;

    /* Announce message */
    memset((buf + 34), 0, 10); /* originTimestamp */
    *(int16_t*)(buf + 44) = flip16(ptpClock->timePropertiesDS.currentUtcOffset);
    *(uint8_t*)(buf + 47) = ptpClock->parentDS.grandmasterPriority1;
    *(uint8_t*)(buf + 48) = ptpClock->portDS.clockQuality.clockClass;
    *(uint8_t*)(buf + 49) = ptpClock->portDS.clockQuality.clockAccuracy;
    *(int16_t*)(buf + 50) = flip16(ptpClock->portDS.clockQuality.offsetScaledLogVariance);
    *(uint8_t*)(buf + 52) = ptpClock->parentDS.grandmasterPriority2;
    memcpy((buf + 53), ptpClock->parentDS.grandmasterIdentity, CLOCK_IDENTITY_LENGTH);
    *(int16_t*)(buf + 61) = flip16(ptpClock->portDS.stepsRemoved);
    *(uint8_t*)(buf + 63) = ptpClock->timePropertiesDS.timeSource;
}


/* Pack SYNC message */
void msgPackSync(const PtpClock *ptpClock, char *buf, const Timestamp *originTimestamp)
{
	/* Changes in header */
	*(char*)(buf + 0) = *(char*)(buf + 0) & 0xF0; //RAZ messageType
	*(char*)(buf + 0) = *(char*)(buf + 0) | SYNC; //Table 19
	*(int16_t*)(buf + 2)  = flip16(SYNC_LENGTH);
	*(int16_t*)(buf + 30) = flip16(ptpClock->sentSyncSequenceId);
	*(uint8_t*)(buf + 32) = CTRL_SYNC; //Table 23
	*(int8_t*)(buf + 33) = ptpClock->portDS.logSyncInterval;
	memset((buf + 8), 0, 8); /* correction field */

	/* Sync message */
	*(int16_t*)(buf + 34) = flip16(originTimestamp->secondsField.msb);
	*(uint32_t*)(buf + 36) = flip32(originTimestamp->secondsField.lsb);
	*(uint32_t*)(buf + 40) = flip32(originTimestamp->nanosecondsField);
}

/* Pack Follow_up message */
void msgPackFollowUp(const PtpClock *ptpClock, char*buf, const Timestamp *preciseOriginTimestamp)
{
	/* Changes in header */
	*(char*)(buf + 0) = *(char*)(buf + 0) & 0xF0; //RAZ messageType
	*(char*)(buf + 0) = *(char*)(buf + 0) | FOLLOW_UP; //Table 19
	*(int16_t*)(buf + 2)  = flip16(FOLLOW_UP_LENGTH);
	*(int16_t*)(buf + 30) = flip16(ptpClock->sentSyncSequenceId - 1);//sentSyncSequenceId has already been  incremented in issueSync
	*(uint8_t*)(buf + 32) = CTRL_FOLLOW_UP; //Table 23
	*(int8_t*)(buf + 33) = ptpClock->portDS.logSyncInterval;

	/* Follow_up message */
	*(int16_t*)(buf + 34) = flip16(preciseOriginTimestamp->secondsField.msb);
	*(uint32_t*)(buf + 36) = flip32(preciseOriginTimestamp->secondsField.lsb);
	*(uint32_t*)(buf + 40) = flip32(preciseOriginTimestamp->nanosecondsField);
}


/* Unpack delayReq message */
void msgUnpackDelayReq(const char *buf, MsgDelayReq *delayreq)
{
	delayreq->originTimestamp.secondsField.msb = flip16(*(int16_t*)(buf + 34));
	delayreq->originTimestamp.secondsField.lsb = flip32(*(uint32_t*)(buf + 36));
	delayreq->originTimestamp.nanosecondsField = flip32(*(uint32_t*)(buf + 40));
}


/* Pack delayResp message */
void msgPackDelayResp(const PtpClock *ptpClock, char *buf, const MsgHeader *header, const Timestamp *receiveTimestamp)
{
	/* Changes in header */
	*(char*)(buf + 0) = *(char*)(buf + 0) & 0xF0; //RAZ messageType
	*(char*)(buf + 0) = *(char*)(buf + 0) | DELAY_RESP; //Table 19
	*(int16_t*)(buf + 2)  = flip16(DELAY_RESP_LENGTH);
	/* *(uint8_t*)(buf+4) = header->domainNumber; */ /* TODO: Why? */
	memset((buf + 8), 0, 8);

	/* Copy correctionField of  delayReqMessage */
	*(int32_t*)(buf + 8) = flip32(header->correctionfield >> 32);
	*(int32_t*)(buf + 12) = flip32((int32_t)header->correctionfield);
	*(int16_t*)(buf + 30) = flip16(header->sequenceId);
	*(uint8_t*)(buf + 32) = CTRL_DELAY_RESP; //Table 23
	*(int8_t*)(buf + 33) = ptpClock->portDS.logMinDelayReqInterval; //Table 24

	/* delay_resp message */
	*(int16_t*)(buf + 34) = flip16(receiveTimestamp->secondsField.msb);
	*(uint32_t*)(buf + 36) = flip32(receiveTimestamp->secondsField.lsb);
	*(uint32_t*)(buf + 40) = flip32(receiveTimestamp->nanosecondsField);
	memcpy((buf + 44), header->sourcePortIdentity.clockIdentity, CLOCK_IDENTITY_LENGTH);
	*(int16_t*)(buf + 52) = flip16(header->sourcePortIdentity.portNumber);
}

