/*******************************************************************************
 * FILENAME: FAQ.c
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
#include "Pages/Pages.h"
#include "Common/Headers.h"

/*** DEFINES                  ***/

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/

/*** FUNCTION PROTOTYPES      ***/

/*** VARIABLE DEFINITIONS     ***/

const char m_FAQHTML[]=
"<ul>\n"
"<li><a href='#1'>Can I just use "PRODUCTNAME" in my product?</a></li>\n"
"<li><a href='#2'>How do I compile this thing?</a></li>\n"
"<li><a href='#3'>What is the most useful uses of "PRODUCTNAME"?</a></li>\n"
"<li><a href='#4'>What about SSL/TLS?</a></li>\n"
"<li><a href='#5'>Why is this web site running under "PRODUCTNAME" instead "
"of a <b>real</b> web server?</a></li>\n"
"</ul>\n"
"<a id='1' class='anchor'></a>"
"<h1><span>1</span>Can I just use "PRODUCTNAME" in my product?</h1>\n"
"<p>Yes.  You don't have to any thing except keep the Copyright message at "
"the top of the files.</p>"
"<p>It would be nice if you linked back to this web site from your web site, "
"but it isn't a requirement</p>"
""
"<a id='2' class='anchor'></a>"
"<h1><span>2</span>How do I compile this thing?</h1>\n"
"<p>There are only two C files needed (plus your code for main() and what files "
"to serve).</p>"
"<ul>\n"
"<li>src/SocketsCon.c</li>\n"
"<li>src/WebServer.c</li>\n"
"</ul>\n"
"<p>See the hello world example for a full example of compiling, but it is "
"basically:</p>"
"<p><span class='coderef'>gcc src/SocketsCon.c src/WebServer.c "
"YOURFILE.c</span></p>"
""
"<a id='3' class='anchor'></a>"
"<h1><span>3</span>What is the most useful uses of "PRODUCTNAME"?</h1>\n"
"<p>"PRODUCTNAME" was originally build to be used in small micro controller "
"embedded systems with odd TCP/IP stacks, however it turns out that "
"embedding it in small utility programs (written in C) has be very useful.</p>\n"
"<p>For example if you had a simple program that listens on a socket and sends "
"every thing that comes in out a serial port, it is very useful to add "
"a web server on another port to be able see current status and even monitor "
"traffic sent though the connection.</p>"
"<p>This is the kind of program that you normally wouldn't bother with a UI "
"for (especially if it was on a remove computer), but having a simple way "
"to throw a status page on it is <b>very</b> useful (no external files are "
" needed keeping it simple).</p>"
""
"<a id='4' class='anchor'></a>"
"<h1><span>4</span>What about SSL/TLS?</h1>\n"
"<p>The web server will work with SSL.  However you would need to change "
"<span class='coderef'>SocketsCon.c</span> to add calls the the SSL library "
"and register your cert.</p>"
"<p>In fact <span class='coderef'>SocketsCon.c</span> was inspired by a "
"design that was used to provide SSL/Normal socket access dynamically "
"without having to change the main code.</p>"
"<p>It was setup so when you opened your socket with "
"<span class='coderef'>SocketsCon_InitSockCon()</span>\n"
"you provided if you wanted to use SSL or not.</p>"
"<p>At some point I may release a version of "
"<span class='coderef'>SocketsCon.c</span> that supports SSL</p>"
""
"<a id='5' class='anchor'></a>"
"<h1><span>5</span>Why is this web site running under "PRODUCTNAME" instead "
"of a real web server?</h1>\n"
"<p>Mostly because I could.</p>"
"<p>Also it provides a larger example (albeit not the cleanest one).</p>"
"";

void File_FAQ(struct WebServer *Web)
{
    WS_WriteChunk(Web,m_FAQHTML,sizeof(m_FAQHTML)-1);
}
