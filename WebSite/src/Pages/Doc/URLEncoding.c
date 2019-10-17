/*******************************************************************************
 * FILENAME: URLEncoding.c
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

const char m_URLEncodingVarsHTML[]=
"<h1><span>1</span>Encoding/Decoding URLs</h1>\n"
"<p>This example will show using the functions for encoding and decoding\n"
"URLs.  This is also known as Percent-encoding and is basically escaping\n"
"a string for use on the URL line.</p>"
"<p>This is needed when you build links to other pages and other places where\n"
"you need to escape URL data</p>\n"
"<p>This example will use <span class='coderef'>WS_URLEncode()</span>, \n"
"<span class='coderef'>WS_URLDecode()</span>, and\n"
"<span class='coderef'>WS_URLDecodeInPlace()</span></p>\n"
"\n"
"<h2>Files</h2>";

const char m_URLEncodingVarsHTML2[]=
"<h2>FileServer.c</h2>\n"
"<p>In this example file server only serves simple page showing encoded\n"
"and decoded strings.</p>"
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
"\n"
"<p>This goes at the top and defines the 3 standard pages we serve.</p>\n"
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
"    char buff[300];\n"
"    const char *Msg=\"100% of chars are &lt;i&gt;escapable&lt;/i&gt;\";\n"
"    char EncodedStr[200];\n"
"    char DecodedStr[200];\n"
"\n"
"    WS_WriteChunk(Web,DisplayHTML_Start,sizeof(DisplayHTML_Start)-1);\n"
"\n"
"    sprintf(buff,\"Before Encoding:%s\",Msg);\n"
"    WS_WriteChunk(Web,buff,strlen(buff));\n"
"    WS_WriteChunk(Web,\"&lt;br/&gt;\",5);\n"
"\n"
"    WS_URLEncode(Msg,EncodedStr,sizeof(EncodedStr));\n"
"    sprintf(buff,\"After Encoding:%s\",EncodedStr);\n"
"    WS_WriteChunk(Web,buff,strlen(buff));\n"
"    WS_WriteChunk(Web,\"&lt;br/&gt;\",5);\n"
"\n"
"    WS_URLDecode(EncodedStr,DecodedStr,sizeof(DecodedStr));\n"
"    sprintf(buff,\"After Decoding:%s\",DecodedStr);\n"
"    WS_WriteChunk(Web,buff,strlen(buff));\n"
"    WS_WriteChunk(Web,\"&lt;br/&gt;\",5);\n"
"\n"
"    WS_URLDecodeInPlace(EncodedStr);\n"
"    sprintf(buff,\"After Decoding in place:%s\",EncodedStr);\n"
"    WS_WriteChunk(Web,buff,strlen(buff));\n"
"    WS_WriteChunk(Web,\"&lt;br/&gt;\",5);\n"
"\n"
"    WS_WriteChunk(Web,DisplayHTML_End,sizeof(DisplayHTML_End)-1);\n"
"}\n"
"</div>\n"
"\n"
"<p>The page starts off by writing out the string\n"
"\"100% of chars are &lt;i&gt;escapable&lt;/i&gt;\".</p>\n"
"<p>The <span class='coderef'>WS_URLEncode()</span> function is called to\n"
"encode the string as a URL string.  The output string will be placed in\n"
"the buffer <span class='coderef'>EncodedStr</span>.  This buffer should be\n"
"3 times the size of the source string because the string can be made up to\n"
"3 times bigger.  In this case the string is 34 bytes and the output\n"
"buffer is 200 bytes long.  The last argument to\n"
"<span class='coderef'>WS_URLEncode()</span> is the size of the output buffer\n"
"</p>"
"<p>The next thing the example does is decode the string we just encoded\n"
"using the <span class='coderef'>WS_URLDecode()</span> function.  This will\n"
"take a URL encoded string and convert it back to a normal string.  Again\n"
"The output string will be stored in <span class='coderef'>DecodedStr</span>\n"
"The last argument to <span class='coderef'>WS_URLDecode()</span> is the\n"
"size of the output buffer\n"
"</p>"
"<p>Finally the <span class='coderef'>WS_URLDecodeInPlace()</span> function\n"
"is used to decode the string again.  This time the input buffer is used to\n"
"store the new string.  This works because the decoded string will always\n"
"be shorter than the source string.</p>\n"
"";

void File_Doc_URLEncodingVars(struct WebServer *Web)
{
    WS_WriteChunk(Web,m_URLEncodingVarsHTML,sizeof(m_URLEncodingVarsHTML)-1);
    OutputListOfExampleFiles(Web,e_ExampleCode_URLEncode);
    WS_WriteChunk(Web,m_URLEncodingVarsHTML2,sizeof(m_URLEncodingVarsHTML2)-1);
}
