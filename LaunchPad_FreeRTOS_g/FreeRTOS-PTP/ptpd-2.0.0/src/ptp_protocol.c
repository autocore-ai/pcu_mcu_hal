#include "ptp_net.h"
#include "ptp_protocol.h"
#include "ptp_bmc.h"
#include "ptp_msg.h"
#include "ptp_time.h"
#include "ptp_servo.h"
#include <math.h>


//2020.02.23
#if 0
static char *stateString(uint8_t state)
{
    switch (state)
    {
        case PTP_INITIALIZING: return (char *) "PTP_INITIALIZING";
        case PTP_FAULTY: return (char *) "PTP_FAULTY";
        case PTP_DISABLED: return (char *) "PTP_DISABLED";
        case PTP_LISTENING: return (char *) "PTP_LISTENING";
        case PTP_PRE_MASTER: return (char *) "PTP_PRE_MASTER";
        case PTP_MASTER: return (char *) "PTP_MASTER";
        case PTP_PASSIVE: return (char *) "PTP_PASSIVE";
        case PTP_UNCALIBRATED: return (char *) "PTP_UNCALIBRATED";
        case PTP_SLAVE: return (char *) "PTP_SLAVE";
        default: break;
    }
    return (char *) "UNKNOWN";
}
static char *messageString(uint8_t type)
{
    switch (type)
    {
        case SYNC: return (char *) "SYNC";
        case DELAY_REQ: return (char *) "DELAY_REQ";
        case PDELAY_REQ: return (char *) "PDELAY_REQ";
        case PDELAY_RESP: return (char *) "PDELAY_RESP";
        case FOLLOW_UP: return (char *) "FOLLOW_UP";
        case DELAY_RESP: return (char *) "DELAY_RESP";
        case PDELAY_RESP_FOLLOW_UP: return (char *) "PDELAY_RESP_FOLLOW_UP";
        case ANNOUNCE: return (char *) "ANNOUNCE";
        case SIGNALING: return (char *) "SIGNALING";
        case MANAGEMENT: return (char *) "MANAGEMENT";
        default: break;
    }
    return (char *) "UNKNOWN";
}
#endif


bool ptp_doInit(PtpClock *ptpClock)
{
    if (!netInit(&ptpClock->netPath, ptpClock))
    {
        return false;
    }
    else
    {
        initData(ptpClock);
        initTimer();
        initClock(ptpClock);
        m1(ptpClock);
        msgPackHeader(ptpClock, ptpClock->msgObuf);
        return true;
    }
}


