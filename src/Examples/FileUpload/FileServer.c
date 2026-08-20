/*******************************************************************************
 * FILENAME: FileServer.c
 *
 * PROJECT:
 *    Bitty HTTP
 *
 * FILE DESCRIPTION:
 *    POST file upload example
 *
 * COPYRIGHT:
 *    Copyright (c) 2026 Paul Hutchinson
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
 ******************************************************************************/

/*** HEADER FILES TO INCLUDE  ***/
#include "../../WebServer.h"
#include "../../main.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

/*** DEFINES                  ***/

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/
const char *FilesArgs[]=
{
    "Upload",
    NULL
};

struct FileInfo
{
    const char *Filename;   // With Path
    bool Dynamic;
    const char **Cookies;
    const char **Gets;
    const char **Posts;
    const char **FilePosts;
    uint8_t *FileStorage;
    uint32_t FileStorageSize;
    bool FileRejected;
    void (*WriteFile)(struct WebServer *Web);
};

/*** FUNCTION PROTOTYPES      ***/
void File_Root(struct WebServer *Web);
void File_Display(struct WebServer *Web);
void File_SomeStyle(struct WebServer *Web);
void File_Quit(struct WebServer *Web);

/*** VARIABLE DEFINITIONS     ***/
uint8_t m_FileContents[2000];
struct FileInfo m_Files[]=
{
    /* Filename, Dynamic, Cookies, Gets, Posts, Callback */
    {"/",false,NULL,NULL,NULL,NULL,NULL,0,false,File_Root},
    {"/Display.html",true,NULL,NULL,NULL,FilesArgs,m_FileContents,sizeof(m_FileContents),false,File_Display},
    {"/SomeStyle.css",false,NULL,NULL,NULL,NULL,NULL,0,false,File_SomeStyle},
    {"/quit.html",true,NULL,NULL,NULL,NULL,NULL,0,false,File_Quit},
};

/*******************************************************************************
 * NAME:
 *    FS_GetFileProperties
 *
 * SYNOPSIS:
 *    bool FS_GetFileProperties(struct WebServer *Web,const char *Filename,
 *          struct WSPageProp *PageProp);
 *
 * PARAMETERS:
 *    Web [I] -- The web context for this web connection.
 *    Filename [I] -- The filename from the URL that is being requested.
 *    PageProp [O] -- This is filled in with info about the page.
 *                      FileID -- The ID of the page.  This has no meaning
 *                                to the web server it is just passed back
 *                                to FS_SendFile().  It can hold a pointer.
 *                      DynamicFile -- If this is true then the file will
 *                                     no be cached.  false will set the
 *                                     ETAG to 'DOCVER' where it will not
 *                                     resent to the browser until 'DOCVER'
 *                                     changes.
 *                      Cookies -- A pointer to the list of cookies that this
 *                                 page accepts.
 *                      Gets -- A pointer to the list of GET vars that this
 *                              page accepts.
 *                      Posts -- A pointer to the list of POST vars that this
 *                               page accepts.
 *
 * FUNCTION:
 *    This function is called when a new request comes in for a file.  This
 *    is before the headers for this request have been processed and the
 *    web server is not yet ready to send a reply.
 *
 *    The web server does need to know if this is a valid file and some info
 *    about the file.  That is what this function provides.
 *
 * RETURNS:
 *    true -- File known and can be sent
 *    false -- File is known.  Will produce a 404 reply.
 *
 * SEE ALSO:
 *    FS_SendFile()
 ******************************************************************************/
bool FS_GetFileProperties(struct WebServer *Web,const char *Filename,
        struct WSPageProp *PageProp)
{
    int r;

    for(r=0;r<sizeof(m_Files)/sizeof(struct FileInfo);r++)
    {
        if(strcmp(Filename,m_Files[r].Filename)==0)
        {
            PageProp->FileID=(uintptr_t)&m_Files[r];
            PageProp->DynamicFile=m_Files[r].Dynamic;
            PageProp->Cookies=m_Files[r].Cookies;
            PageProp->Gets=m_Files[r].Gets;
            PageProp->Posts=m_Files[r].Posts;
            PageProp->FilePosts=m_Files[r].FilePosts;

            /* Clear the contents before we try to send a reply (or collect
               any contents) */
            if(m_Files[r].FileStorage!=NULL)
                *m_Files[r].FileStorage=0;
            m_Files[r].FileRejected=false;

            return true;
        }
    }
    return false;
}

