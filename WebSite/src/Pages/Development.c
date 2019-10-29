/*******************************************************************************
 * FILENAME: Development.c
 *
 * PROJECT:
 *    Bitty HTTP
 *
 * FILE DESCRIPTION:
 *    
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
#include "Pages/Pages.h"
#include "CodeExamples.h"
#include "Common/Headers.h"
#include <string.h>

/*** DEFINES                  ***/

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/

/*** FUNCTION PROTOTYPES      ***/

/*** VARIABLE DEFINITIONS     ***/

const char m_DevelopmentHTML[]=
"<h1><span>1</span>API Explained</h1>\n"
"<p>This is a series of examples that explain how to use "PRODUCTNAME".  It "
"starts from a simple hello world web page and adds more with each example "
"explaining and demoing each feature as it goes."
"</p>"
"<ul>"
    "<li><a href='/Doc/TheBasics.html'>The Basics</a></li>"
    "<li><a href='/Doc/HelloWorld.html'>Hello World</a></li>"
    "<li><a href='/Doc/CSS.html'>CSS</a></li>"
    "<li><a href='/Doc/Graphics.html'>Graphics</a></li>"
    "<li><a href='/Doc/DynamicContent.html'>Dynamic Content</a></li>"
    "<li><a href='/Doc/GETVars.html'>GET Vars</a></li>"
    "<li><a href='/Doc/POSTVars.html'>POST Vars</a></li>"
    "<li><a href='/Doc/Cookies.html'>Cookies</a></li>"
    "<li><a href='/Doc/ManualHeaders.html'>Manual Headers</a></li>"
    "<li><a href='/Doc/URLEncoding.html'>URL encoding/decoding</a></li>"
    "<li><a href='/Doc/Waiting.html'>Waiting on a socket</a></li>"
    "<li><a href='/Doc/Error404.html'>404 Error Page</a></li>"
"</ul>"

"<h1><span>2</span>Autodocs</h1>\n"
"<p>The autodocs are the headers off the API.  They document what API calls "
"are available and how to use them.  You can get the same information by "
"looking at the source code, but this is easier to navigate.</p>"
"<ul>"
    "<li><a href=\"/AutoDocs.html#WS_COOKIE_WebServer.c\">WS_COOKIE</a></li>\n"
    "<li><a href=\"/AutoDocs.html#WS_GET_WebServer.c\">WS_GET</a></li>\n"
    "<li><a href=\"/AutoDocs.html#WS_GetOSSocketHandles_WebServer.c\">WS_GetOSSocketHandles</a></li>\n"
    "<li><a href=\"/AutoDocs.html#WS_Header_WebServer.c\">WS_Header</a></li>\n"
    "<li><a href=\"/AutoDocs.html#WS_Init_WebServer.c\">WS_Init</a></li>\n"
    "<li><a href=\"/AutoDocs.html#WS_Location_WebServer.c\">WS_Location</a></li>\n"
    "<li><a href=\"/AutoDocs.html#WS_POST_WebServer.c\">WS_POST</a></li>\n"
    "<li><a href=\"/AutoDocs.html#WS_SetCookie_WebServer.c\">WS_SetCookie</a></li>\n"
    "<li><a href=\"/AutoDocs.html#WS_SetHTTPStatusCode_WebServer.c\">WS_SetHTTPStatusCode</a></li>\n"
    "<li><a href=\"/AutoDocs.html#WS_Shutdown_WebServer.c\">WS_Shutdown</a></li>\n"
    "<li><a href=\"/AutoDocs.html#WS_Start_WebServer.c\">WS_Start</a></li>\n"
    "<li><a href=\"/AutoDocs.html#WS_Tick_WebServer.c\">WS_Tick</a></li>\n"
    "<li><a href=\"/AutoDocs.html#WS_URLDecode_WebServer.c\">WS_URLDecode</a></li>\n"
    "<li><a href=\"/AutoDocs.html#WS_URLDecodeInPlace_WebServer.c\">WS_URLDecodeInPlace</a></li>\n"
    "<li><a href=\"/AutoDocs.html#WS_URLEncode_WebServer.c\">WS_URLEncode</a></li>\n"
    "<li><a href=\"/AutoDocs.html#WS_WriteChunk_WebServer.c\">WS_WriteChunk</a></li>\n"
    "<li><a href=\"/AutoDocs.html#WS_WriteChunkStr_WebServer.c\">WS_WriteChunkStr</a></li>\n"
    "<li><a href=\"/AutoDocs.html#WS_WriteWhole_WebServer.c\">WS_WriteWhole</a></li>\n"
    "<li><a href=\"/AutoDocs.html#WS_WriteWholeStr_WebServer.c\">WS_WriteWholeStr</a></li>\n"
"</ul>"

"<h1><span>3</span>Examples</h1>\n"
"<p>This is the source to the examples that are described in the API explained "
"section.</p>"
"";

void File_Development(struct WebServer *Web)
{
    int e;

    WS_WriteChunk(Web,m_DevelopmentHTML,sizeof(m_DevelopmentHTML)-1);

    /* Now all the examples source */
    WS_WriteChunk(Web,"<ul>\n",5);
    for(e=0;e<g_ExamplesCount;e++)
    {
        WS_WriteChunk(Web,"<li>\n",5);
        WS_WriteChunk(Web,g_Examples[e].Name,strlen(g_Examples[e].Name));
        OutputListOfExampleFiles(Web,e);
        WS_WriteChunk(Web,"</li>\n",6);
    }
    WS_WriteChunk(Web,"</ul>\n",6);
}

