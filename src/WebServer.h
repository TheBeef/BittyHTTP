/*******************************************************************************
 * FILENAME: WebServer.h
 * 
 * PROJECT:
 *    Bitty HTTP
 *
 * FILE DESCRIPTION:
 *    This is the web server's main .h file.  You need to copy this file to
 *    your project.
 *
 * COPYRIGHT:
 *    Copyright (c) 2019 Paul Hutchinson
 *
 *    Permission is hereby granted, free of charge, to any person obtaining a copy
 *    of this software and associated documentation files (the "Software"), to deal
 *    in the Software without restriction, including without limitation the rights
 *    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *    copies of the Software, and to permit persons to whom the Software is
 *    furnished to do so, subject to the following conditions:
 *    
 *    The above copyright notice and this permission notice shall be included in all
 *    copies or substantial portions of the Software.
 *    
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *    SOFTWARE.
 *
 *******************************************************************************/
#ifndef __WEBSERVER_H_
#define __WEBSERVER_H_

/***  HEADER FILES TO INCLUDE          ***/
#include "SocketsCon.h"
#include "Options.h"
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

/***  DEFINES                          ***/

/***  MACROS                           ***/

/***  TYPE DEFINITIONS                 ***/
typedef enum
{
    e_ReplyStatus_Ok,                           // 200
    e_ReplyStatus_MovedPerm,                    // 301
    e_ReplyStatus_NotModified,                  // 304
    e_ReplyStatus_TmpRedirect,                  // 307
    e_ReplyStatus_PermRedirect,                 // 308
    e_ReplyStatus_BadRequest,                   // 400
    e_ReplyStatus_Forbidden,                    // 403
    e_ReplyStatus_NotFound,                     // 404
    e_ReplyStatus_MethodNotAllowed,             // 405
    e_ReplyStatus_URITooLong,                   // 414
    e_ReplyStatus_RequestHeaderFieldsTooLarge,  // 431
    e_ReplyStatus_InternalServerError,          // 500
    e_ReplyStatus_NotImplemented,               // 501
    e_ReplyStatus_HTTPVersionNotSupported,      // 505
    e_ReplyStatus_InsufficientStorage,          // 507
    e_ReplyStatusMAX
} e_ReplyStatusType;

typedef enum
{
    e_WebServerState_Closed,
    e_WebServerState_Request,
    e_WebServerState_Headers,
    e_WebServerState_Body,
    e_WebServerState_Response,
    e_WebServerStateMAX
} e_WebServerStateType;

typedef enum
{
    e_ReqType_Get,
    e_ReqType_Post,
    e_ReqTypeMAX
} e_ReqTypeType;

typedef enum
{
    e_EncType_URLencoded,
    e_EncType_FormData,
    e_EncType_Unknown,
    e_EncTypeMAX
} e_EncTypeType;

typedef enum
{
    e_POSTMetaData_Filename,
    e_POSTMetaData_ContentType,
} e_POSTMetaDataType;

struct WSPageProp
{
    bool DynamicFile;
    const char **Cookies;
    const char **Gets;
    const char **Posts;
    const char **FilePosts;
    uintptr_t FileID;
};

typedef enum
{
    e_WSPostState_GettingKey,
    e_WSPostState_GettingValue,
    e_WSPostState_Error,
    e_WSPostState_FormData_First,
    e_WSPostState_FormData_BoundarySearch,
    e_WSPostState_FormData_Header,
    e_WSPostState_FormData_Data,
    e_WSPostStateMAX
} e_WSPostStateType;

typedef uint32_t t_ElapsedTime;   // Time to be used for elapsed time

