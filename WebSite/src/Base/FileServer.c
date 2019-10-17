/*******************************************************************************
 * FILENAME: FileServer.c
 *
 * PROJECT:
 *    Bitty HTTP
 *
 * FILE DESCRIPTION:
 *    This has the list of files in it and calls to the pages.
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
 ******************************************************************************/

/*** HEADER FILES TO INCLUDE  ***/
#include "Base/FileServer.h"
#include "Base/WebServer.h"
#include "Pages/Pages.h"
#include "Common/CommonCSS.h"
#include "Common/Headers.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

/*** DEFINES                  ***/
#define MAX_DISK_BASED_PATH_LEN             256

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/
typedef enum
{
    e_FileKind_BuiltIn=0,
    e_FileKind_DiskBased,
    e_FileKindMAX
} e_FileKindType;

struct BuiltInFile
{
    const char *Filename;   // With Path
    bool Dynamic;
    const char **Cookies;
    const char **Gets;
    const char **Posts;
    e_PageType PageID;
    void (*WriteFile)(struct WebServer *Web);
};

struct DiskBasedFile
{
    const char *HTMLPath;
    const char *DiskPath;
    bool TextFile;
};

struct FileInfo
{
    e_FileKindType FileKind;
    union
    {
        struct BuiltInFile BuiltIn;
        struct DiskBasedFile DiskBased;
    };
};

/*** FUNCTION PROTOTYPES      ***/
static bool BuildDiskBasedFilename(char *OutputBuff,int MaxBuff,
        const char *ReqFilename,const char *HTMLPath,const char *DiskPath);
void SendDiskFile(struct WebServer *Web,const char *Filename,bool Binary);

/*** VARIABLE DEFINITIONS     ***/
struct FileInfo m_Files[]=
{
    /* e_FileKind_BuiltIn,        Filename, Dynamic, Cookies, Gets, Posts, Callback */
    {e_FileKind_BuiltIn,.BuiltIn={"/",                       false,NULL,NULL,NULL,e_Page_Root,           File_Root}},
    {e_FileKind_BuiltIn,.BuiltIn={"/CommonCSS.css",          false,NULL,NULL,NULL,e_PageMAX,             File_CommonCSS}},
    {e_FileKind_BuiltIn,.BuiltIn={"/About.html",             false,NULL,NULL,NULL,e_Page_About,          File_About}},
    {e_FileKind_BuiltIn,.BuiltIn={"/Download.html",          false,NULL,NULL,NULL,e_Page_Download,       File_Download}},
    {e_FileKind_BuiltIn,.BuiltIn={"/License.html",           false,NULL,NULL,NULL,e_Page_License,        File_License}},
    {e_FileKind_BuiltIn,.BuiltIn={"/FAQ.html",               false,NULL,NULL,NULL,e_Page_FAQ,            File_FAQ}},
    {e_FileKind_BuiltIn,.BuiltIn={"/Links.html",             false,NULL,NULL,NULL,e_Page_Links,          File_Links}},
    {e_FileKind_BuiltIn,.BuiltIn={"/Development.html",       false,NULL,NULL,NULL,e_Page_Development,    File_Development}},
    {e_FileKind_BuiltIn,.BuiltIn={"/AutoDocs.html",          false,NULL,NULL,NULL,e_Page_AutoDocs,       File_AutoDocs}},
    {e_FileKind_BuiltIn,.BuiltIn={"/ReleaseNotes.html",      false,NULL,NULL,NULL,e_Page_ReleaseNotes,   File_ReleaseNotes}},
    {e_FileKind_BuiltIn,.BuiltIn={"/Contact.html",           false,NULL,NULL,NULL,e_Page_Contact,        File_Contact}},
    {e_FileKind_BuiltIn,.BuiltIn={"/StatInfo.dat",           true ,NULL,NULL,NULL,e_Page_Contact,        File_StatInfo}},
    {e_FileKind_BuiltIn,.BuiltIn={"/Doc/TheBasics.html",     false,NULL,NULL,NULL,e_Page_TheBasics,      File_Doc_TheBasics}},
    {e_FileKind_BuiltIn,.BuiltIn={"/Doc/HelloWorld.html",    false,NULL,NULL,NULL,e_Page_HelloWorld,     File_Doc_HelloWorld}},
    {e_FileKind_BuiltIn,.BuiltIn={"/Doc/CSS.html",           false,NULL,NULL,NULL,e_Page_CSS,            File_Doc_CSS}},
    {e_FileKind_BuiltIn,.BuiltIn={"/Doc/Graphics.html",      false,NULL,NULL,NULL,e_Page_Graphics,       File_Doc_Graphics}},
    {e_FileKind_BuiltIn,.BuiltIn={"/Doc/DynamicContent.html",false,NULL,NULL,NULL,e_Page_DynamicContent, File_Doc_DynamicContent}},
    {e_FileKind_BuiltIn,.BuiltIn={"/Doc/GETVars.html",       false,NULL,NULL,NULL,e_Page_GETVars,        File_Doc_GETVars}},
    {e_FileKind_BuiltIn,.BuiltIn={"/Doc/POSTVars.html",      false,NULL,NULL,NULL,e_Page_POSTVars,       File_Doc_POSTVars}},
    {e_FileKind_BuiltIn,.BuiltIn={"/Doc/Cookies.html",       false,NULL,NULL,NULL,e_Page_CookiesVars,    File_Doc_CookiesVars}},
    {e_FileKind_BuiltIn,.BuiltIn={"/Doc/ManualHeaders.html", false,NULL,NULL,NULL,e_Page_Headers,        File_Doc_HeadersVars}},
    {e_FileKind_BuiltIn,.BuiltIn={"/Doc/URLEncoding.html",   false,NULL,NULL,NULL,e_Page_URLEncode,      File_Doc_URLEncodingVars}},
    {e_FileKind_BuiltIn,.BuiltIn={"/Doc/Waiting.html",       false,NULL,NULL,NULL,e_Page_Waiting,        File_Doc_Waiting}},
    {e_FileKind_BuiltIn,.BuiltIn={"/Doc/Error404.html",      false,NULL,NULL,NULL,e_Page_Error404,       File_Doc_Error404}},
    /* e_FileKind_DiskBased,        HTMLPath,DiskPath */
    {e_FileKind_DiskBased,.DiskBased={"/source/","../src/",true}},
    {e_FileKind_DiskBased,.DiskBased={"/Releases/","../Releases/",false}},
};

