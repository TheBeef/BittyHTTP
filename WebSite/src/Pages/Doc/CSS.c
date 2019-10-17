/*******************************************************************************
 * FILENAME: CSS.c
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

const char m_CSSHTML[]=
"<h1><span>1</span>CSS</h1>\n"
"<p>This example will show handling sending of different files. It adds a CSS\n"
"file and a quit page to exit the program we started with\n"
"<a href='/Doc/HelloWorld.html'>Hello World</a>.</p>\n"
"\n"
"<h2>Files</h2>";

const char m_CSSHTML2[]=
"<h2>FileServer.c</h2>\n"
"<p>We update the file server file to have 3 functions that get called\n"
"when a page is requested.</p>\n"
"\n"
"<div class='code'>"
"void File_Root(struct WebServer *Web);\n"
"void File_SomeStyle(struct WebServer *Web);\n"
"void File_Quit(struct WebServer *Web);\n"
"\n"
"struct FileInfo m_Files[]=\n"
"{\n"
"    /* Filename, Dynamic, Cookies, Gets, Posts, Callback */\n"
"    {\"/\",false,NULL,NULL,NULL,File_Root},\n"
"    {\"/SomeStyle.css\",false,NULL,NULL,NULL,File_SomeStyle},\n"
"    {\"/quit.html\",true,NULL,NULL,NULL,File_Quit},\n"
"};\n"
"</div>"
"\n"
"<p>The File_Root() function is called when the root page (\"/\" or when\n"
"the URL doesn't include a filename). This will output a &lt;link&gt;\n"
"tag that will include the \"SomeStyle.css\" file. It will also have a\n"
"link to the \"quit.html\" file.</p>\n"
"\n"
"<p>The first entry is the URL path of the file name. This will be the\n"
"filename part after the host name (http://example.com/SomeStyle.css\n"
"for example). This will always include the forward slash.</p>\n"
"\n"
"<p>Next we have if the file is dynamic or not. If it is dynamic then the\n"
"callback will ALWAYS be called. If it is static (not dynamic) then the\n"
"callback may or may not be called depending on if the web browser has\n"
"a good copy or not.</p>\n"
"\n"
"<p>We mark the \"/\" and \"/SomeStyle.css\" pages as being static. The\n"
"content does not change so the browser can cache it.</p>\n"
"\n"
"<p>The \"/quit.html\" is marked as dynamic even though the content is\n"
"static. This is because we need to have the callback called every\n"
"time so we can exit the program.</p>\n"
"\n"
"<p>Next we have 3 NULL's because we do not have any cookies, GET, or\n"
"POST vars on these pages.</p>\n"
"\n"
"<p>Last we have the function pointer to call to sent the contents of the\n"
"page.</p>\n"
"\n"
"<div class='code'>"
"const char RootHTML[]=\n"
"\"&lt;!DOCTYPE html&gt;\"\n"
"\"&lt;html&gt;\"\n"
"\"&lt;head&gt;\"\n"
"    \"&lt;title&gt;Web Server Example - Root&lt;/title&gt;\"\n"
"    \"&lt;link rel='stylesheet' href='/SomeStyle.css'&gt;\"\n"
"\"&lt;/head&gt;\"\n"
"\"&lt;body&gt;\"\n"
"    \"&lt;div id='top'&gt;Web Server Example - Root&lt;/div&gt;\"\n"
"    \"&lt;div id='quitbttn'&gt;&lt;a href='/quit.html'&gt;QUIT&lt;/a&gt;&lt;/div&gt;\"\n"
"    \"&lt;div id='content'&gt;\"\n"
"        \"Hello World with some style!\n\"\n"
"    \"&lt;/div&gt;\"\n"
"\"&lt;div id='bottom'&gt;&lt;/div&gt;\"\n"
"\"&lt;/body&gt;\"\n"
"\"&lt;/html&gt;\";\n"
"\n"
"void File_Root(struct WebServer *Web)\n"
"{\n"
"    WS_WriteWhole(Web,RootHTML,sizeof(RootHTML)-1);\n"
"}\n"
"</div>"
"\n"
"<p>The <span class='coderef'>File_Root()</span> function has been changed\n"
"to have a bit more complex html. The html includes a css link\n"
"to \"/SomeStyle.css\" and a html link to the \"/quit.html\" file.</p>\n"
"\n"
"<p>NOTE that if you running this after running a different example you\n"
"will need to force a cache ignore (SHIFT+F5) or change the\n"
"<span class='coderef'>DOCVER</span> define in Options.h.</p>\n"
"\n"
"<div class='code'>"
"const char QuitHTML[]=\n"
"\"&lt;!DOCTYPE html&gt;\"\n"
"\"&lt;html&gt;\"\n"
"\"&lt;head&gt;\"\n"
"    \"&lt;title&gt;Web Server Example - Quit&lt;/title&gt;\"\n"
"    \"&lt;link rel='stylesheet' href='/SomeStyle.css'&gt;\"\n"
"\"&lt;/head&gt;\"\n"
"\"&lt;body&gt;\"\n"
"    \"&lt;div id='top'&gt;Web Server Example&lt;/div&gt;\"\n"
"    \"&lt;div id='content'&gt;\"\n"
"        \"&lt;br/&gt;\"\n"
"        \"Bye bye&lt;br/&gt;\"\n"
"        \"&lt;br/&gt;\"\n"
"        \"&lt;a href='/'&gt;HOME&lt;/a&gt;\"\n"
"        \"&lt;br/&gt;\"\n"
"    \"&lt;/div&gt;\"\n"
"\"&lt;div id='bottom'&gt;&lt;/div&gt;\"\n"
"\"&lt;/body&gt;\"\n"
"\"&lt;/html&gt;\";\n"
"void File_Quit(struct WebServer *Web)\n"
"{\n"
"\n"
"    WS_WriteWhole(Web,QuitHTML,sizeof(QuitHTML)-1);\n"
"\n"
"    g_Quit=true;\n"
"}\n"
"</div>"
"\n"
"<p>We add a new function for quiting the program with the\n"
"<span class='coderef'>File_Quit()</span> function.\n"
"It sends the quit html and then sets a global var to \"true\" to quit.</p>\n"
"\n"
"<div class='code'>"
"const char CSS[]=\n"
"\"div#top\"\n"
"\"{\"\n"
"    \"height:50px;\"\n"
"    \"width:100%;\"\n"
"    \"background-color:#679509;\"\n"
"    \"font-size:1.5em;\"\n"
"    \"line-height:50px;\"\n"
"    \"padding-left:15px;\"\n"
"    \"color:white;\"\n"
"    \"text-shadow:#4F4F4F 2px 2px;\"\n"
"\"}\n\"\n"
"\"div#quitbttn\"\n"
"\"{\"\n"
"    \"position:absolute;\"\n"
"    \"top:23px;\"\n"
"    \"right:30px;\"\n"
"\"}\n\"\n"
"\"div#quitbttn a\"\n"
"\"{\"\n"
"    \"color:white;\"\n"
"    \"text-decoration:none\"\n"
"\"}\n\"\n"
"\"div#quitbttn a:hover\"\n"
"\"{\"\n"
"    \"text-decoration:underline\"\n"
"\"}\n\"\n"
"\"div#bottom\"\n"
"\"{\"\n"
"    \"position:absolute;\"\n"
"    \"bottom:0px;\"\n"
"    \"left:0px;\"\n"
"    \"height:50px;\"\n"
"    \"width:100%;\"\n"
"    \"background-color:#679509;\"\n"
"\"}\n\"\n"
"\"div#content\"\n"
"\"{\"\n"
"    \"background-color:#f0f0f0;\"\n"
"    \"color:#6A6A6A;\"\n"
"\"}\n\";\n"
"\n"
"void File_SomeStyle(struct WebServer *Web)\n"
"{\n"
"    WS_WriteWhole(Web,CSS,sizeof(CSS)-1);\n"
"}\n"
"</div>"
"\n"
"<p>Finally we the \"/SomeStyle.css\" file with static CSS in it.</p>\n"
"";

void File_Doc_CSS(struct WebServer *Web)
{
    WS_WriteChunk(Web,m_CSSHTML,sizeof(m_CSSHTML)-1);
    OutputListOfExampleFiles(Web,e_ExampleCode_CSS);
    WS_WriteChunk(Web,m_CSSHTML2,sizeof(m_CSSHTML2)-1);
}
