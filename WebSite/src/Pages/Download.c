/*******************************************************************************
 * FILENAME: Download.c
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
#include "../../ReleaseNotes.h"
#include "Pages/Pages.h"
#include "Common/Headers.h"
#include "Common/DownloadInfo.h"
#include <stdio.h>
#include <string.h>

/*** DEFINES                  ***/

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/

/*** FUNCTION PROTOTYPES      ***/

/*** VARIABLE DEFINITIONS     ***/

const char m_DownloadHTML[]=
"<h1><span>1</span>Downloads</h1>\n"
"<p>This is where you can download the current version of "PRODUCTNAME".</p>";

const char m_WebSiteBlockHTML[]=
"<h1><span>2</span>Website</h1>\n"
"<p>You can download the source for this web site here.</p>"
"<p>The website it's self is written in C using "PRODUCTNAME" as it's web "
"server.</p>";

void File_Download(struct WebServer *Web)
{
    const char *Str;
    int r;
    char Version[100];

    WS_WriteChunk(Web,m_DownloadHTML,sizeof(m_DownloadHTML)-1);
    WS_WriteChunk(Web,"<h2>Current Version</h2>",24);

    WS_WriteChunk(Web,"<a class='bttn' style='background-color:green' href='/Releases/",63);
    BuildReleaseFilename(m_ReleaseNotes[m_ReleaseNoteCount-1].Version,Version);
    WS_WriteChunk(Web,Version,strlen(Version));
    WS_WriteChunk(Web,"'>",2);
    WS_WriteChunk(Web,"Download ",9);
    Str=m_ReleaseNotes[m_ReleaseNoteCount-1].Version;
    WS_WriteChunk(Web,Str,strlen(Str));
    WS_WriteChunk(Web,"</a>",4);

    WS_WriteChunk(Web,"<br/>",5);
    WS_WriteChunk(Web,"<br/>",5);

    WS_WriteChunk(Web,"<h2>Past Versions</h2>",22);
    WS_WriteChunk(Web,"<table class='ReleaseTable'>",28);
    for(r=0;r<m_ReleaseNoteCount;r++)
    {
        WS_WriteChunk(Web,"<tr>",4);

        /* Version string */
        WS_WriteChunk(Web,"<td>",4);
        Str=m_ReleaseNotes[r].Version;
        WS_WriteChunk(Web,Str,strlen(Str));
        WS_WriteChunk(Web,"</td>",5);

        /* Link */
        WS_WriteChunk(Web,"<td>",4);
        WS_WriteChunk(Web,"<a href='/Releases/",19);
        BuildReleaseFilename(m_ReleaseNotes[r].Version,Version);
        WS_WriteChunk(Web,Version,strlen(Version));
        WS_WriteChunk(Web,"'>",2);
        WS_WriteChunk(Web,Version,strlen(Version));
        WS_WriteChunk(Web,"</a>",4);
        WS_WriteChunk(Web,"</td>",5);

        /* Release notes */
        WS_WriteChunk(Web,"<td>",4);
        WS_WriteChunk(Web,"<a href='/ReleaseNotes.html#",28);
        WS_WriteChunk(Web,m_ReleaseNotes[r].Version,
                strlen(m_ReleaseNotes[r].Version));
        WS_WriteChunk(Web,"'>",2);
        WS_WriteChunk(Web,"Release Notes",13);
        WS_WriteChunk(Web,"</a>",4);
        WS_WriteChunk(Web,"</td>",5);

        WS_WriteChunk(Web,"</tr>",5);
    }
    WS_WriteChunk(Web,"</table>",8);

    /* Web site */
    WS_WriteChunk(Web,m_WebSiteBlockHTML,sizeof(m_WebSiteBlockHTML)-1);

    WS_WriteChunk(Web,"<p>",3);
    WS_WriteChunk(Web,"<a class='bttn' style='background-color:green' "
            "href='/Releases/WebSite.tar.gz'>Download Website</a>",99);
    WS_WriteChunk(Web,"</p>",4);

}

/* DEBUG PAUL: Add Web site download */
