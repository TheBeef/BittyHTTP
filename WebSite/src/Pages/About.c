/*******************************************************************************
 * FILENAME: About.c
 *
 * PROJECT:
 *    Bitty HTTP
 *
 * FILE DESCRIPTION:
 *    This file has the about page in it.
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

const char m_AboutHTML[]=
"<h1><span>1</span>What is "PRODUCTNAME"</h1>\n"
"<p>"PRODUCTNAME" is a small light weight web server with the basic handling "
"of common HTML methods.</p>\n"
"<p>It is designed to serve web pages directly from the same C code as the "
"web server it's self.</p>"

"<h1><span>2</span>What "PRODUCTNAME" isn't</h1>\n"
"<p>"PRODUCTNAME" isn't a general purpose web server.  It doesn't support "
"CGI, URL rewriting, URL redirection, virtual servers, "
"load balancing, or any other feature you would expect in a web server.</p>\n"

"<h1><span>3</span>Project Goals</h1>\n"
"The core goals of "PRODUCTNAME" are:\n"
"<ul>"
"<li>Written in 100% C</li>\n"
"<li>No OS needed</li>\n"
"<li>No threads needed</li>\n"
"<li>Non blocking</li>\n"
"<li>Works with non standard socket interfaces</li>\n"
"<li>No file system needed</li>\n"
"<li>No external dependencies (beyond C std libary)</li>\n"
"<li>Easily embedded in to C applications</li>\n"
"</ul>"
"\n"

"<h1><span>4</span>Feature List</h1>\n"
"The current feature list for "PRODUCTNAME" is:\n"
"<ul>"
"<li>Written in C</li>\n"
"<li>Supports HTTP 1.1</li>\n"
"<li>Handles GET</li>\n"
"<li>Handles POST</li>\n"
"<li>Handles reading cookies</li>\n"
"<li>Handles setting cookies</li>\n"
"<li>Handles caching (using ETAG)</li>\n"
"<li>Handles sending custom http headers</li>\n"
"<li>Suitable for embedded systems</li>\n"
"</ul>"
"\n"
"<h2>Unsupported features</h2>\n"
"\n"
"<ul>"
"<li>File upload (multipart/form-data)</li>\n"
"<li>HTTP 2.0</li>\n"
"</ul>"

"<h1><span>5</span>Why</h1>\n"

"<p>"PRODUCTNAME" was started when I was looking around for a web server to "
"replace the Microchip supplied one that came with one of there PICs. After "
"looking around I could not find one that did all the things I needed (runs "
"with a non standard socket interface, no threads, static memory use, "
"supports GET,POST, and Cookies).</p>\n"

"<p>I wanted to just write my own because \"how hard could it be\", but my "
"manager insisted it was \"too hard\" and told me to stick with Microchip "
"one. After much hacking to force it to work with dynamic content (it was "
"really designed for mostly static content) I got it working.</p>\n"

"<p>I was annoyed by the whole \"too hard\" vs \"how hard could it be\" "
"discussion so I spent a bunch of time looking into all the details of "
"how http/1.1 worked. Turns out it's not that hard (however finding the "
"info isn't so easy).</p>\n"

"<p>A few years later I wanted a web server again.  Again I looked around "
"and nothing (that I could find anyway) that fit my needs. The \"too hard\" "
"discussion was still bugging me so I desided to see how long it would take "
"to write a web server from nothing. One day later I had a basic web server "
"up and running with GET and Cookie support. The code was not all that "
"clean but it was still only 1 day to write one.</p>\n"

"<p>I started embedding this web server into all kind of projects, and it "
"turned out to be really handy. So I decided to clean it up by rewriting it "
"and to release the rewrite as an open source project.</p>\n"

"<p>I kept the low memory foot print, threadless, non blocking, non "
"standard sockets design and added support for POST.  "PRODUCTNAME" is "
"the result of all that.</p>\n";

void File_About(struct WebServer *Web)
{
    WS_WriteChunk(Web,m_AboutHTML,sizeof(m_AboutHTML)-1);
}
