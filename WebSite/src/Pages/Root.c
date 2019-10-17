/*******************************************************************************
 * FILENAME: Root.c
 *
 * PROJECT:
 *    Bitty HTTP
 *
 * FILE DESCRIPTION:
 *    This is the main root file
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
#include "../../ReleaseNotes.h"
#include "Pages/Pages.h"
#include "Common/DownloadInfo.h"
#include "Common/Headers.h"
#include <string.h>

/*** DEFINES                  ***/

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/

/*** FUNCTION PROTOTYPES      ***/

/*** VARIABLE DEFINITIONS     ***/

const char HelloWorldHTML[]=
"<h1><span>1</span>Welcome</h1>\n"
"<p>"PRODUCTNAME" is a small lightweight web server designed be used in small\n"
"micro controlers, but powerful enough to be used with large embedded processors\n"
"and even embedded into larger programs.</p>\n"
"\n"
"<p>If you are looking for small, simple, easy to use HTTP server with minimal\n"
"dependencies then you have found what you are looking for.</p>\n"
"\n"
"<p>"PRODUCTNAME" is licensed under the MIT License\n"
"(see License.txt).  This means you are free to use this software\n"
"however you want as long as you keep the copyright notice.</p>\n"
"\n"
"Download the latest version and get started today!<br/>\n";
//"<a href='#' class='bttn' style='background-color:green'>Download...</a>\n";

void File_Root(struct WebServer *Web)
{
    char Version[100];
    const char *Str;

    WS_WriteChunk(Web,HelloWorldHTML,sizeof(HelloWorldHTML)-1);

    WS_WriteChunk(Web,"<a class='bttn' style='background-color:green' href='/Releases/",63);
    BuildReleaseFilename(m_ReleaseNotes[m_ReleaseNoteCount-1].Version,Version);
    WS_WriteChunk(Web,Version,strlen(Version));
    WS_WriteChunk(Web,"'>",2);
    WS_WriteChunk(Web,"Download ",9);
    Str=m_ReleaseNotes[m_ReleaseNoteCount-1].Version;
    WS_WriteChunk(Web,Str,strlen(Str));
    WS_WriteChunk(Web,"...</a>",7);
}
