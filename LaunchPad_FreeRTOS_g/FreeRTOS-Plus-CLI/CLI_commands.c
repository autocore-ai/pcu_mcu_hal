#include "CLI_commands.h"
#include "FreeRTOS.h"
#include "FreeRTOS_IO.h"
#include "os_task.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "FreeRTOS_IP.h"
#include "FreeRTOS_Sockets.h"
#include "HL_emac.h"
#include "HL_mdio.h"
#include "HL_phy_dp83640.h"
extern hdkif_t hdkif_data[MAX_EMAC_INSTANCE];



#if ( configGENERATE_RUN_TIME_STATS == 1 )
/*-----------------------------------------------------------*/
portBASE_TYPE xTaskStatsCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString )
{
	const char *pcHeader =  "\r\nTask          State  Priority  Stack	#\r\n************************************************\r\n";

	( void ) pcCommandString;
	configASSERT( pcWriteBuffer );

	/* This function assumes the buffer length is adequate. */
	( void ) xWriteBufferLen;

	/* Generate a table of task stats. */
	strcpy((char*)pcWriteBuffer, (char*)pcHeader);
	vTaskList((char*)(pcWriteBuffer + strlen(pcHeader)));
	/* There is no more data to return after this single string, so return
	pdFALSE. */
	return pdFALSE;
}

/*-----------------------------------------------------------*/
portBASE_TYPE xRunTimeStatsCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString )
{
	const char * const pcHeader = ( char * ) "\r\nTask            Abs Time      % Time\r\n****************************************\r\n";

	( void ) pcCommandString;
	configASSERT( pcWriteBuffer );

	/* This function assumes the buffer length is adequate. */
	( void ) xWriteBufferLen;

	/* Generate a table of task stats. */
	strcpy((char *)pcWriteBuffer,(char *)pcHeader);
	vTaskGetRunTimeStats((char*)(pcWriteBuffer + strlen(pcHeader)));
	/* There is no more data to return after this single string, so return
	pdFALSE. */
	return pdFALSE;
}
#endif