//2020.02.23
void ptp_toState(PtpClock *ptpClock, uint8_t state)
{
    ptpClock->messageActivity = true;
    //FreeRTOS_printf(("[1]ptp_toState:leaving state %s \r\n", stateString(ptpClock->portDS.portState)));
    /* leaving state tasks */
    switch (ptpClock->portDS.portState)//旧状态
    {
		case PTP_MASTER://ok
			timerStop(SYNC_INTERVAL_TIMER);  
			timerStop(ANNOUNCE_INTERVAL_TIMER);
			break;
		case PTP_SLAVE://ok
			timerStop(ANNOUNCE_RECEIPT_TIMER);
			initClock(ptpClock); 
			break;
		case PTP_PASSIVE://ok
			break;
		case PTP_LISTENING://ok
			timerStop(ANNOUNCE_RECEIPT_TIMER);
			break;
		default:
			break;

    }
    //FreeRTOS_printf(("[1]ptp_toState:entering state %s\r\n", stateString(state)));
    /* Entering state tasks */
    switch (state)//新状态
    {
        case PTP_INITIALIZING://ok
            ptpClock->portDS.portState = PTP_INITIALIZING;
            break;
        case PTP_FAULTY://ok
            ptpClock->portDS.portState = PTP_FAULTY;
            break;
		case PTP_DISABLED://ok
			ptpClock->portDS.portState = PTP_DISABLED;
			break;
		case PTP_UNCALIBRATED://ok
			ptpClock->portDS.portState = PTP_UNCALIBRATED;
			break;
        case PTP_LISTENING://ok
			timerStop(SYNC_INTERVAL_TIMER);
			timerStop(ANNOUNCE_INTERVAL_TIMER);
            timerStart(ANNOUNCE_RECEIPT_TIMER, (ptpClock->portDS.announceReceiptTimeout) * (pow2ms(ptpClock->portDS.logAnnounceInterval)));
            ptpClock->portDS.portState = PTP_LISTENING;
            break;
		case PTP_MASTER://ok
			timerStart(SYNC_INTERVAL_TIMER, pow2ms(ptpClock->portDS.logSyncInterval));
            timerStart(ANNOUNCE_INTERVAL_TIMER, pow2ms(ptpClock->portDS.logAnnounceInterval));
			ptpClock->portDS.portState = PTP_MASTER;
			break;
		case PTP_PASSIVE://ok
			break;
        case PTP_SLAVE://ok
			initClock(ptpClock);
			ptpClock->waitingForFollowUp = false;
            timerStart(ANNOUNCE_RECEIPT_TIMER, (ptpClock->portDS.announceReceiptTimeout) * (pow2ms(ptpClock->portDS.logAnnounceInterval)));
            ptpClock->portDS.portState = PTP_SLAVE;
            break;
        default:
            break;
    }
}

/* Handle actions and events for 'port_state' */
void ptp_doState(PtpClock *ptpClock)
{
	uint8_t state;
    ptpClock->messageActivity = false;
    //FreeRTOS_printf(("[2]ptp_doState1:entering state %s\r\n", stateString(ptpClock->portDS.portState)));
    switch (ptpClock->portDS.portState)//当前状态
    {
		case PTP_INITIALIZING://ok
			if (ptp_doInit(ptpClock))
			{
				ptp_toState(ptpClock, PTP_LISTENING);
			}
			else
			{
				ptp_toState(ptpClock, PTP_FAULTY);
			}
			break;
		case PTP_LISTENING://ok
		case PTP_PASSIVE:
		case PTP_SLAVE:
		case PTP_MASTER:
            if (getFlag(ptpClock->events, STATE_DECISION_EVENT))//收到Announce报文
            {
                clearFlag(ptpClock->events, STATE_DECISION_EVENT);
                state = bmc(ptpClock);//setp7 ptpClock->recommendedState = PTP_SLAVE
                //FreeRTOS_printf(("[2]bcm:entering state %s\r\n", stateString(state)));
                if(state != ptpClock->portDS.portState)
					ptp_toState(ptpClock, state);
            }
            break;
        default:
            break;
    }
    //FreeRTOS_printf(("[2]ptp_doState2:entering state %s\r\n", stateString(ptpClock->portDS.portState)));
    switch (ptpClock->portDS.portState)//当前状态-更新后
    {
	case PTP_FAULTY://ok
		ptp_toState(ptpClock, PTP_INITIALIZING);
		return;	
	case PTP_LISTENING://ok
	case PTP_UNCALIBRATED:
	case PTP_SLAVE:
	case PTP_PASSIVE:
		ptp_handle(ptpClock);

		if (timerExpired(ANNOUNCE_RECEIPT_TIMER))
		{
		    ptpClock->foreignMasterDS.count = 0;
		    ptpClock->foreignMasterDS.i = 0;
			if (!ptpClock->portDS.slaveOnly || ptpClock->portDS.clockQuality.clockClass != DEFAULT_CLOCK_CLASS_SLAVE_ONLY)
			{
				m1(ptpClock);
				ptp_toState(ptpClock, PTP_MASTER);
			} 
			else 
			{
				ptp_toState(ptpClock, PTP_LISTENING);
			}
		}
		break;
	case PTP_MASTER://ok
		if (timerExpired(ANNOUNCE_INTERVAL_TIMER)) 
		{
			issueAnnounce(ptpClock);
            timerStart(ANNOUNCE_INTERVAL_TIMER, pow2ms(ptpClock->portDS.logAnnounceInterval));
		}
		if (timerExpired(SYNC_INTERVAL_TIMER)) 
		{
			issueSync(ptpClock);
			timerStart(SYNC_INTERVAL_TIMER, pow2ms(ptpClock->portDS.logSyncInterval));
		}
		ptp_handle( ptpClock);
		break;
	case PTP_DISABLED://ok
		break;
	default:
		break;
	}
}


