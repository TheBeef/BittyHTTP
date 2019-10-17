/*******************************************************************************
 * FILENAME: Error404.c
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
 *    Paul Hutchinson (29 Aug 2019)
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

const char m_Error404HTML[]=
"<h1><span>1</span>404 Errors</h1>\n"
"<p>This example will show handling a page not found error.</p>\n"
"\n"
"<p>We handle 404 Errors in the <span class='coderef'>FS_SendFile()</span>\n"
"function.  Basicly when <span class='coderef'>FS_GetFileProperties()</span>\n"
"is called if we do not find the requested page and we set the FileID to\n"
"0 (NULL).  Then when <span class='coderef'>FS_SendFile()</span> is called\n"
"we detect that the FileID is set to NULL and send a 404 error page.</p>\n"
"\n"
"<h2>Files</h2>";

const char m_Error404HTML2[]=
"<h2>FileServer.c</h2>\n"
"<p>The file server is updated to have the 3 basic pages plus an error\n"
"page that we send if the user goes to an unknown page.</p>\n"
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
"<p>We setup the 3 known pages (css, quit, and root).</p>\n"
"\n"
"<div class='code'>"
"bool FS_GetFileProperties(const char *Filename,struct WSPageProp *PageProp)\n"
"{\n"
"    int r;\n"
"\n"
"    PageProp-&gt;FileID=0;\n"
"    for(r=0;r&lt;sizeof(m_Files)/sizeof(struct FileInfo);r++)\n"
"    {\n"
"        if(strcmp(Filename,m_Files[r].Filename)==0)\n"
"        {\n"
"            PageProp-&gt;FileID=(uintptr_t)&m_Files[r];\n"
"            PageProp-&gt;DynamicFile=m_Files[r].Dynamic;\n"
"            PageProp-&gt;Cookies=m_Files[r].Cookies;\n"
"            PageProp-&gt;Gets=m_Files[r].Gets;\n"
"            PageProp-&gt;Posts=m_Files[r].Posts;\n"
"            return true;\n"
"        }\n"
"    }\n"
"    return true;\n"
"}\n"
"</div>\n"
"\n"
"<p>The <span class='coderef'>FS_GetFileProperties()</span> function is\n"
"changed to set <span class='coderef'>PageProp-&gt;FileID</span> to 0 (NULL)\n"
"and always returns true even if the page was not found.  This is because\n"
"<span class='coderef'>FS_SendFile()</span> will send a 404 page if we didn't\n"
"find the page.</p>\n"
"\n"
"<div class='code'>"
"void FS_SendFile(struct WebServer *Web,uintptr_t FileID)\n"
"{\n"
"    struct FileInfo *File=(struct FileInfo *)FileID;\n"
"\n"
"    if(File==NULL)\n"
"    {\n"
"        File_Error404(Web);\n"
"        return;\n"
"    }\n"
"\n"
"    File->WriteFile(Web);\n"
"}\n"
"</div>\n"
"\n"
"<p>The <span class='coderef'>FS_SendFile()</span> is changed to call\n"
"<span class='coderef'>File_Error404()</span> if File==NULL (page not found).\n"
"If it isn't NULL then the page is sent as normal.</p>\n"
"\n"
"<div class='code'>"
"const char Error404HTML[]=\n"
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
"        \"&lt;h1 style='text-align:center;font-size:10em;margin:0'&gt;404&lt;/h1&gt;\"\n"
"        \"&lt;h3 style='text-align:center'&gt;Oops! Page not found&lt;/h3&gt;\"\n"
"        \"&lt;br/&gt;\"\n"
"    \"&lt;/div&gt;\"\n"
"\"&lt;div id='bottom'&gt;&lt;/div&gt;\"\n"
"\"&lt;/body&gt;\"\n"
"\"&lt;/html&gt;\";\n"
"\n"
"void File_Error404(struct WebServer *Web)\n"
"{\n"
"    WS_SetHTTPStatusCode(Web,e_ReplyStatus_NotFound);\n"
"    WS_WriteWhole(Web,Error404HTML,sizeof(Error404HTML)-1);\n"
"}\n"
"</div>\n"
"\n"
"<p>This is the 404 error page.  It is sent like any normal page.</p>\n"
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
"        \"GET example&lt;br/&gt;\"\n"
"        \"&lt;br/&gt;\"\n"
"        \"&lt;a href='/nopagehere.html'&gt;Non existing page&lt;/a&gt;\"\n"
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
"<p>This is the root page.  It simply displays a page with a link to a page\n"
"that doesn't exist (/nopagehere.html).</p>"
"";

void File_Doc_Error404(struct WebServer *Web)
{
    WS_WriteChunk(Web,m_Error404HTML,sizeof(m_Error404HTML)-1);
    OutputListOfExampleFiles(Web,e_ExampleCode_404Error);
    WS_WriteChunk(Web,m_Error404HTML2,sizeof(m_Error404HTML2)-1);
}
