/*******************************************************************************
 * FILENAME: Cookies.c
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

const char m_CookiesVarsHTML[]=
"<h1><span>1</span>Using Cookies</h1>\n"
"<p>This example will show reading and setting cookies from the server.\n"
"Reading cookies are basically the same as GET vars but using\n"
"<span class='coderef'>WS_COOKIE()</span> instead of\n"
"<span class='coderef'>WS_GET()</span></p>\n"
"\n"
"<p>"PRODUCTNAME" stores cookie values in a block of RAM as the headers are \n"
"processed (just after the POST vars).  This means it needs to know the names\n"
"of all the COOKIES before the page is requested.  This is done by\n"
"filling in the <span class='coderef'>struct WSPageProp.Cookies</span>\n"
"variable when the page properties are requested.</p>\n"
"\n"
"<p>The <span class='coderef'>Cookies</span> property (just like the\n"
"<span class='coderef'>Gets</span>) is an array of pointers\n"
"to strings with the last one being set to NULL to mark the end of the list.\n"
"This list is scanned when the page is requested and the value of any\n"
"vars in this list are added to a RAM array.</p>\n"
"\n"
"<p>You then call <span class='coderef'>WS_COOKIE()</span> to get the value\n"
"that was saved (or NULL if it wasn't found).</p>\n"
"\n"
"<p>Using things this way means a low memory foot print as we only remember\n"
"vars that we are going to pull out later.</p>\n"
"\n"
"<h2>Files</h2>";

const char m_CookiesVarsHTML2[]=
"<h2>FileServer.c</h2>\n"
"<p>The file server is changed to display the number of times the page has\n"
"been reloaded.  It uses a session cookie for the reload count, and a\n"
"cookie set to expire in 7 days for the all time reload count.</p>\n"
"\n"
"<div class='code'>"
"const char *CookieArgs[]=\n"
"{\n"
"    \"LoadCount\",\n"
"    \"LoadCountAllTime\",\n"
"    NULL\n"
"};\n"
"</div>\n"
"\n"
"<p>We add a list of COOKIES that we may want to read when processing a\n"
"page later.  We end the list with NULL to mark the end of the list.  The\n"
"code will loop though this list looking for a NULL entry to stop at.</p>\n"
"\n"
"<p>When a match is made the value of the var will be copied to an\n"
"internal RAM buffer.</p>\n"
"\n"
"<div class='code'>"
"struct FileInfo m_Files[]=\n"
"{\n"
"    /* Filename, Dynamic, Cookies, Gets, Posts, Callback */\n"
"    {\"/\",true,CookieArgs,NULL,NULL,File_Root},\n"
"    {\"/SomeStyle.css\",false,NULL,NULL,NULL,File_SomeStyle},\n"
"    {\"/quit.html\",true,NULL,NULL,NULL,File_Quit},\n"
"};\n"
"</div>\n"
"\n"
"<p>This include only the normal pages (SomeStyle.css, quit.html, and root)\n"
"The root page includes a pointer to the <span class='coderef'>Cookies</span>\n"
"as the 3'rd argument.  If you wanted to use GET or POST vars as well you\n"
"would provide pointers to different arrays (one for\n"
"<span class='coderef'>POST</span> or one for\n"
"the <span class='coderef'>GET</span> vars).</p>\n"
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
"void File_Root(struct WebServer *Web)\n"
"{\n"
"    char buff[100];\n"
"    const char *LoadCount;\n"
"    const char *LoadCountAllTime;\n"
"    int LoadCountInt;\n"
"    int LoadCountAllTimeInt;\n"
"\n"
"    LoadCount=WS_COOKIE(Web,\"LoadCount\");\n"
"    if(LoadCount==NULL)\n"
"        LoadCountInt=0;\n"
"    else\n"
"        LoadCountInt=atoi(LoadCount);\n"
"\n"
"    LoadCountAllTime=WS_COOKIE(Web,\"LoadCountAllTime\");\n"
"    if(LoadCountAllTime==NULL)\n"
"        LoadCountAllTimeInt=0;\n"
"    else\n"
"        LoadCountAllTimeInt=atoi(LoadCountAllTime);\n"
"\n"
"    LoadCountInt++;\n"
"    sprintf(buff,\"%d\",LoadCountInt);\n"
"    WS_SetCookie(Web,\"LoadCount\",buff,0,NULL,NULL,false,false);\n"
"\n"
"    LoadCountAllTimeInt++;\n"
"    sprintf(buff,\"%d\",LoadCountAllTimeInt);\n"
"    /* Expires in a week (60 sec * 60 min * 24 hours * 7 days) */\n"
"    WS_SetCookie(Web,\"LoadCountAllTime\",buff,time(NULL)+60*60*24*7,NULL,\n"
"            NULL,false,false);\n"
"\n"
"    WS_WriteChunk(Web,DisplayHTML_Start,sizeof(DisplayHTML_Start)-1);\n"
"\n"
"    sprintf(buff,\"Page loaded:%d times this session, and %d this week&lt;br/&gt;\",\n"
"            LoadCountInt,LoadCountAllTimeInt);\n"
"    WS_WriteChunk(Web,buff,strlen(buff));\n"
"\n"
"    WS_WriteChunk(Web,DisplayHTML_End,sizeof(DisplayHTML_End)-1);\n"
"}\n"
"</div>\n"
"\n"
"<p>This page starts by reading the <span class='coderef'>LoadCount</span>\n"
"cookie.  Using the <span class='coderef'>WS_COOKIE()</span> function.\n"
"<span class='coderef'>WS_COOKIES()</span> returns a string so it will need\n"
"to be converted to an int before we can work with it.\n</p>"
"<p>We first check that this cookie was found, and if not we set our var\n"
"<span class='coderef'>LoadCountInt</span> to 0.  If it was found then\n"
"we use <span class='coderef'>atoi()</span> to convert it to an int.</p>"
"<p>Next we do the same for the <span class='coderef'>LoadCountAllTime</span>\n"
"cookie placing the int in <span class='coderef'>LoadCountAllTimeInt</span>.</p>"
"<p>We then add 1 to <span class='coderef'>LoadCountInt</span> and convert it\n"
"back to a string in <span class='coderef'>buff</span>.  We then call\n"
"<span class='coderef'>WS_SetCookie()</span> to output a cookie.</p>"

