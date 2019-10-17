/*******************************************************************************
 * FILENAME: Waiting.c
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
 * CREATED BY:
 *    Paul Hutchinson (28 Aug 2019)
 *
 ******************************************************************************/

/*** HEADER FILES TO INCLUDE  ***/
#include "CodeExamples.h"
#include "Pages/Pages.h"
#include "Common/Headers.h"

/*** DEFINES                  ***/

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/

/*** FUNCTION PROTOTYPES      ***/

/*** VARIABLE DEFINITIONS     ***/

const char m_WaitingHTML[]=
"<h1><span>1</span>Waiting on a socket</h1>\n"
"<p>Shows how to wait for traffic on the socket instead of polling.  This\n"
"is mainly useful when running under an operating system instead of directly\n"
"on the metel.</p>"
"\n"
"<p>We wait by having the main loop ask for the active sockets so we can use\n"
"<span class='coderef'>select()</span> or one of the other handles.</p>"
"\n"
"<h2>Files</h2>";

const char m_WaitingHTML2[]=
"<h2>FileServer.c</h2>\n"
"<p>The file server is setup to just send a basic page as this example works\n"
"mainly in the main.c file.</p>\n"
"\n"
"<div class='code'>"
"struct FileInfo m_Files[]=\n"
"{\n"
"    /* Filename, Dynamic, Cookies, Gets, Posts, Callback */\n"
"    {\"/\",false,NULL,NULL,NULL,File_Root},\n"
"    {\"/SomeStyle.css\",false,NULL,NULL,NULL,File_SomeStyle},\n"
"    {\"/quit.html\",true,NULL,NULL,NULL,File_Quit},\n"
"};\n"
"</div>\n"
"At the bottom we have the code that handles sending the static page.\n"
"<div class='code'>"
"const char RootHTML[]=\n"
"\"&lt;!DOCTYPE html&gt;\"\n"
"\"&lt;html&gt;\"\n"
"\"&lt;head&gt;\"\n"
"    \"&lt;title&gt;Bitty HTTP - Root&lt;/title&gt;\"\n"
"    \"&lt;link rel='stylesheet' href='/SomeStyle.css'&gt;\"\n"
"\"&lt;/head&gt;\"\n"
"\"&lt;body&gt;\"\n"
"    \"&lt;div id='top'&gt;Bitty HTTP Example - Root&lt;/div&gt;\"\n"
"    \"&lt;div id='quitbttn'&gt;&lt;a href='/quit.html'&gt;QUIT&lt;/a&gt;&lt;/div&gt;\"\n"
"    \"&lt;div id='content'&gt;\"\n"
"        \"Wait example&lt;br/&gt;\"\n"
"    \"&lt;/div&gt;\"\n"
"\"&lt;div id='bottom'&gt;&lt;/div&gt;\"\n"
"\"&lt;/body&gt;\"\n"
"\"&lt;/html&gt;\";\n"
"\n"
"void File_Root(struct WebServer *Web)\n"
"{\n"
"    WS_WriteWhole(Web,RootHTML,sizeof(RootHTML)-1);\n"
"}\n"
"</div>\n"
"\n"
"<h2>main.c</h2>\n"
"<p>The main has it's main loop changed to wait on the sockets that the\n"
"web server currently have open.</p>\n"
"<div class='code'>"
"int main(void)\n"
"{\n"
"    t_ElapsedTime Waiting2End;\n"
"    t_ConSocketHandle OSHandles[WS_OPT_MAX_CONNECTIONS+1];\n"
"    fd_set rfds;\n"
"    int retval;\n"
"    int MaxFD;\n"
"    int r;\n"
"    int HandleCount;\n"
"</div>"
"<p>First there are some new variables:\n"
"<ul>\n"
"<li>OSHandles</li>\n"
"<li>rfds</li>\n"
"<li>retval</li>\n"
"<li>MaxFD</li>\n"
"<li>r</li>\n"
"<li>HandleCount</li>\n"
"</ul>\n"
"<p><span class='coderef'>OSHandles[]</span> is used to hold the socket\n"
"handles that are currently open.  This has the same number as\n"
"<span class='coderef'>WS_OPT_MAX_CONNECTIONS</span> plus one for the\n"
"listening socket.  We will fill this array in by calling\n"
"<span class='coderef'>WS_GetOSSocketHandles()</span>.</p>"
"<p><span class='coderef'>rfds</span> is the set of OS handles to wait on.\n"
"This is filled in using <span class='coderef'>FD_SET()</span> with each the\n"
"socket handles that where returned in\n"
"<span class='coderef'>OSHandles[]</span>.</p>\n"
"<p><span class='coderef'>retval</span> is the return value from the\n"
"<span class='coderef'>select()</span> it's self.  We only print out an error\n"
"if <span class='coderef'>select()</span> returns an error</p>"
"<p><span class='coderef'>MaxFD</span> is the highest OS file handle that we\n"
"found in the socket handles.</p>"
"<p><span class='coderef'>r</span> is just a simple loop counter.</p>"
"<p><span class='coderef'>HandleCount</span> is the number of socket handles\n"
"that was returned by <span class='coderef'>WS_GetOSSocketHandles()</span>.</p>"
"<div class='code'>"
"\n"
"    SocketsCon_InitSocketConSystem();\n"
"    WS_Init();\n"
"\n"
"    if(!WS_Start(3000))\n"
"    {\n"
"        printf(\"Failed to start web server\\n\");\n"
"        return 0;\n"
"    }\n"
"\n"
"    printf(\"Waiting for connections on port 3000\\n\");\n"
"\n"
"    g_Quit=false;\n"
"    while(!g_Quit)\n"
"    {\n"
"        WS_Tick();\n"
"        \n"
"</div>"
"<p>This all remains unchanged</p>\n"
"<div class='code'>"
"        /* Wait for traffic */\n"
"        FD_ZERO(&rfds);\n"
"        \n"
"        /* What handles are open may change each loop, so we think it all */\n"
"        HandleCount=WS_GetOSSocketHandles(OSHandles);\n"
"</div>"