/* Check and ptp_handle received messages */
static void ptp_handle(PtpClock *ptpClock)
{
    TimeInternal time;
    recv_udp_event_msg(&ptpClock->netPath, ptpClock->msgIbuf, &ptpClock->msgIbufLength, &time);
    if(ptpClock->msgIbufLength < 0)
    {
        FreeRTOS_printf(("handle: failed to receive on the event socket\r\n"));
        ptp_toState(ptpClock, PTP_FAULTY);
        return;
    }
    else if(!ptpClock->msgIbufLength)
    {
        recv_udp_general_msg(&ptpClock->netPath, ptpClock->msgIbuf, &ptpClock->msgIbufLength, &time);
        if(ptpClock->msgIbufLength < 0)
        {
            FreeRTOS_printf(("handle: failed to receive on the general socket\r\n"));
            ptp_toState(ptpClock, PTP_FAULTY);
            return;
        }
        else if(!ptpClock->msgIbufLength)
        {
            return;
        }
    }
    if (ptpClock->msgIbufLength < HEADER_LENGTH)
    {
        ptp_toState(ptpClock, PTP_FAULTY);
        return;
    }
    msgUnpackHeader(ptpClock->msgIbuf, &ptpClock->msgTmpHeader);
    if (ptpClock->msgTmpHeader.versionPTP != ptpClock->portDS.versionNumber)
    {
        return;
    }
    if (ptpClock->msgTmpHeader.domainNumber != ptpClock->portDS.domainNumber)
    {
        return;
    }
    bool isFromSelf = isSamePortIdentity(&ptpClock->portDS.portIdentity, &ptpClock->msgTmpHeader.sourcePortIdentity);
	if (!isFromSelf && time.seconds > 0)
    {
        subTime(&time, &time, &ptpClock->inboundLatency);
    }

	if(ptpClock->timeLock)
	{
	    return;
	}
    switch (ptpClock->msgTmpHeader.messageType)
    {
    case ANNOUNCE://master
        handleAnnounce(ptpClock, isFromSelf);
        break;
    case SYNC://E2E:1)m->s
        handleSync(ptpClock, &time, isFromSelf);
        break;
    case FOLLOW_UP://E2E:2)m->s
        handleFollowUp(ptpClock, isFromSelf);
        break;
    case DELAY_REQ://E2E:3)s->m
        handleDelayReq(ptpClock, &time, isFromSelf);
        break;
    case DELAY_RESP://E2E:4)m->s
        handleDelayResp(ptpClock, isFromSelf);
        break;
    default:
        FreeRTOS_printf(("ptp_handle: unrecognized message %d\r\n", ptpClock->msgTmpHeader.messageType));
        break;
    }
}
//ok
static void handleAnnounce(PtpClock *ptpClock, bool isFromSelf)
{
    bool  isFromCurrentParent = false;
    if (ptpClock->msgIbufLength < ANNOUNCE_LENGTH)
    {
    	ptp_toState(ptpClock, PTP_FAULTY);
        return;
    }
	if(isFromSelf)
	{
		return;
	}
    switch (ptpClock->portDS.portState)
    {
        case PTP_INITIALIZING://ok
		case PTP_FAULTY:
        case PTP_DISABLED:
            break;
		case PTP_UNCALIBRATED://ok
        case PTP_SLAVE:
            setFlag(ptpClock->events, STATE_DECISION_EVENT);
			
            isFromCurrentParent = isSamePortIdentity(&ptpClock->parentDS.parentPortIdentity,
            	&ptpClock->msgTmpHeader.sourcePortIdentity);
			
            msgUnpackAnnounce(ptpClock->msgIbuf, &ptpClock->msgTmp.announce);
            if (isFromCurrentParent)
            {
                s1(ptpClock, &ptpClock->msgTmpHeader, &ptpClock->msgTmp.announce);
                timerStart(ANNOUNCE_RECEIPT_TIMER, (ptpClock->portDS.announceReceiptTimeout)*(pow2ms(ptpClock->portDS.logAnnounceInterval)));
            }
            else
            {
                addForeign(ptpClock, &ptpClock->msgTmpHeader, &ptpClock->msgTmp.announce);
                timerStart(ANNOUNCE_RECEIPT_TIMER, (ptpClock->portDS.announceReceiptTimeout)*(pow2ms(ptpClock->portDS.logAnnounceInterval)));
			}
            break;
		case PTP_PASSIVE://ok
			break;
		case PTP_MASTER://ok
		case PTP_LISTENING:
		default:	
            msgUnpackAnnounce(ptpClock->msgIbuf, &ptpClock->msgTmp.announce);
            setFlag(ptpClock->events, STATE_DECISION_EVENT);
            addForeign(ptpClock, &ptpClock->msgTmpHeader, &ptpClock->msgTmp.announce);
            break;
    }
}