char m_RequestFilename[WS_LINE_BUFFER_SIZE];

struct PageInfo g_PageInfo[e_PageMAX]=
{
    /* Order must match 'e_PageType' */
    {e_PageMAX,                         "Home"},                // e_Page_Root
    {e_PageMAX,                         "About"},               // e_Page_About
    {e_PageMAX,                         "Download"},            // e_Page_Download
        {e_Page_Download,               "Release Notes"},       // e_Page_ReleaseNotes
    {e_PageMAX,                         "License"},             // e_Page_License
    {e_PageMAX,                         "FAQ"},                 // e_Page_FAQ
    {e_PageMAX,                         "Development"},         // e_Page_Development
        {e_Page_Development,            "AutoDocs"},            // e_Page_AutoDocs
        {e_Page_Development,            "The Basics"},          // e_Page_TheBasics
        {e_Page_Development,            "Hello World"},         // e_Page_HelloWorld
        {e_Page_Development,            "CSS"},                 // e_Page_CSS
        {e_Page_Development,            "Graphics"},            // e_Page_Graphics
        {e_Page_Development,            "Dynamic Content"},     // e_Page_DynamicContent
        {e_Page_Development,            "GET Vars"},            // e_Page_GETVars
        {e_Page_Development,            "POST Vars"},           // e_Page_POSTVars
        {e_Page_Development,            "Cookies"},             // e_Page_CookiesVars
        {e_Page_Development,            "Headers"},             // e_Page_Headers
        {e_Page_Development,            "URL Encode"},          // e_Page_URLEncode
        {e_Page_Development,            "Waiting on Sockets"},  // e_Page_Waiting
        {e_Page_Development,            "404 Errors"},          // e_Page_Error404
    {e_PageMAX,                         "Links"},               // e_Page_Links
    {e_PageMAX,                         "Contact"},             // e_Page_Contact
};