/*-----------------------------------------------------------*/
portBASE_TYPE xMemTestCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString )
{
	static uint32 xMemTestState = 0;
	BaseType_t xReturnValue = pdFALSE;
	BaseType_t i,j = 0;
	uint32 xTestPattern;
	static uint32 xRandomSeed;

	const char * const pcHeader = (char *) "EMIF base address: %#p, size: %d KiB\r\n";
	const char * const pcTest0 = (char *) "Test 0 [Address test, own address, sequential]: ";
	const char * const pcTest1 = (char *) "Test 1 [Address test, walking ones]: ";
	const char * const pcTest2 = (char *) "Test 2 [Random number sequence, seed: %d]: ";
	const char * const pcError = (char *) "Error.\r\nAddress: %#p write: %#010lx read: %#010lx.\r\n";
	const char * const pcPassed = (char *) "Passed.\r\n";

	( void ) pcCommandString;
	configASSERT( pcWriteBuffer );

	/* This function assumes the buffer length is adequate. */
	( void ) xWriteBufferLen;

	switch (xMemTestState)
	{
		case 0:
			sprintf((char *)pcWriteBuffer, pcHeader, EMIF_BASE_ADDRESS, boardEMIF_MEMORY_SIZE/1024);
			xMemTestState++;
			xReturnValue = pdTRUE;
			break;
		case 1:
			strcpy((char *)pcWriteBuffer,(char *)pcTest0);
			strcpy((char *)pcWriteBuffer,(char *)pcTest0);
			xMemTestState++;
			xReturnValue = pdTRUE;
			break;
		case 2:
			/* Test 0 [Address test, own address, Sequential] */
			for(i=0; i<boardEMIF_MEMORY_SIZE/sizeof(uint32); i++)
			{
				EMIF_BASE_ADDRESS[i] = (uint32)&(EMIF_BASE_ADDRESS[i]);
			}
			for(i=0; i<boardEMIF_MEMORY_SIZE/sizeof(uint32); i++)
			{
				if(EMIF_BASE_ADDRESS[i] != (uint32)&(EMIF_BASE_ADDRESS[i]))
				{
					sprintf((char *)pcWriteBuffer, pcError, (EMIF_BASE_ADDRESS + i), &(EMIF_BASE_ADDRESS[i]), EMIF_BASE_ADDRESS[i]);
					xMemTestState = 0;
					return pdFALSE;
				}
			}
			strcpy((char *)pcWriteBuffer,pcPassed);
			xMemTestState++;
			xReturnValue = pdTRUE;
			break;
		case 3:
			strcpy((char *)pcWriteBuffer,(char *)pcTest1);
			xMemTestState++;
			xReturnValue = pdTRUE;
			break;
		case 4:
			/* Test 1 [Address test, walking ones] */
			for(i=0; i<boardEMIF_MEMORY_SIZE/sizeof(uint32); i++)
			{
				for(j=0; j<32; j++)
				{
				xTestPattern = 0x00000001 << j;
				*(EMIF_BASE_ADDRESS + i) = xTestPattern;
				if(*(EMIF_BASE_ADDRESS + i) != xTestPattern)
					{
					sprintf((char *)pcWriteBuffer,pcError, (EMIF_BASE_ADDRESS + i), xTestPattern, *(EMIF_BASE_ADDRESS + i));
					xMemTestState = 0;
					return pdFALSE;
					}
				}
			}
			strcpy((char *)pcWriteBuffer,pcPassed);
			xMemTestState++;
			xReturnValue = pdTRUE;
			break;
		case 5:
			xRandomSeed = portGET_RUN_TIME_COUNTER_VALUE();
			sprintf((char *)pcWriteBuffer, pcTest2, xRandomSeed);
			xMemTestState++;
			xReturnValue = pdTRUE;
			break;
		case 6:
			srand(xRandomSeed);
			for(i=0; i<boardEMIF_MEMORY_SIZE/sizeof(uint32); i++)
			{
				xTestPattern = rand() & 0xff | (rand() & 0xff) << 8 | (rand() & 0xff) << 16 |(rand() & 0xff) << 24;
				EMIF_BASE_ADDRESS[i] = xTestPattern;
			}
			srand(xRandomSeed);
			for(i=0; i<boardEMIF_MEMORY_SIZE/sizeof(uint32); i++)
			{
				xTestPattern = rand() & 0xff | (rand() & 0xff) << 8 | (rand() & 0xff) << 16 |(rand() & 0xff) << 24;
				if(EMIF_BASE_ADDRESS[i] != xTestPattern)
				{
					sprintf((char *)pcWriteBuffer, pcError, (EMIF_BASE_ADDRESS + i), xTestPattern, EMIF_BASE_ADDRESS[i]);
					xMemTestState = 0;
					return pdFALSE;
				}
			}
			strcpy((char *)pcWriteBuffer,pcPassed);
			xReturnValue = pdTRUE;
			xMemTestState = 0;
			xReturnValue = pdFALSE;
			break;
	}
	return xReturnValue;
}