struct WebServer
{
    struct WebServerInstance *Inst;
    e_WebServerStateType State;
    struct SocketCon Con;
    int LineBuffPos;
    char LineBuff[WS_LINE_BUFFER_SIZE];
    e_ReqTypeType Req;
    e_EncTypeType EncType;
    e_ReplyStatusType ReplyStatus;
    bool UserSetReplyStatus;
    bool WriteStarted;
    bool WriteChunked;
    bool ReplyStarted;
    struct WSPageProp PageProp;
    t_ElapsedTime LastReadTime;
    uint32_t BodySize;
    e_WSPostStateType PostState;
    char *PostWritePos;
    char *PostEndOfStorage;
    int PostBoundaryPos;            // How many bytes of the multipart/form-data delimiter we have matched
    bool PostVarIsFile;             // Is the multipart/form-data var we are reading in the FilePosts[] list
    unsigned long PostFileOffset;   // The number of bytes we have already sent to FS_POSTGetFile()
    char ArgsStorage[WS_OPT_ARG_MEMORY_SIZE];
    char POSTBoundaryStr[WS_POST_BOUNDARY_SIZE];
};

struct WebServerInstance
{
    struct SocketCon ListeningSocket;
    uint16_t Port;
    struct WebServer WebServers[WS_OPT_MAX_CONNECTIONS];
    bool (*GetFileProperties)(const char *Filename,struct WSPageProp *PageProp);
    void (*SendFile)(struct WebServer *Web,uintptr_t FileID);
    bool (*POSTGetFile)(struct WebServer *Web,uintptr_t FileID,uint8_t *ChunkData,unsigned long ChunkOffset,unsigned long ChunkDataSize);
    void (*POSTGetFileMetadata)(struct WebServer *Web,uintptr_t FileID,e_POSTMetaDataType Meta,const char *Metadata);
};

/***  CLASS DEFINITIONS                ***/

/***  GLOBAL VARIABLE DEFINITIONS      ***/

/***  EXTERNAL FUNCTION PROTOTYPES     ***/
void WS_Init(struct WebServerInstance *Inst,uint16_t Port,
        bool (*GetFilePropertiesCB)(const char *Filename,struct WSPageProp *PageProp),
        void (*SendFileCB)(struct WebServer *Web,uintptr_t FileID),
        bool (*POSTGetFileCB)(struct WebServer *Web,uintptr_t FileID,uint8_t *ChunkData,unsigned long ChunkOffset,unsigned long ChunkDataSize),
        void (*POSTGetFileMetadataCB)(struct WebServer *Web,uintptr_t FileID,e_POSTMetaDataType Meta,const char *Metadata));
void WS_Shutdown(struct WebServerInstance *Inst);
bool WS_Start(struct WebServerInstance *Inst);
void WS_Tick(struct WebServerInstance *Inst);

void WS_WriteWhole(struct WebServer *Web,const char *Buffer,int Len);
void WS_WriteWholeStr(struct WebServer *Web,const char *Buffer);
void WS_WriteChunk(struct WebServer *Web,const char *Buffer,int Len);
void WS_WriteChunkStr(struct WebServer *Web,const char *Buffer);
bool WS_Header(struct WebServer *Web,const char *Header);
bool WS_Location(struct WebServer *Web,const char *NewURL);
bool WS_SetHTTPStatusCode(struct WebServer *Web,e_ReplyStatusType Code);

const char *WS_GET(struct WebServer *Web,const char *Arg);
const char *WS_COOKIE(struct WebServer *Web,const char *Arg);
const char *WS_POST(struct WebServer *Web,const char *Arg);
bool WS_COOKIECopy(struct WebServer *Web,const char *Arg,char *Dest,int MaxDest);
bool WS_GETCopy(struct WebServer *Web,const char *Arg,char *Dest,int MaxDest);
bool WS_POSTCopy(struct WebServer *Web,const char *Arg,char *Dest,int MaxDest);

bool WS_SetCookie(struct WebServer *Web,const char *Name,const char *Value,
        time_t Expire,const char *Path,const char *Domain,bool Secure,
        bool HttpOnly);
bool WS_URLEncode(const char *Value,char *OutputBuffer,int MaxLen);
bool WS_URLDecode(const char *Value,char *Decoded,int MaxLen);
char *WS_URLDecodeInPlace(char *Value);
int WS_GetOSSocketHandles(struct WebServerInstance *Inst,t_ConSocketHandle *Handles);

t_ElapsedTime ReadElapsedClock(void);

#endif