/*******************************************************************************
 * NAME:
 *    FS_GetFileProperties
 *
 * SYNOPSIS:
 *    bool FS_GetFileProperties(const char *Filename,
 *          struct WSPageProp *PageProp);
 *
 * PARAMETERS:
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
bool FS_GetFileProperties(const char *Filename,struct WSPageProp *PageProp)
{
    int r;
    int l;
    char FilePath[MAX_DISK_BASED_PATH_LEN];

    strncpy(m_RequestFilename,Filename,sizeof(m_RequestFilename)-1);
    m_RequestFilename[sizeof(m_RequestFilename)-1]=0;

    for(r=0;r<sizeof(m_Files)/sizeof(struct FileInfo);r++)
    {
        switch(m_Files[r].FileKind)
        {
            case e_FileKind_BuiltIn:
                if(strcmp(Filename,m_Files[r].BuiltIn.Filename)==0)
                {
                    PageProp->FileID=(uintptr_t)&m_Files[r];
                    PageProp->DynamicFile=m_Files[r].BuiltIn.Dynamic;
                    PageProp->Cookies=m_Files[r].BuiltIn.Cookies;
                    PageProp->Gets=m_Files[r].BuiltIn.Gets;
                    PageProp->Posts=m_Files[r].BuiltIn.Posts;
                    return true;
                }
            break;
            case e_FileKind_DiskBased:
                l=strlen(m_Files[r].DiskBased.HTMLPath);
                if(strncmp(Filename,m_Files[r].DiskBased.HTMLPath,l)==0)
                {
                    /* Check that this file actually exists */
                    if(!BuildDiskBasedFilename(FilePath,MAX_DISK_BASED_PATH_LEN,
                            Filename,m_Files[r].DiskBased.HTMLPath,
                            m_Files[r].DiskBased.DiskPath))
                    {
                        /* Buffer overflow, just say the page doesn't exist */
                        return false;
                    }
                    if(access(FilePath,F_OK)!=0)
                    {
                        /* File does not exist */
                        return false;
                    }
                    PageProp->FileID=(uintptr_t)&m_Files[r];
                    PageProp->DynamicFile=false;
                    PageProp->Cookies=NULL;
                    PageProp->Gets=NULL;
                    PageProp->Posts=NULL;
                    return true;
                }
            break;
            case e_FileKindMAX:
            break;
        }
    }

//    int r;
//
//    for(r=0;r<sizeof(m_Files)/sizeof(struct FileInfo);r++)
//    {
//        if(strcmp(Filename,m_Files[r].Filename)==0)
//        {
//            PageProp->FileID=(uintptr_t)&m_Files[r];
//            PageProp->DynamicFile=m_Files[r].Dynamic;
//            PageProp->Cookies=m_Files[r].Cookies;
//            PageProp->Gets=m_Files[r].Gets;
//            PageProp->Posts=m_Files[r].Posts;
//            return true;
//        }
//    }
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
    char FilePath[MAX_DISK_BASED_PATH_LEN];

    /* Not needed but I always check... */
    if(File==NULL)
        return;

    switch(File->FileKind)
    {
        case e_FileKind_BuiltIn:
            if(File->BuiltIn.PageID!=e_PageMAX)
            {
                Start_WebPage(Web,g_PageInfo[File->BuiltIn.PageID].PageTitle,
                        File->BuiltIn.PageID);
            }
            File->BuiltIn.WriteFile(Web);
            if(File->BuiltIn.PageID!=e_PageMAX)
            {
                End_WebPage(Web);
            }
        break;
        case e_FileKind_DiskBased:
            if(!BuildDiskBasedFilename(FilePath,MAX_DISK_BASED_PATH_LEN,
                    m_RequestFilename,File->DiskBased.HTMLPath,
                    File->DiskBased.DiskPath))
            {
                /* We ran out of space, should have been handled before we
                   got here so just ignore */
                return;
            }
            SendDiskFile(Web,FilePath,!File->DiskBased.TextFile);
        break;
        case e_FileKindMAX:
        break;
    }
}