/*******************************************************************************
 * NAME:
 *    FS_SendFile
 *
 * SYNOPSIS:
 *    void FS_SendFile(struct WebServer *Web,uintptr_t FileID);
 *
 * PARAMETERS:
 *    Web [I] -- The web context for this web connection.
 *    FileID [I] -- The number that was setup in FS_GetFileProperties().
 *                  This has no meaning to the web server and is just passed
 *                  to this function.  It can be a pointer to some object
 *                  of your defining.
 *
 * FUNCTION:
 *    This function is called from the web server when it is time to send the
 *    contents of a "file".  You may also set headers using WS_Header() as
 *    long as you haven't sent anything else yet.
 *
 * RETURNS:
 *    NONE
 *
 * SEE ALSO:
 *    WS_Header(), WS_WriteWhole(), WS_WriteChunk(), WS_GET(), WS_COOKIE(),
 *    WS_POST(), WS_SetCookie()
 ******************************************************************************/
void FS_SendFile(struct WebServer *Web,uintptr_t FileID)
{
    struct FileInfo *File=(struct FileInfo *)FileID;

    /* Not needed but I always check... */
    if(File==NULL)
        return;

    File->WriteFile(Web);
}

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
 *    FileID [I] -- The number that was setup in GetFilePropertiesCB().
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
 *    If you do not support file uploads you can set this to NULL.
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
 *    SendFileCB()
 ******************************************************************************/
bool FS_POSTGetFile(struct WebServer *Web,uintptr_t FileID,
        uint8_t *ChunkData,unsigned long ChunkOffset,
        unsigned long ChunkDataSize)
{
    struct FileInfo *File=(struct FileInfo *)FileID;

    if(File->FileRejected)
    {
        WS_SetHTTPStatusCode(Web,e_ReplyStatus_InternalServerError);
        WS_WriteWholeStr(Web,"500 Internal Server Error");
        return false;
    }

    if(ChunkDataSize==0)
    {
        /* Done, make it a string */
        File->FileStorage[ChunkOffset]=0;
        return true;
    }

    if(ChunkOffset+ChunkDataSize>=File->FileStorageSize)
    {
        WS_SetHTTPStatusCode(Web,e_ReplyStatus_InsufficientStorage);
        WS_WriteWholeStr(Web,"507 Insufficient Storage");
        return false;
    }

    memcpy(&File->FileStorage[ChunkOffset],ChunkData,ChunkDataSize);

    return true;
}

/*******************************************************************************
 * NAME:
 *    FS_POSTGetFileMetadata
 *
 * SYNOPSIS:
 *    void FS_POSTGetFileMetadata(struct WebServer *Web,uintptr_t FileID,
 *              e_POSTMetaDataType Meta,const char *Metadata);
 *
 * PARAMETERS:
 *    Web [I] -- The web context for this web connection.
 *    FileID [I] -- The number that was setup in GetFilePropertiesCB().
 *                  This has no meaning to the web server and is just passed
 *                  to this function.  It can be a pointer to some object
 *                  of your defining.
 *    Meta [I] -- What type of metadata did we find.  Supported values:
 *                      e_POSTMetaData_Filename -- The filename of the
 *                          uploaded file
 *                      e_POSTMetaData_ContentType -- The type of content.
 *                          This will be a string from the Content-Type:
 *                          header for this file.
 *    Metadata [I] -- A pointer to the string with the metadata in it.
 *
 * FUNCTION:
 *    This function is called when uploading a file with
 *    enctype="multipart/form-data".  It lets you know info about the
 *    file that is about to be sent to POSTGetFileCB().  Depending on what
 *    the web browser send you may get all these metadata's or none of them.
 *
 *    If you do not handle file uploads or don't care about the metadata then
 *    this can be set to NULL to ignore.
 *
 * RETURNS:
 *    NONE
 *
 * SEE ALSO:
 *    
 ******************************************************************************/
void FS_POSTGetFileMetadata(struct WebServer *Web,uintptr_t FileID,
        e_POSTMetaDataType Meta,const char *Metadata)
{
    struct FileInfo *File=(struct FileInfo *)FileID;

    /* We only let them upload text files.  We use strstr() because the
       line may include other text (like the charset), really we should
       process the line correctly looking for ';' and such, but this is
       "easy" */
    if(Meta==e_POSTMetaData_ContentType && strstr(Metadata,"text/plain")==0)
    {
        File->FileRejected=true;
    }
}

