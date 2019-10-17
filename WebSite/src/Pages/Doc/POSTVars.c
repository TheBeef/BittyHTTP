/*******************************************************************************
 * FILENAME: POSTVars.c
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

const char m_POSTVarsHTML[]=
"<h1><span>1</span>Reading POST vars</h1>\n"
"<p>This example will show reading POST vars.  These are basically the same\n"
"as GET vars but using <span class='coderef'>WS_POST()</span> instead of\n"
"<span class='coderef'>WS_GET()</span></p>\n"
"\n"
"<p>"PRODUCTNAME" stores POST vars in a block of RAM as the headers are \n"
"processed (just after the GET vars).  This means it needs to know the names\n"
"of all the POST vars before the page is requested.  This is done by\n"
"filling in the <span class='coderef'>struct WSPageProp.Posts</span> variable \n"
"when the page properties are requested.</p>\n"
"\n"
"<p>The <span class='coderef'>Posts</span> property (just like the\n"
"<span class='coderef'>Gets</span>) is an array of pointers \n"
"to strings with the last one being set to NULL to mark the end of the list.\n"
"This list is scanned when the page is requested and the value of any \n"
"vars in this list are added to a RAM array.</p>\n"
"\n"
"<p>You then call <span class='coderef'>WS_POST()</span> to get the value \n"
"that was saved (or NULL if it wasn't found).</p>\n"
"\n"
"<p>Using things this way means a low memory foot print as we only remember \n"
"vars that we are going to pull out later.</p>\n"
"\n"
"<h2>Files</h2>";

const char m_POSTVarsHTML2[]=
"<h2>FileServer.c</h2>\n"
"<p>The file server is changed to provide a form on the root page and a \n"
"new page to display the values from the form.</p>\n"
"\n"
"<div class='code'>"
"const char *PostArgs[]=\n"
"{\n"
"    \"Name\",\n"
"    NULL\n"
"};\n"
"</div>\n"
"\n"
"<p>We add a list of POST vars that we may want to read when processing a \n"
"page later.  We end the list with NULL to mark the end of the list.  The \n"
"code will loop though this list looking for a NULL entry to stop at.</p>\n"
"\n"
"<p>When a match is made the value of the var will be copied to an \n"
"internal RAM buffer.</p>\n"
"\n"
"<div class='code'>"
"struct FileInfo m_Files[]=\n"
"{\n"
"    /* Filename, Dynamic, Cookies, Gets, Posts, Callback */\n"
"    {\"/\",false,NULL,NULL,NULL,File_Root},\n"
"    {\"/Display.html\",true,NULL,NULL,PostArgs,File_Display},\n"
"    {\"/SomeStyle.css\",false,NULL,NULL,NULL,File_SomeStyle},\n"
"    {\"/quit.html\",true,NULL,NULL,NULL,File_Quit},\n"
"};\n"
"</div>\n"
"\n"
"<p>A new page has been added called <span class='coderef'>/Display.html</span>\n"
"that will display what the user has typed into the form from the root \n"
"page.  This includes a pointer to the <span class='coderef'>PostArgs</span>\n"
"as the 5'th argument.  If you wanted to use both GET and POST vars you\n"
"would provide to different arrays (one for <span class='coderef'>POST</span>"
"and one for <span class='coderef'>GET</span> vars).</p>\n"
"\n"
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
"        \"POST example&lt;br/&gt;\"\n"
"        \"&lt;br/&gt;\"\n"
"        \"&lt;form action='/Display.html' method='POST'&gt;\"\n"
"        \"Input your name:&lt;input name='Name'&gt;&lt;/input&gt; \"\n"
"        \"&lt;input type='submit'&gt;&lt;/input&gt;\"\n"
"        \"&lt;/form&gt;\"\n"
"        \"&lt;br/&gt;\"\n"
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
"<p>This now just outputs a basic form with a get method asking the user for \n"
"their name and going to /Display.html.</p>\n"
"\n"
"<div class='code'>"
"const char DisplayHTML_Start[]=\n"
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
"const char DisplayHTML_End[]=\n"
"    \"&lt;/div&gt;\"\n"
"\"&lt;div id='bottom'&gt;&lt;/div&gt;\"\n"
"\"&lt;/body&gt;\"\n"
"\"&lt;/html&gt;\";\n"
"\n"
"void File_Display(struct WebServer *Web)\n"
"{\n"
"    char buff[100];\n"
"    const char *Name;\n"
"\n"
"    WS_WriteChunk(Web,DisplayHTML_Start,sizeof(DisplayHTML_Start)-1);\n"
"\n"
"    Name=WS_POST(Web,\"Name\");\n"
"    if(Name==NULL)\n"
"    {\n"
"        WS_WriteChunk(Web,\"Name was not set.\",17);\n"
"    }\n"
"    else\n"
"    {\n"
"        sprintf(buff,\"Your name is:%s\",Name);\n"
"        WS_WriteChunk(Web,buff,strlen(buff));\n"
"    }\n"
"\n"
"    WS_WriteChunk(Web,\"&lt;br/&gt;&lt;br/&gt;&lt;a href='/'&gt;Try again&lt;/a&gt;\",35);\n"
"    WS_WriteChunk(Web,\"&lt;br/&gt;\",5);\n"
"\n"
"    WS_WriteChunk(Web,DisplayHTML_End,sizeof(DisplayHTML_End)-1);\n"
"}\n"
"</div>\n"
"\n"
"<p><span class='coderef'>File_Display()</span> uses "
"<span class='coderef'>WS_POST()</span> to read out the get vars from \n"
"internal RAM.  You call it with the name of the POST var to read.  \n"
"This name also has to be in the <span class='coderef'>PostArgs</span> "
"array as well.</p>\n"
"\n"
"<p>If <span class='coderef'>WS_POST()</span> does not find the var (because "
" it wasn't passed in) it returns NULL.</p>\n"
"\n"
"<p>It <span class='coderef'>WS_POST()</span> does find the var then "
"it returns a string pointer to the value that was read.</p>\n"
"";

void File_Doc_POSTVars(struct WebServer *Web)
{
    WS_WriteChunk(Web,m_POSTVarsHTML,sizeof(m_POSTVarsHTML)-1);
    OutputListOfExampleFiles(Web,e_ExampleCode_POSTVars);
    WS_WriteChunk(Web,m_POSTVarsHTML2,sizeof(m_POSTVarsHTML2)-1);
}