/*******************************************************************************
 * NAME:
 *    FS_FindPagePath
 *
 * SYNOPSIS:
 *    const char *FS_FindPagePath(e_PageType PageID);
 *
 * PARAMETERS:
 *    PageID [I] -- The page ID to get the HTML filename for
 *
 * FUNCTION:
 *    This function searchs for a page that matches the requested ID and
 *    returns it's HTML path and filename (the filename needed to link to this
 *    page).
 *
 * RETURNS:
 *    A static buffer with the path and filename of the requested page or
 *    NULL if it could not be found.
 *
 * NOTES:
 *    The returned string does not include the http:// or server name, only
 *    the path (starting at root).
 *
 * LIMITATIONS:
 *    This is a slow search as it needs to go though all the files looking
 *    for the requested page.
 *
 * EXAMPLE:
 *    
 *
 * SEE ALSO:
 *    
 ******************************************************************************/
const char *FS_FindPagePath(e_PageType PageID)
{
    int r;

    for(r=0;r<sizeof(m_Files)/sizeof(struct FileInfo);r++)
    {
        if(m_Files[r].FileKind==e_FileKind_BuiltIn &&
                m_Files[r].BuiltIn.PageID==PageID)
        {
            return m_Files[r].BuiltIn.Filename;
        }
    }

    return NULL;
}

/*******************************************************************************
 * NAME:
 *    BuildDiskBasedFilename
 *
 * SYNOPSIS:
 *    static bool BuildDiskBasedFilename(char *OutputBuff,int MaxBuff,
 *          const char *ReqFilename,const char *HTMLPath,const char *DiskPath);
 *
 * PARAMETERS:
 *    OutputBuff [O] -- The buffer to fill in with the disk based path
 *    MaxBuff [I] -- The max size of 'OutputBuff'
 *    ReqFilename [I] -- The URL part of the filename
 *    HTMLPath [I] -- The base HTML path
 *    DiskPath [I] -- The disk path to replace the HTML path with.
 *
 * FUNCTION:
 *    This function builds a disk based filename for a file by replacing
 *    the 'HTMLPath' part of the 'ReqFilename' with 'DiskPath'.
 *
 * RETURNS:
 *    true -- Things worked
 *    false -- We didn't have space in the 'OutputBuff'.
 *
 * SEE ALSO:
 *    
 ******************************************************************************/
static bool BuildDiskBasedFilename(char *OutputBuff,int MaxBuff,
        const char *ReqFilename,const char *HTMLPath,const char *DiskPath)
{
    int l;

    l=strlen(HTMLPath);
    if(strlen(DiskPath)+strlen(&ReqFilename[l])>=MaxBuff)
    {
        /* Path is too long */
        return false;
    }
    strcpy(OutputBuff,DiskPath);
    strcat(OutputBuff,&ReqFilename[l]);
    return true;
}

/*******************************************************************************
 * NAME:
 *    SendDiskFile
 *
 * SYNOPSIS:
 *    void SendDiskFile(struct WebServer *Web,const char *Filename,bool Binary);
 *
 * PARAMETERS:
 *    Web [I] -- The web server to work on
 *    Filename [I] -- The file to open and send.
 *    Binary [I] -- Is this file binary (if true then send as
 *                  "application/octet-stream", else send as
 *                  "text/plain").
 *
 * FUNCTION:
 *    This function sends a file from the disk.
 *
 * RETURNS:
 *    NONE
 *
 * SEE ALSO:
 *    
 ******************************************************************************/
void SendDiskFile(struct WebServer *Web,const char *Filename,bool Binary)
{
    FILE *in;
    char buff[1000];
    int bytes;

    if(Binary)
        WS_Header(Web,"Content-Type: application/octet-stream");
    else
        WS_Header(Web,"Content-Type: text/plain");

    in=fopen(Filename,"rb");
    if(in==NULL)
        return;

    while((bytes=fread(buff,1,sizeof(buff),in))>0)
        WS_WriteChunk(Web,buff,bytes);

    fclose(in);
}