/*************************************E2E**************************************/
//E2E:1)m->s
static void handleSync(PtpClock *ptpClock, TimeInternal *time, bool isFromSelf)
{
    TimeInternal correctionField;
    bool  isFromCurrentParent = false;
    if (ptpClock->msgIbufLength < SYNC_LENGTH)
    {
        ptp_toState(ptpClock, PTP_FAULTY);
        return;
    }
	if(isFromSelf)
	{
		return;
	}
    switch (ptpClock->portDS.portState)
    {
        case PTP_INITIALIZING://ok
        case PTP_FAULTY:
        case PTP_LISTENING:
            break;
        case PTP_UNCALIBRATED://ok
        case PTP_SLAVE:
            isFromCurrentParent = isSamePortIdentity(&ptpClock->parentDS.parentPortIdentity,
            	&ptpClock->msgTmpHeader.sourcePortIdentity);
            if (isFromCurrentParent)
            {
                ptpClock->timestamp_syncRecieve = *time;
	            scaledNanosecondsToInternalTime(&ptpClock->msgTmpHeader.correctionfield, &correctionField);
	            if (getFlag(ptpClock->msgTmpHeader.flagField[0], FLAG0_TWO_STEP))
	            {
	                ptpClock->waitingForFollowUp = true;
	                ptpClock->recvSyncSequenceId = ptpClock->msgTmpHeader.sequenceId;
	                ptpClock->correctionField_sync = correctionField;
	            }
	            else
	            {
	                FreeRTOS_printf(("handleSync: only support two step\r\n"));
	            }
            }
            break;
		case PTP_MASTER:
			break;
		case PTP_PASSIVE:
			break;
        default:
            break;
    }
}
//E2E:2)m->s
static void handleFollowUp(PtpClock *ptpClock, bool isFromSelf)
{
    TimeInternal preciseOriginTimestamp;
    TimeInternal correctionField;
    bool  isFromCurrentParent = false;

    if (ptpClock->msgIbufLength < FOLLOW_UP_LENGTH)
    {
        ptp_toState(ptpClock, PTP_FAULTY);
        return;
    }
	if (isFromSelf)
	{
		return;
	}
    switch (ptpClock->portDS.portState)
    {
        case PTP_INITIALIZING://ok
        case PTP_FAULTY:
		case PTP_DISABLED:
        case PTP_LISTENING:
            break;
        case PTP_UNCALIBRATED://ok
        case PTP_SLAVE:
            isFromCurrentParent = isSamePortIdentity(&ptpClock->parentDS.parentPortIdentity,
            	&ptpClock->msgTmpHeader.sourcePortIdentity);
            if (!ptpClock->waitingForFollowUp)
            {
                FreeRTOS_printf(("handleFollowUp:  !waitingForFollowUp\r\n"));
                break;
            }
            if (!isFromCurrentParent)
            {
                break;
            }
            if (ptpClock->recvSyncSequenceId !=  ptpClock->msgTmpHeader.sequenceId)
            {
                FreeRTOS_printf(("handleFollowUp:  !recvSyncSequenceId\r\n"));
                break;
            }
            msgUnpackFollowUp(ptpClock->msgIbuf, &ptpClock->msgTmp.follow);

            ptpClock->waitingForFollowUp = false;
            /* synchronize local clock */
            toInternalTime(&preciseOriginTimestamp, &ptpClock->msgTmp.follow.preciseOriginTimestamp);
            scaledNanosecondsToInternalTime(&ptpClock->msgTmpHeader.correctionfield, &correctionField);
            addTime(&correctionField, &correctionField, &ptpClock->correctionField_sync);
            updateOffset(ptpClock, &ptpClock->timestamp_syncRecieve, &preciseOriginTimestamp, &correctionField);
            updateClock(ptpClock);
            if(ptpClock->portDS.delayMechanism == E2E)
            {
                issueDelayReq(ptpClock);
            }
			break;
		case PTP_MASTER://ok
		case PTP_PASSIVE:
			break;
        default:
            break;
    }
}