/*-----------------------------------------------------------*/
BaseType_t xEMACRxEventSemaphoreFulls = 0;
portBASE_TYPE xEmacStatCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString )
{
	BaseType_t xReturnValue = pdFALSE;
	uint32_t xRxGoodFrames, xRxCrcErrors, xRxAlignCodeErrors, xRxOverSizedFrames, xRxJabberFrames, xRxUnderSizedFrames, xRxFrameFragments, xRxFilteredFrames, xRxOctetFrames, xRxSumErrors, xRxDmaOverruns;
	uint32_t xTxGoodFrames, xTxCollisionFrames, xTxExcessiveCollision, xTxLateCollision, xTxUnderrunError, xTxCarrierSenseError, xTxOctetFrames, xTxSumErrors;
	uint8_t xMacAddr[6] ={0x00,0x00,0x00,0x00,0x00,0x00};
	uint32_t xIpAddr, xNetMask, xGatewayAddr, xDNSAddr;
	uint32_t xRxHeadPointer, xTxHeadPointer;
	char cIpBuffer[17], cNetMaskBuffer[17], cGWBuffer[17], cDNSBuffer[17];
	hdkif_t *hdkif = &hdkif_data[0U];

	// RX Statistics
	xRxGoodFrames =  EMACReadNetStatRegisters(EMAC_BASE, 0);		// Good Receive Frames Register (RXGOODFRAMES) (offset = 200h)
	xRxCrcErrors =  EMACReadNetStatRegisters(EMAC_BASE, 4);			// Receive CRC Errors Register (RXCRCERRORS) (offset = 210h)
	xRxAlignCodeErrors = EMACReadNetStatRegisters(EMAC_BASE, 5);	// Receive Alignment/Code Errors Register (RXALIGNCODEERRORS) (offset = 214h)
	xRxOverSizedFrames = EMACReadNetStatRegisters(EMAC_BASE, 6);	// Receive Oversized Frames Register (RXOVERSIZED) (offset = 218h)
	xRxJabberFrames = EMACReadNetStatRegisters(EMAC_BASE, 7);		// Receive Jabber Frames Register (RXJABBER) (offset = 21Ch)
	xRxUnderSizedFrames = EMACReadNetStatRegisters(EMAC_BASE, 8);	// Receive Undersized Frames Register (RXUNDERSIZED) (offset = 220h)
	xRxFrameFragments = EMACReadNetStatRegisters(EMAC_BASE, 9);		// Receive Frame Fragments Register (RXFRAGMENTS) (offset = 224h)
	xRxFilteredFrames = EMACReadNetStatRegisters(EMAC_BASE, 10);	// Filtered Receive Frames Register (RXFILTERED) (offset = 228h)
	xRxOctetFrames = EMACReadNetStatRegisters(EMAC_BASE, 12);		// Receive Octet Frames Register (RXOCTETS) (offset = 230h)
	xRxSumErrors = xRxCrcErrors + xRxAlignCodeErrors + xRxOverSizedFrames + xRxJabberFrames + xRxUnderSizedFrames + xRxFrameFragments;
	xRxDmaOverruns = EMACReadNetStatRegisters(EMAC_BASE, 35);		// Receive DMA Overruns Register (RXDMAOVERRUNS) (offset = 28Ch)
	// TX Statistics
	xTxGoodFrames =  EMACReadNetStatRegisters(EMAC_BASE, 13);		// Good Transmit Frames Register (TXGOODFRAMES) (offset = 234h)
	xTxCollisionFrames = EMACReadNetStatRegisters(EMAC_BASE, 18);	// Transmit Collision Frames Register (TXCOLLISION) (offset = 248h)
	xTxExcessiveCollision = EMACReadNetStatRegisters(EMAC_BASE, 21);// Transmit Excessive Collision Frames Register (TXEXCESSIVECOLL) (offset = 254h)
	xTxLateCollision = EMACReadNetStatRegisters(EMAC_BASE, 22);		// Transmit Late Collision Frames Register (TXLATECOLL) (offset = 258h)
	xTxUnderrunError = EMACReadNetStatRegisters(EMAC_BASE, 23);		// Transmit Underrun Error Register (TXUNDERRUN) (offset = 25Ch)
	xTxCarrierSenseError = EMACReadNetStatRegisters(EMAC_BASE, 24);	// Transmit Carrier Sense Errors Register (TXCARRIERSENSE) (offset = 260h)
	xTxOctetFrames = EMACReadNetStatRegisters(EMAC_BASE, 25);		// Transmit Octet Frames Register (TXOCTETS) (offset = 264h)
	xTxSumErrors = xTxExcessiveCollision + xTxLateCollision + xTxUnderrunError + xTxCarrierSenseError;

	EMACMACSrcAddrGet(EMAC_BASE, xMacAddr);
	FreeRTOS_GetAddressConfiguration(&xIpAddr, &xNetMask, &xGatewayAddr, &xDNSAddr);

	vAddrToString(cIpBuffer,xIpAddr); vAddrToString(cNetMaskBuffer,xNetMask); vAddrToString(cGWBuffer,xGatewayAddr); vAddrToString(cDNSBuffer,xDNSAddr);

	xRxHeadPointer = HWREG(hdkif->emac_base + EMAC_RXHDP(EMAC_CHANNELNUMBER));
	xTxHeadPointer = HWREG(hdkif->emac_base + EMAC_TXHDP(EMAC_CHANNELNUMBER));
	sprintf((char *)pcWriteBuffer,"EMAC\tHW addr: %02X:%02X:%02X:%02X:%02X:%02X\r\n\tInet:%s Mask:%s\r\n\tGW:%s DNS:%s\r\n\tRX packets:%u errors:%u overruns:%u filtered:%u\r\n\tTX packets:%u errors:%u collisions:%u carrier:%u\r\n\tRX bytes:%u TX bytes:%u\r\n\tRXHP:%p TXHP:%p\n\r",\
			xMacAddr[5],xMacAddr[4],xMacAddr[3],xMacAddr[2],xMacAddr[1],xMacAddr[0],cIpBuffer,cNetMaskBuffer,cGWBuffer,cDNSBuffer,xRxGoodFrames,xRxSumErrors,xRxDmaOverruns,xRxFilteredFrames,xTxGoodFrames,xTxSumErrors,xTxCollisionFrames,xTxCarrierSenseError,xRxOctetFrames,xTxOctetFrames,xRxHeadPointer,xTxHeadPointer);

	return xReturnValue;
}


