/****************************************************************************
This program is an unpublished work fully protected by the United States
Copyright laws and is considered a trade secret belonging to Cheyenne
Software, Inc.

Copyright (C) 1990-1993  Cheyenne Software, Inc.

 Program Name:  Agent Communication Interface
      Version:  1.0
 Version Date:  April 5, 1994
****************************************************************************/

#ifndef _ACI_H
#define _ACI_H

/*
 *      Constants
 */

// Agent Workstation Type
#define _AWST_IPX       0

// Agent Type
#define _AT_DOS         1
#define _AT_OS2_HPFS    2
#define _AT_WIN         3
#define _AT_OS2_FAT     4
#define _AT_NT_FAT      6
#define _AT_NT_HPFS     7
#define _AT_NT_NTFS     8

// Agent Command Codes
#define _ACC_RCV_OK             0
#define _ACC_OK                 0
#define _ACC_NO                 1
#define _ACC_ABORT              2
#define _ACC_EOJ                3
#define _ACC_REQ_OK             4
#define _ACC_REQ_REJ            5
#define _ACC_BOF                6
#define _ACC_MOF                7
#define _ACC_EOF                8
#define _ACC_EOD                9
#define _ACC_YES                10
#define _ACC_ASK_DRIVE          10
#define _ACC_ASK_DIR            11
#define _ACC_ASK_FILE           12
#define _ACC_MOEA               14
#define _ACC_EOEA               15
#define _ACC_LONG_NAME          16

#define _ACC_MKDIR              20
#define _ACC_MKDIR2             21
#define _ACC_OPENFILE           22
#define _ACC_OPENFILE2          23
#define _ACC_OS2FIND            24
#define _ACC_CLEAR_ARCHIVE      25
#define _ACC_FILEPATH           26
#define _ACC_NTFIND             28    // NT

#define _ACC_MOSD               30    // NT
#define _ACC_EOSD               31    // NT
#define _ACC_MOAD               32    // NT
#define _ACC_EOAD               33    // NT

#define _ACC_ARC_ABORT          100
#define _ACC_CANT_FINDFIRST     101
#define _ACC_OPEN_FAIL          102
#define _ACC_READ_ERR           103
#define _ACC_INVALID_PATH       104
#define _ACC_EMPTY_SOURCE       105
#define _ACC_RES_CREAT_FAIL     106
#define _ACC_RES_ATTRIB_FAIL    107
#define _ACC_RES_WRITE_FAIL     108
#define _ACC_RES_DATE_FAIL      109
#define _ACC_INVALID_FILE       110
#define _ACC_SKIP_FILE          111
#define _ACC_SHARE_VIOLATION    120

// #define FILE_CHANGED            27  /* may have conflict with FSTAT */
// #define AGENT_BUSY              50
// #define MAX_CONNECTION          51

// Agent Op Codes 
#define _AOC_WSBACKUP           0
#define _AOC_WSARCHIVE          0
#define _AOC_WSRESTORE          1
#define _AOC_WSCOMPARE          2
#define _AOC_WSEXECUTE          66
#define _AOC_WSOS2QUERY         67
#define _AOC_MOACL              68
#define _AOC_EOACL              69
#define _AOC_WSCOMMAND          70
#define _AOC_MOFL               71
#define _AOC_ENDFL              72

// Agent Status
#define _AS_LAST_PACKET            0
#define _AS_MORE_PACKET_TO_COME    1

// Agent Flags
#define _AF_ARCSERVE_50        0x01
#define _AF_RESTORE_SKIP       0x02          // restore
#define _AF_RESTORE_OVERWRITE  0x04          // restore
#define _AF_RESTORE_RENAME     0x08          // restore
#define _AF_RESTORE_SKIP_NEWER 0x10          // restore
#define _AF_LAST_CONNECTION    0x20
#define _AF_CLEAR_ARCHIVE_50   0x80          // backup
#define _AF_OS2FLAG            0x20

/*
 *      Data Types
 */

#ifndef _ACI_INTERNAL                   // For ACI Driver Only

typedef struct  _ADC {                  // Agent Device Context
  UCHAR         reserved[32];
} ADC, *PADC;

#endif

typedef struct  _WS_HEADER {
  UCHAR         command;
  UCHAR         device;
  USHORT        status;
  USHORT        blocks;         // # blocks involves in this transaction
  USHORT        offset;         // Current Block Offset
} WS_HEADER;
typedef WS_HEADER *PWS_HEADER;

typedef struct  _WS_ACCESS {
  char   rootPath[223];         // DRV:\PATH
  UCHAR  flag;                  // see flag codes definition
  char   password[24];          // Password
  USHORT packetSize;            // Packet Size 512/1024...
  UCHAR  acceptEA;              // 1 => HPFS-aware
  UCHAR  opMode;                // 0/1/2 => Backup/Restore/Compare
} WS_ACCESS;
typedef WS_ACCESS *PWS_ACCESS;

#define _MAX_PACKET_SIZE        4096

typedef struct  _WS_PACKET {
  WS_HEADER     header;
  union         {
    UCHAR       buffer[_MAX_PACKET_SIZE];       // data
    WS_ACCESS   access;                         // access
  }             data;
} WS_PACKET;
typedef WS_PACKET *PWS_PACKET;

typedef struct DOSFILEINFO {
  UCHAR  workArea[21];
  UCHAR  attrib;
  USHORT wr_time;
  USHORT wr_date;
  ULONG  size;
  char   name[13];
} DOSFILEINFO;

/*
 *      Function Prototypes
 */

int     WINAPI  ACIOpen(PADC, ULONG, PUCHAR);
int     WINAPI  ACIClose(PADC);
int     WINAPI  ACIConnect(PADC, ULONG, PUCHAR);
int     WINAPI  ACIListen(PADC);
int     WINAPI  ACIWaitForConnection(PADC, PADC);
int     WINAPI  ACISendData(PADC, PVOID, USHORT);
int     WINAPI  ACIReceiveData(PADC, PVOID, USHORT);
int     WINAPI  ACISendCommand(PADC, UCHAR, UCHAR);
int     WINAPI  ACIReceivePacket(PADC, PWS_PACKET, USHORT);

#endif
