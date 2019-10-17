/*******************************************************************************
 * FILENAME: DynamicContent.c
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
#include "CodeExamples.h"
#include "Pages/Pages.h"
#include "Common/Headers.h"

/*** DEFINES                  ***/

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/

/*** FUNCTION PROTOTYPES      ***/

/*** VARIABLE DEFINITIONS     ***/

const char m_DynamicContentHTML[]=
"<h1><span>1</span>Dynamic content (chunked output)</h1>\n"
"<p>This example will show sending dynamic content using chunked\n"
"transfer encoding.</p>\n"
"\n"
"<p>Chunked encoding is where you do not send the total size of the file you\n"
"which to send but instead send small chunks of the file and a marker\n"
"saying you are done.</p>\n"
"\n"
"<p>This is very useful for dynamic content as you do not have to pre\n"
"build the whole file in RAM before sending it, but instead can send it\n"
"as you build it.</p>\n"
"\n"
"<h2>Files</h2>";

const char m_DynamicContentHTML2[]=
"<h2>FileServer.c</h2>\n"
"<p>We change the file server file removing the graphic stuff we added in the\n"
"last example and changing the root file to output dynamic content instead of\n"
"the static content we where using before.</p>\n"
"\n"
"<div class='code'>"
"struct FileInfo m_Files[]=\n"
"{\n"
"    /* Filename, Dynamic, Cookies, Gets, Posts, Callback */\n"
"    {\"/\",true,NULL,NULL,NULL,File_Root},\n"
"    {\"/SomeStyle.css\",false,NULL,NULL,NULL,File_SomeStyle},\n"
"    {\"/quit.html\",true,NULL,NULL,NULL,File_Quit},\n"
"};\n"
"</div>\n"
"\n"
"<p>Here we have changed the root page to be dynamic (true) instead of static\n"
"(false).  Otherwize it stays the same.</p>\n"
"\n"
"<div class='code'>"
"const char RootHTML_Start[]=\n"
"\"&lt;!DOCTYPE html&gt;\"\n"
"\"&lt;html&gt;\"\n"
"\"&lt;head&gt;\"\n"
"    \"&lt;title&gt;Bitty HTTP - Root&lt;/title&gt;\"\n"
"    \"&lt;link rel='stylesheet' href='/SomeStyle.css'&gt;\"\n"
"\"&lt;/head&gt;\"\n"
"\"&lt;body&gt;\"\n"
"    \"&lt;div id='top'&gt;Bitty HTTP Example - Root&lt;/div&gt;\"\n"
"    \"&lt;div id='quitbttn'&gt;&lt;a href='/quit.html'&gt;QUIT&lt;/a&gt;&lt;/div&gt;\"\n"
"    \"&lt;div id='content'&gt;\";\n"
"const char RootHTML_End[]=\n"
"    \"&lt;/div&gt;\"\n"
"\"&lt;div id='bottom'&gt;&lt;/div&gt;\"\n"
"\"&lt;/body&gt;\"\n"
"\"&lt;/html&gt;\";\n"
"\n"
"void File_Root(struct WebServer *Web)\n"
"{\n"
"    static int PageLoads=0;\n"
"    char buff[100];\n"
"\n"
"    WS_WriteChunk(Web,RootHTML_Start,sizeof(RootHTML_Start)-1);\n"
"\n"
"    WS_WriteChunk(Web,\"This example shows dynamic content using \"\n"
"            \"WS_WriteChunk().&lt;br/&gt;\",62);\n"
"\n"
"    sprintf(buff,\"You have loaded this page %d times\",PageLoads++);\n"
"\n"
"    WS_WriteChunk(Web,buff,strlen(buff));\n"
"\n"
"    WS_WriteChunk(Web,RootHTML_End,sizeof(RootHTML_End)-1);\n"
"}\n"
"</div>\n"
"\n"
"<p>The root function has been changed to output the number of times the page\n"
"has been load since the program was started.</p>\n"
"\n"
"<p>We start by outputing the start of the HTML we want to send from the\n"
"<span class='coderef'>RootHTML_Start</span> variable.  We use the\n"
"<span class='coderef'>WS_WriteChunk()</span> function instead of\n"
"the <span class='coderef'>WS_WriteWhole()</span> function.</p>\n"
"\n"
"<p>You can only use <span class='coderef'>WS_WriteChunk()</span> OR\n"
"<span class='coderef'>WS_WriteWhole()</span> as they change how the\n"
"HTTP reply is sent and can not be mixed.</p>\n"
"\n"
"<p>We then send a descrition line of text using a const string of 62\n"
"bytes in length.</p>\n"
"\n"
"<p>Next we print a line into a string (<span class='coderef'>buff</span>)\n"
"which includes the number of times this function has been called and we\n"
"call WS_WriteChunk() passing the buffer.  Note that this uses strlen()\n"
"instead of sizeof().  Sizeof only works on static const data.</p>\n"
"\n"
"<p>Last we send the end of the page from the global variable\n"
"<span class='coderef'>RootHTML_End</span>.</p>\n"
"";

void File_Doc_DynamicContent(struct WebServer *Web)
{
    WS_WriteChunk(Web,m_DynamicContentHTML,sizeof(m_DynamicContentHTML)-1);
    OutputListOfExampleFiles(Web,e_ExampleCode_DynamicContent);
    WS_WriteChunk(Web,m_DynamicContentHTML2,sizeof(m_DynamicContentHTML2)-1);
}