static void handleDelayReq(PtpClock *ptpClock, TimeInternal *time, bool isFromSelf)
{
	if (ptpClock->portDS.delayMechanism == E2E)
	{
		if (ptpClock->msgIbufLength < DELAY_REQ_LENGTH)
		{
			ptp_toState(ptpClock, PTP_FAULTY);
			return;
		}
		if (isFromSelf)
		{
			return;
		}
		switch (ptpClock->portDS.portState)
		{
			case PTP_INITIALIZING://ok
			case PTP_FAULTY:
			case PTP_DISABLED:
			case PTP_UNCALIBRATED:
			case PTP_LISTENING:
				return;		
			case PTP_SLAVE:
				break;		
			case PTP_MASTER://ok
				issueDelayResp(ptpClock, time, &ptpClock->msgTmpHeader);
				break;
			default:
				break;
		}
	}
}
//E2E:4)m->s
static void handleDelayResp(PtpClock *ptpClock, bool  isFromSelf)
{
    bool  isFromCurrentParent = false;
    bool  isCurrentRequest = false;
    TimeInternal correctionField;
	if (ptpClock->msgIbufLength < DELAY_RESP_LENGTH)
	{
		ptp_toState(ptpClock, PTP_FAULTY);
		return;
	}
	if (isFromSelf)
	{
		return;
	}

    if (ptpClock->portDS.delayMechanism == E2E)
    {
		switch (ptpClock->portDS.portState)
		{
			case PTP_INITIALIZING://ok
			case PTP_FAULTY:
			case PTP_DISABLED:
			case PTP_LISTENING:
			case PTP_UNCALIBRATED:
				break;
			case PTP_SLAVE://ok
				msgUnpackDelayResp(ptpClock->msgIbuf, &ptpClock->msgTmp.resp);
				isFromCurrentParent = isSamePortIdentity(&ptpClock->parentDS.parentPortIdentity,
					&ptpClock->msgTmpHeader.sourcePortIdentity);
		
				isCurrentRequest = isSamePortIdentity(&ptpClock->portDS.portIdentity,
					&ptpClock->msgTmp.resp.requestingPortIdentity);
		
				if (((ptpClock->sentDelayReqSequenceId - 1) == ptpClock->msgTmpHeader.sequenceId) && isCurrentRequest && isFromCurrentParent)
				{
					toInternalTime(&ptpClock->timestamp_delayReqRecieve, &ptpClock->msgTmp.resp.receiveTimestamp);
					scaledNanosecondsToInternalTime(&ptpClock->msgTmpHeader.correctionfield, &correctionField);
					updateDelay(ptpClock, &ptpClock->timestamp_delayReqSend, &ptpClock->timestamp_delayReqRecieve, &correctionField);
					ptpClock->portDS.logMinDelayReqInterval = ptpClock->msgTmpHeader.logMessageInterval;
				}
				else
				{
					FreeRTOS_printf(("handleDelayResp: doesn't match with the delayReq\r\n"));
					break;
				}
			default:
				break;
		}

    }
}

