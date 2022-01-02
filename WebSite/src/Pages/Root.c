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
#define WCCOLOR         "black"
#define HTMLCOLOR       "blue"
#define CCOLOR          "green"

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/

/*** FUNCTION PROTOTYPES      ***/

/*** VARIABLE DEFINITIONS     ***/

const char RootHTML[]=
"<h1><span>1</span>Welcome</h1>\n"
"<p>"PRODUCTNAME" is a small lightweight web server designed be used in small\n"
"microcontrollers, but powerful enough to be used with large embedded processors\n"
"and even embedded into larger programs.</p>\n"
"\n"
"<p>If you are looking for small, simple, easy to use HTTP server with minimal\n"
"dependencies then you have found what you are looking for.</p>\n"
"\n"
"<p>"PRODUCTNAME" is licensed under the MIT License\n"
"(see License.txt).  This means you are free to use this software\n"
"however you want as long as you keep the copyright notice.</p>\n"
"\n"
"Download the latest version and get started today!<br/>\n"
"<br/>";
//"<a href='#' class='bttn' style='background-color:green'>Download...</a>\n";

const char RootPart2HTML[]=
"<br/>\n"
"<br/>\n"
"<h1><span>2</span>Other Projects That Work With "PRODUCTNAME"</h1>\n"
"<div style='font-size:1.5em'><a href='http://webcprecompiler.com/'>WebC</a></div>\n"
"<div style='margin-left:10px'>\n"
"<p><a href='http://webcprecompiler.com/'>WebC</a> makes working with HTML in C much easier.  It works by letting you "
"write C code mixed in with your HTML, changing between the two on the fly.  "
"The <a href='http://webcprecompiler.com/'>WebC</a> compiler then converts your mixed C &amp; HTML into C code which "
"you then compile with your normal C compiler.</p>"
"<p>For example this <a href='http://webcprecompiler.com/'>WebC</a> program outputs a calendar.  Note how easy it is "
"to change between HTML and C.</p>"
"<div class='code'>"
"<div style='color:"WCCOLOR"'>"
"&lt;?wc\n"
"</div>"
"<div style='color:"CCOLOR"'>"
"#include &lt;time.h&gt;\n"
"#include &lt;stdio.h&gt;\n"
"#include &lt;string.h&gt;\n"
"\n"
"/* Jan 2022 */\n"
"#define MONTH  (0)             // 0=Jan\n"
"#define YEAR   (2022-1900)     // 1900 based\n"
"\n"
"void OutputCal(void)\n"
"{\n"
"    char buff[100];\n"
"    time_t thetime;\n"
"    struct tm start;\n"
"    int r,w;\n"
"    const int DaysInMonth[12]={31,28,31,30,31,30,31,31,30,31,30,31};\n"
"\n"
"    memset(&start,0x00,sizeof(start));\n"
"    start.tm_mday=1;\n"
"    start.tm_mon=MONTH;\n"
"    start.tm_year=YEAR;\n"
"\n"
"    /* Get the week day */\n"
"    thetime=mktime(&start)-timezone;\n"
"    start=*gmtime(&thetime);\n"
"</div>"
"<div style='color:"WCCOLOR"'>"
"?&gt;\n"
"</div>"
"<div style='color:"HTMLCOLOR"'>"
"&lt;!doctype html&gt;\n"
"&lt;html&gt;\n"
"    &lt;head&gt;\n"
"        &lt;title&gt;Calendar&lt;/title&gt;\n"
"    &lt;/head&gt;\n"
"    &lt;body&gt;\n"
"        &lt;table&gt;\n"
"            &lt;tr&gt;\n"
"                &lt;th&gt;Sun&lt;/th&gt;&lt;th&gt;Mon&lt;/th&gt;&lt;th&gt;Tue&lt;/th&gt;&lt;th&gt;Wed&lt;/th&gt;&lt;th&gt;Thu&lt;/th&gt;&lt;th&gt;Fri&lt;/th&gt;&lt;th&gt;Sat&lt;/th&gt;\n"
"            &lt;/tr&gt;\n"
"            &lt;tr&gt;\n"
"</div>"
"<div style='color:"WCCOLOR"'>"
"&lt;?wc\n"
"</div>"
"<div style='color:"CCOLOR"'>"
"                /* Output the cal */\n"
"                if(start.tm_wday&gt;0)\n"
"                {\n"
"                    sprintf(buff,\"&lt;td colspan='%d'&gt;&lt;/td&gt;\",start.tm_wday);\n"
"                    wcecho(buff);\n"
"                }\n"
"\n"
"                w=start.tm_wday;\n"
"                for(r=0;r&lt;DaysInMonth[start.tm_mon];r++)\n"
"                {\n"
"                    sprintf(buff,\"&lt;td&gt;%d&lt;/td&gt;\",r+1);\n"
"                    wcecho(buff);\n"
"                    w=(w+1)%7;\n"
"                    if(w==0)\n"
"                        wcecho(\"&lt;/tr&gt;\\n&lt;tr&gt;\");\n"
"                }\n"
"</div>"
"<div style='color:"WCCOLOR"'>"
"?&gt;\n"
"</div>"
"<div style='color:"HTMLCOLOR"'>"
"            &lt;/tr&gt;\n"
"        &lt;/table&gt;\n"
"    &lt;/body&gt;\n"
"&lt;/html&gt;\n"
"</div>"
"<div style='color:"WCCOLOR"'>"
"&lt;?wc\n"
"</div>"
"<div style='color:"CCOLOR"'>"
"}\n"
"</div>"
"<div style='color:"WCCOLOR"'>"
"?&gt;\n"
"</div>"
"</div>"

"<p>This will then get converted into a C program that you can compile.  "
"The compiled program will output HTML (which can be sent to "PRODUCTNAME")</p>"
"<p>Swing by <a href='http://webcprecompiler.com/'>http://webcprecompiler.com</a> to check it out!</p>";

void File_Root(struct WebServer *Web)
{
    char Version[100];
    const char *Str;

    WS_WriteChunk(Web,RootHTML,sizeof(RootHTML)-1);

    WS_WriteChunk(Web,"<a class='bttn' style='background-color:green' href='/Releases/",63);
    BuildReleaseFilename(m_ReleaseNotes[m_ReleaseNoteCount-1].Version,Version);
    WS_WriteChunk(Web,Version,strlen(Version));
    WS_WriteChunk(Web,"'>",2);
    WS_WriteChunk(Web,"Download ",9);
    Str=m_ReleaseNotes[m_ReleaseNoteCount-1].Version;
    WS_WriteChunk(Web,Str,strlen(Str));
    WS_WriteChunk(Web,"...</a>",7);

    WS_WriteChunk(Web,RootPart2HTML,sizeof(RootPart2HTML)-1);
}