void vAddrToString(char * pcBuffer, uint32_t xAddress)
{
	sprintf(pcBuffer,"%d.%d.%d.%d",(xAddress & 0xff000000)>>24, (xAddress & 0x00ff0000)>>16, (xAddress & 0x0000ff00)>>8, (xAddress & 0x000000ff));
}

/*-----------------------------------------------------------*/
portBASE_TYPE xResetCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString )
{
	systemREG1->SYSECR |= 0x00008000;
	return pdFALSE;
}

BaseType_t xPingCommand( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString )
	{
	char * pcParameter;
	BaseType_t lParameterStringLength, xReturn;
	uint32_t ulIPAddress, ulBytesToPing;
	//const uint32_t ulDefaultBytesToPing = 22UL;
	const uint32_t ulDefaultBytesToPing = 8UL;
	char cBuffer[ 16 ];

		/* Remove compile time warnings about unused parameters, and check the
		write buffer is not NULL.  NOTE - for simplicity, this example assumes the
		write buffer length is adequate, so does not check for buffer overflows. */
		( void ) pcCommandString;
		configASSERT( pcWriteBuffer );

		/* Start with an empty string. */
		pcWriteBuffer[ 0 ] = 0x00;

		/* Obtain the number of bytes to ping. */
		pcParameter = ( char * ) FreeRTOS_CLIGetParameter
								(
									pcCommandString,		/* The command string itself. */
									2,						/* Return the second parameter. */
									&lParameterStringLength	/* Store the parameter string length. */
								);

		if( pcParameter == NULL )
		{
			/* The number of bytes was not specified, so default it. */
			ulBytesToPing = ulDefaultBytesToPing;
		}
		else
		{
			ulBytesToPing = atol( pcParameter );
		}

		/* Obtain the IP address string. */
		pcParameter = ( char * ) FreeRTOS_CLIGetParameter
								(
									pcCommandString,		/* The command string itself. */
									1,						/* Return the first parameter. */
									&lParameterStringLength	/* Store the parameter string length. */
								);

		/* Sanity check something was returned. */
		configASSERT( pcParameter );

		/* Attempt to obtain the IP address.   If the first character is not a
		digit, assume the host name has been passed in. */
		if( ( *pcParameter >= '0' ) && ( *pcParameter <= '9' ) )
		{
			ulIPAddress = FreeRTOS_inet_addr( pcParameter );
		}
		else
		{
			/* Terminate the host name. */
			pcParameter[ lParameterStringLength ] = 0x00;

			/* Attempt to resolve host. */
			ulIPAddress = FreeRTOS_gethostbyname( pcParameter );
		}

		/* Convert IP address, which may have come from a DNS lookup, to string. */
		FreeRTOS_inet_ntoa( ulIPAddress, cBuffer );

		if( ulIPAddress != 0 )
		{
			xReturn = FreeRTOS_SendPingRequest( ulIPAddress, ( uint16_t ) ulBytesToPing, portMAX_DELAY );
		}
		else
		{
			xReturn = pdFALSE;
		}

		if( xReturn == pdFALSE )
		{
			snprintf( pcWriteBuffer, xWriteBufferLen, "%s", "Could not send ping request\r\n" );
		}
		else
		{
			snprintf( pcWriteBuffer, xWriteBufferLen, "Ping sent to %s with identifier %d\r\n", cBuffer, xReturn );
		}

		return pdFALSE;
	}
	/*-----------------------------------------------------------*/

BaseType_t xNetStatCommand( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString )
	{
	( void ) pcWriteBuffer;
	( void ) xWriteBufferLen;
	( void ) pcCommandString;

	FreeRTOS_netstat();
	snprintf( pcWriteBuffer, xWriteBufferLen, "FreeRTOS_netstat() called - output uses FreeRTOS_printf\r\n" );
	return pdFALSE;
	}