static void issueAnnounce(PtpClock *ptpClock)
{
	msgPackAnnounce(ptpClock, ptpClock->msgObuf);

	if (!send_udp_general_msg(&ptpClock->netPath, ptpClock->msgObuf, ANNOUNCE_LENGTH))
	{
		ptp_toState(ptpClock, PTP_FAULTY);
	}
	else
	{
		ptpClock->sentAnnounceSequenceId++;
	}
}

static void issueSync(PtpClock *ptpClock)
{
	Timestamp originTimestamp;
	TimeInternal internalTime;

	getTime(&internalTime);
	fromInternalTime(&internalTime, &originTimestamp);
	msgPackSync(ptpClock, ptpClock->msgObuf, &originTimestamp);

	if (!send_udp_event_msg(&ptpClock->netPath, ptpClock->msgObuf, SYNC_LENGTH))
	{
		ptp_toState(ptpClock, PTP_FAULTY);
		return;
	}
	else
	{
		ptpClock->sentSyncSequenceId++;
		if ( ptpClock->portDS.twoStepFlag )
		{
			addTime(&internalTime, &internalTime, &ptpClock->outboundLatency);
			issueFollowup(ptpClock, &internalTime);
		}
	}
}

static void issueFollowup(PtpClock *ptpClock, const TimeInternal *time)
{
	Timestamp preciseOriginTimestamp;

	fromInternalTime(time, &preciseOriginTimestamp);
	msgPackFollowUp(ptpClock, ptpClock->msgObuf, &preciseOriginTimestamp);

	if (!send_udp_general_msg(&ptpClock->netPath, ptpClock->msgObuf, FOLLOW_UP_LENGTH))
	{
		ptp_toState(ptpClock, PTP_FAULTY);
	}
}


static void issueDelayReq(PtpClock *ptpClock)
{
    Timestamp originTimestamp;
    TimeInternal internalTime;

    getTime(&internalTime);
    fromInternalTime(&internalTime, &originTimestamp);
    msgPackDelayReq(ptpClock, ptpClock->msgObuf, &originTimestamp);

    if (!send_udp_event_msg(&ptpClock->netPath, ptpClock->msgObuf, DELAY_REQ_LENGTH))
    {
        ptp_toState(ptpClock, PTP_FAULTY);
    }
    else
    {
		ptpClock->sentDelayReqSequenceId++;
		addTime(&internalTime, &internalTime, &ptpClock->outboundLatency);
		ptpClock->timestamp_delayReqSend = internalTime;
    }
}


static void issueDelayResp(PtpClock *ptpClock, const TimeInternal *time, const MsgHeader * delayReqHeader)
{
	Timestamp requestReceiptTimestamp;

	fromInternalTime(time, &requestReceiptTimestamp);
	msgPackDelayResp(ptpClock, ptpClock->msgObuf, delayReqHeader, &requestReceiptTimestamp);

	if (!send_udp_general_msg(&ptpClock->netPath, ptpClock->msgObuf, PDELAY_RESP_LENGTH))
	{
		ptp_toState(ptpClock, PTP_FAULTY);
	}
}

