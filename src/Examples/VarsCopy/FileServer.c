/*******************************************************************************
 * FILENAME: FileServer.c
 *
 * PROJECT:
 *    Bitty HTTP
 *
 * FILE DESCRIPTION:
 *    example using WS_GETCopy()/WS_POSTCopy()/WS_COOKIECopy()
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
const char *GetArgs[]=
{
    "Name",
    "DoCookie",
    "SetCookieValue",
    NULL
};

const char *PostArgs[]=
{
    "Name",
    NULL
};

const char *CookieArgs[]=
{
    "Name",
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
    void (*WriteFile)(struct WebServer *Web);
};

/*** FUNCTION PROTOTYPES      ***/
void File_Root(struct WebServer *Web);
void File_Display(struct WebServer *Web);
void File_SomeStyle(struct WebServer *Web);
void File_Quit(struct WebServer *Web);

/*** VARIABLE DEFINITIONS     ***/
struct FileInfo m_Files[]=
{
    /* Filename, Dynamic, Cookies, Gets, Posts, Callback */
    {"/",false,NULL,NULL,NULL,NULL,File_Root},
    {"/Display.html",true,CookieArgs,GetArgs,PostArgs,NULL,File_Display},
    {"/SomeStyle.css",false,NULL,NULL,NULL,NULL,File_SomeStyle},
    {"/quit.html",true,NULL,NULL,NULL,NULL,File_Quit},
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
    "<title>Bitty HTTP - VarCopy example</title>"
    "<link rel='stylesheet' href='/SomeStyle.css'>"
"</head>"
"<body>"
    "<div id='top'>Bitty HTTP Example - VarCopy</div>"
    "<div id='quitbttn'><a href='/quit.html'>QUIT</a></div>"
    "<div id='content'>"
        "<div style='border:1px solid black;padding:3px;margin-top:5px;'>"
        "GET example<br/>"
        "<form action='/Display.html' method='GET'>"
        "Input your name:<input name='Name'></input> "
        "<input type='submit'></input>"
        "</form>"
        "</div>"
        "<br/>"
        "<div style='border:1px solid black'>"
        "POST example<br/>"
        "<form action='/Display.html' method='POST'>"
        "Input your name:<input name='Name'></input> "
        "<input type='submit'></input>"
        "</form>"
        "</div>"
        "<br/>"
        "<div style='border:1px solid black'>"
        "COOKIE example<br/>"
        "<form action='/Display.html' method='GET'>"
        "<input type='hidden' name='DoCookie' value='1' />"
        "Input your name:<input name='SetCookieValue'></input> "
        "<input type='submit'></input>"
        "</form>"
        "</div>"
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
    char DoingCookie[2];
    char GetName[10];
    char PostName[10];
    char CookieName[10];
    char SetCookieValue[10];
    bool GetFound;
    bool PostFound;
    bool CookieFound;

    /* Collect all the vars first */
    GetFound=WS_GETCopy(Web,"Name",GetName,sizeof(GetName));
    PostFound=WS_POSTCopy(Web,"Name",PostName,sizeof(PostName));
    CookieFound=WS_COOKIECopy(Web,"Name",CookieName,sizeof(CookieName));

    /* Handle setting the cookie (if needed) */
    WS_GETCopy(Web,"DoCookie",DoingCookie,sizeof(DoingCookie));
    if(DoingCookie[0]=='1')
    {
        /* We use 'SetCookieValue' without checking if it was found because we
           know it will be set to '\0' if it was not found */
        WS_GETCopy(Web,"SetCookieValue",SetCookieValue,sizeof(SetCookieValue));
        WS_SetCookie(Web,"Name",SetCookieValue,0,NULL,NULL,false,false);
    }

    /* Start the page */
    WS_WriteChunk(Web,DisplayHTML_Start,sizeof(DisplayHTML_Start)-1);

    WS_WriteChunkStr(Web,"<table>");
    /************ GET ************/
    WS_WriteChunkStr(Web,"<tr>");
    WS_WriteChunkStr(Web,"<td>GET</td>");

    snprintf(buff,sizeof(buff),"<td>Value:\"%s\"</td>",GetName);
    WS_WriteChunkStr(Web,buff);
    if(!GetFound)
        WS_WriteChunkStr(Web,"<td>Name was not set or was too long</td>");
    else
        WS_WriteChunkStr(Web,"<td></td>");
    WS_WriteChunkStr(Web,"</tr>");

    /************ POST ************/
    WS_WriteChunkStr(Web,"<tr>");
    WS_WriteChunkStr(Web,"<td>POST</td>");

    snprintf(buff,sizeof(buff),"<td>Value:\"%s\"</td>",PostName);
    WS_WriteChunkStr(Web,buff);
    if(!PostFound)
        WS_WriteChunkStr(Web,"<td>Name was not set or was too long</td>");
    else
        WS_WriteChunkStr(Web,"<td></td>");
    WS_WriteChunkStr(Web,"</tr>");

    /************ COOKIE ************/
    WS_WriteChunkStr(Web,"<tr>");
    WS_WriteChunkStr(Web,"<td>COOKIE</td>");

    snprintf(buff,sizeof(buff),"<td>Value:\"%s\"</td>",CookieName);
    WS_WriteChunkStr(Web,buff);
    if(!CookieFound)
        WS_WriteChunkStr(Web,"<td>Name was not set or was too long");
    else
        WS_WriteChunkStr(Web,"<td>");
    WS_WriteChunkStr(Web," (Remember the cookie value will be 1 refresh behind)</td>");
    WS_WriteChunkStr(Web,"</tr>");

    WS_WriteChunkStr(Web,"</table>");

    WS_WriteChunk(Web,"<br/><br/><a href='/'>Try again</a>",35);
    WS_WriteChunk(Web,"<br/>",5);

    WS_WriteChunk(Web,DisplayHTML_End,sizeof(DisplayHTML_End)-1);
}