////////////////////////////////////////////////////////////////////////////////
const char QuitHTML[]=
"<!DOCTYPE html>"
"<html>"
"<head>"
    "<title>Bitty HTTP Example - Quit</title>"
    "<link rel='stylesheet' href='/SomeStyle.css'>"
"</head>"
"<body>"
    "<div id='top'>Bitty HTTP Example</div>"
    "<div id='content'>"
        "<br/>"
        "Bye bye<br/>"
        "<br/>"
        "<a href='/'>HOME</a>"
        "<br/>"
    "</div>"
"<div id='bottom'></div>"
"</body>"
"</html>";
void File_Quit(struct WebServer *Web)
{
    WS_WriteWhole(Web,QuitHTML,sizeof(QuitHTML)-1);

    g_Quit=true;
}

////////////////////////////////////////////////////////////////////////////////
const char CSS[]=
"div#top"
"{"
    "height:50px;"
    "width:100%;"
    "background-color:#679509;"
    "font-size:1.5em;"
    "line-height:50px;"
    "padding-left:15px;"
    "color:white;"
    "text-shadow:#4F4F4F 2px 2px;"
"}\n"
"div#quitbttn"
"{"
    "position:absolute;"
    "top:23px;"
    "right:30px;"
"}\n"
"div#quitbttn a"
"{"
    "color:white;"
    "text-decoration:none"
"}\n"
"div#quitbttn a:hover"
"{"
    "text-decoration:underline"
"}\n"
"div#bottom"
"{"
    "position:absolute;"
    "bottom:0px;"
    "left:0px;"
    "height:50px;"
    "width:100%;"
    "background-color:#679509;"
"}\n"
"div#content"
"{"
    "background-color:#f0f0f0;"
    "color:#6A6A6A;"
"}\n";
void File_SomeStyle(struct WebServer *Web)
{
    WS_WriteWhole(Web,CSS,sizeof(CSS)-1);
}

////////////////////////////////////////////////////////////////////////////////

const char RootHTML[]=
"<!DOCTYPE html>"
"<html>"
"<head>"
    "<title>Bitty HTTP - Root</title>"
    "<link rel='stylesheet' href='/SomeStyle.css'>"
"</head>"
"<body>"
    "<div id='top'>Bitty HTTP Example - Root</div>"
    "<div id='quitbttn'><a href='/quit.html'>QUIT</a></div>"
    "<div id='content'>"
        "POST file upload example<br/>"
        "<br/>"
        "<form action='/Display.html' method='POST' enctype='multipart/form-data'>"
        "Select your file:<input name='Upload' type='File'></input><br/>"
        "<input type='submit'></input>"
        "</form>"
        "<br/>"
    "</div>"
"<div id='bottom'></div>"
"</body>"
"</html>";

void File_Root(struct WebServer *Web)
{
    WS_WriteWhole(Web,RootHTML,sizeof(RootHTML)-1);
}

////////////////////////////////////////////////////////////////////////////////
const char DisplayHTML_Start[]=
"<!DOCTYPE html>"
"<html>"
"<head>"
    "<title>Bitty HTTP - Root</title>"
    "<link rel='stylesheet' href='/SomeStyle.css'>"
"</head>"
"<body>"
    "<div id='top'>Bitty HTTP Example - Root</div>"
    "<div id='quitbttn'><a href='/quit.html'>QUIT</a></div>"
    "<div id='content'>";
const char DisplayHTML_End[]=
    "</div>"
"<div id='bottom'></div>"
"</body>"
"</html>";

void File_Display(struct WebServer *Web)
{
    char buff[100];
    const char *Name;

    WS_WriteChunk(Web,DisplayHTML_Start,sizeof(DisplayHTML_Start)-1);

    WS_WriteChunkStr(Web,"Contents of file uploaded:");
    WS_WriteChunkStr(Web,"<hr/><pre>");
    WS_WriteChunkStr(Web,m_FileContents);
    WS_WriteChunkStr(Web,"</pre><hr/>");
    WS_WriteChunkStr(Web,"NOTE: You should NEVER just echo back what was sent in on a real server");

    WS_WriteChunk(Web,"<br/><br/><a href='/'>Try again</a>",35);
    WS_WriteChunk(Web,"<br/>",5);

    WS_WriteChunk(Web,DisplayHTML_End,sizeof(DisplayHTML_End)-1);
}