"<p>The <span class='coderef'>WS_SetCookie()</span> has the following prototype:\n"
"<div class='code' style='margin-left:50px;width:94%;background-color:#FAEBD7'>"
"bool WS_SetCookie(struct WebServer *Web,const char *Name,const char *Value,"
"time_t Expire,const char *Path,const char *Domain,bool Secure,bool HttpOnly);\n"
"</div>"
"<p><span class='coderef'>Name</span> is the name of the cookie<br/>"
"<span class='coderef'>Value</span> is the value to set the cookie to as a string<br/>"
"<span class='coderef'>Expire</span> is a unix timestamp of when this cookie\n"
"will expire.  If it is set to 0 then it will be a session cookie.<br/>"
"<span class='coderef'>Path</span> is the path that this cookie is valid, NULL\n"
"means it will be ignored.<br/>"
"<span class='coderef'>Domain</span> is domain that this cookie is valid, NULL\n"
"means it will be ignored.<br/>"
"<span class='coderef'>Secure</span> is a bool that makes this cookie a secure cookie<br/>"
"<span class='coderef'>HttpOnly</span> is a bool that makes this cookie only avaiable to the server.<br/>"
"</p>"
"<p>For more details see the auto doc for <a href='#' style='color:red'>WS_SetCookie()</a>\n"
"<p>We set the <span class='coderef'>LoadCount</span> cookie as a session\n"
"cookie and set it's value to the buffer we just made.</p>"
"<p>We repeat the same thing for the\n"
"<span class='coderef'>LoadCountAllTime</span> cookie, except with this cookie\n"
"we set the expiry date as a week from now.  We do this by calling the time.h\n"
"function <span class='coderef'>time()</span> and add the number of seconds\n"
"in a week (60*60*24*7 or 604800 seconds).</p>"
"<p>Because the cookies must be set before the body is written we do this\n"
"all before we call <span class='coderef'>WS_WriteChunk()</span> with the\n"
"top part of the web page.</p>"
"<p>We then output a string telling the user how many times this page has\n"
"been loaded, and finish off the page.</p>"
"";

void File_Doc_CookiesVars(struct WebServer *Web)
{
    WS_WriteChunk(Web,m_CookiesVarsHTML,sizeof(m_CookiesVarsHTML)-1);
    OutputListOfExampleFiles(Web,e_ExampleCode_Cookies);
    WS_WriteChunk(Web,m_CookiesVarsHTML2,sizeof(m_CookiesVarsHTML2)-1);
}