"<p>We have replaced the <span class='coderef'>usleep(1000);</span> with\n"
"code to get the active sockets and then wait on them.</p>\n"
"<p>The first thing we do is normal <span class='coderef'>select()</span>\n"
"handing such has zeroing the <span class='coderef'>rfds</span> variable.</p>"
"<p>We then call <span class='coderef'>WS_GetOSSocketHandles()</span> to get\n"
"the active sockets.  This will fill in the\n"
"<span class='coderef'>OSHandles[]</span> array with the socket handles we\n"
"will waiting on.  The web server may have up to\n"
"<span class='coderef'>WS_OPT_MAX_CONNECTIONS</span> open, or none of them\n"
"(depending on what requests are being processed) the\n"
"<span class='coderef'>WS_GetOSSocketHandles()</span> function returns the\n"
"number of handles it filled in.</p>"
"<p><span class='coderef'>WS_GetOSSocketHandles()</span> uses\n"
"<span class='coderef'>t_ConSocketHandle</span> as the type data for a OS\n"
"socket handle.  This type will depend on what a socket handle on the OS\n"
"being used is.  This is defined in <span class='coderef'>SocketsCon.h</span>.\n"
"This allows the system to return a complex type such as a structure as a\n"
"socket handle.</p>"
"<p>In this example it is a Unix style handle which is a simple\n"
"<span class='coderef'>int</span>.</p>"
"<div class='code'>"
"        MaxFD=0;\n"
"        for(r=0;r&lt;HandleCount;r++)\n"
"        {\n"
"            if(OSHandles[r]&gt;MaxFD)\n"
"                MaxFD=OSHandles[r];\n"
"            FD_SET(OSHandles[r],&rfds);\n"
"        }\n"
"</div>"
"<p>Next we need to find the highest socket handle number to pass into\n"
"<span class='coderef'>select()</span>.  We loop through all the handles\n"
"returned to us updating <span class='coderef'>MaxFD</span> if the new\n"
"handle is bigger than the old <span class='coderef'>MaxFD</span>.  We\n"
"also need to use <span class='coderef'>FD_SET()</span> to setup\n"
"<span class='coderef'>rfds</span>.</p>\n"
"<div class='code'>"
"        retval=select(MaxFD+1,&rfds,NULL,NULL,NULL);\n"
"        if(retval&lt;0)\n"
"            printf(\"select() error\\n\");\n"
"</div>"
"<p>At this point we call the select that will wait forever for something\n"
"to happen on one of the sockets.</p>"
"<p>If the return value from <span class='coderef'>select()</span> is\n"
"negative then we just print an error message and continue.  You would likely\n"
"want to handle the error here.</p>"
""
"<div class='code'>"
"    }\n"
"    printf(\"Quiting...\\n\");\n"
"\n"
"    /* Run the web server for a while so we can send any \"finished\" page */\n"
"    Waiting2End=ReadElapsedClock();\n"
"    while(ReadElapsedClock()-Waiting2End&lt;3)\n"
"        WS_Tick();\n"
"\n"
"    WS_Shutdown();\n"
"    SocketsCon_ShutdownSocketConSystem();\n"
"\n"
"    return 0;\n"
"}"
"</div>"
"<p>The shut down code remains the same as before.</p>"
"";

void File_Doc_Waiting(struct WebServer *Web)
{
    WS_WriteChunk(Web,m_WaitingHTML,sizeof(m_WaitingHTML)-1);
    OutputListOfExampleFiles(Web,e_ExampleCode_Waiting);
    WS_WriteChunk(Web,m_WaitingHTML2,sizeof(m_WaitingHTML2)-1);
}
