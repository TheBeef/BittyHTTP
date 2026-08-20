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

/***  CLASS DEFINITIONS                ***/

/***  GLOBAL VARIABLE DEFINITIONS      ***/

/***  EXTERNAL FUNCTION PROTOTYPES     ***/
void WS_Init(void);
void WS_Shutdown(void);
bool WS_Start(uint16_t Port);
void WS_Tick(void);
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
int WS_GetOSSocketHandles(t_ConSocketHandle *Handles);

/* Web server calls these */
bool FS_GetFileProperties(const char *Filename,struct WSPageProp *PageProp);
void FS_SendFile(struct WebServer *Web,uintptr_t FileID);

/*******************************************************************************
 * NAME:
 *    FS_POSTGetFile
 *
 * SYNOPSIS:
 *    bool FS_POSTGetFile(struct WebServer *Web,uintptr_t FileID,
 *              uint8_t *ChunkData,unsigned long ChunkOffset,
 *              unsigned long ChunkDataSize);
 *
 * PARAMETERS:
 *    Web [I] -- The web context for this web connection.
 *    FileID [I] -- The number that was setup in FS_GetFileProperties().
 *                  This has no meaning to the web server and is just passed
 *                  to this function.  It can be a pointer to some object
 *                  of your defining.
 *    ChunkData [I] -- A buffer with the file data in it.  This will not
 *          have all the data in it just some of it (see below for details)
 *    ChunkOffset [I] -- The number of bytes have already been send before
 *          we got to this call.
 *    ChunkDataSize [I] -- The number of bytes of data available 'ChunkData'.
 *
 * FUNCTION:
 *    This function is called when handling a POST request with
 *    enctype="multipart/form-data" set.
 *
 *    When this is call we have found a POST var in the WSPageProp.FilePosts
 *    list and we have the some data for that chunk.  This will be called
 *    many times for the same file as new data comes in the connection.
 *    The data will always be in order (you do not have to re-assemble the
 *    data, you just have to handle it coming a bit at a time).
 *
 *    When the whole file has been uploaded then this will be called one last
 *    time with a 'ChunkDataSize' of 0.  This can be used to close the file.
 *
 * RETURNS:
 *    true -- Everything is good
 *    false -- There was an error.  You should call WS_SetHTTPStatusCode()
 *             to set the error code.
 *
 * EXAMPLE:
 *    So for a file that has:
 *      abcdefghijklmnopqrstuvwxyz
 *    You might get the following calls:
 *      FS_POSTGetFile(web,0,"abc",0,3);
 *      FS_POSTGetFile(web,0,"defghijklmnop",3,13);
 *      FS_POSTGetFile(web,0,"qrstuvwxyz",16,10);
 *      FS_POSTGetFile(web,0,"",26,0);
 *
 * SEE ALSO:
 *    FS_SendFile()
 ******************************************************************************/
bool FS_POSTGetFile(struct WebServer *Web,uintptr_t FileID,uint8_t *ChunkData,
        unsigned long ChunkOffset,unsigned long ChunkDataSize);

void FS_POSTGetFileMetadata(struct WebServer *Web,uintptr_t FileID,
        e_POSTMetaDataType Meta,const char *Metadata);

t_ElapsedTime ReadElapsedClock(void);

#endif
