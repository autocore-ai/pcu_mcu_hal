/*
 * cli_commands.h
 *
 *  Created on: 2015 jún. 26
 *      Author: loszi
 */

#ifndef CLI_COMMANDS_H_
#define CLI_COMMANDS_H_

#include "FreeRTOS.h"
#include "FreeRTOS_CLI.h"
#include "sys_main.h"


void vAddrToString(char * pcBuffer, uint32_t xAddress);

#if ( configGENERATE_RUN_TIME_STATS == 1 )
portBASE_TYPE xTaskStatsCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString );
portBASE_TYPE xRunTimeStatsCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString );

/* Structure that defines the "top" command line command. */
static const CLI_Command_Definition_t xRunTimeStats =
{
	( const char *) "top",
	( const char *) "\r\ntop (top cpu tasks/processes):\r\n Displays a table showing how much processing time each FreeRTOS task has used.\r\n",
	( pdCOMMAND_LINE_CALLBACK ) xRunTimeStatsCommand,
	0
};

/* Structure that defines the "ps" command line command. */
static const CLI_Command_Definition_t xTaskStats =
{
	( const char *) "ps",
	( const char *) "\r\nps (process status):\r\n Displays a table showing the state of each FreeRTOS task/process.\r\n",
	( pdCOMMAND_LINE_CALLBACK ) xTaskStatsCommand,
	0
};
#endif

portBASE_TYPE xResetCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString );
/* Structure that defines the "reset" command line command. */
static const CLI_Command_Definition_t xReset =
{
	( const char *) "reset",
	( const char *) "\r\nreset:\r\n Performs warm reset.\r\n",
	( pdCOMMAND_LINE_CALLBACK ) xResetCommand,
	0
};

portBASE_TYPE xMemTestCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString );
/* Structure that defines the "memtest" command line command. */
static const CLI_Command_Definition_t xMemTest =
{
	( const char *) "memtest",
	( const char *) "\r\nmemtest:\r\n Performs External Memory InterFace (EMIF) connected memory test.\r\n",
	( pdCOMMAND_LINE_CALLBACK ) xMemTestCommand,
	0
};

portBASE_TYPE xEmacStatCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString );
/* Structure that defines the "emacstat" command line command. */
static const CLI_Command_Definition_t xEmacStat =
{
	( const char *) "emacstat",
	( const char *) "\r\nemacstat:\r\n Display network interface related statistics.\r\n",
	( pdCOMMAND_LINE_CALLBACK ) xEmacStatCommand,
	0
};

BaseType_t xPingCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);
/* Structure that defines the "ping" command line command. */
static const CLI_Command_Definition_t xPing =
{
	( const char *) "ping",
	( const char *) "\r\nping <ipaddress> <optional:bytes to send>:\r\n for example, ping 192.168.0.3 8, or ping www.example.com\r\n",
	( pdCOMMAND_LINE_CALLBACK ) xPingCommand,
	-1
};

BaseType_t xNetStatCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);
/* Structure that defines the "netstat" command line command. */
static const CLI_Command_Definition_t xNetStat =
{
	"netstat",
	"\r\nnetstat:\r\n Calls FreeRTOS_netstat()\r\n",
	( pdCOMMAND_LINE_CALLBACK ) xNetStatCommand,
	0 /* No parameters are expected. */
};
#endif /* CLI_COMMANDS_H_ */
