/*******************************************************************************
 * FILENAME: TheBasics.c
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

const char m_TheBasicsHTML[]=
"<h1><span>1</span>The Basics</h1>\n"
"Here we are going to go over what files you will need and how to build the example.\n"
"\n"
"The basic list of files needed in the examples are (and their .h files):\n"
"\n"
"<ul>\n"
"<li>main.c</li>\n"
"<li>Options.h</li>\n"
"<li>WebServer.c</li>\n"
"<li>WebServer.h</li>\n"
"<li>SocketsCon.c</li>\n"
"<li>SocketsCon.h</li>\n"
"<li>FileServer.c</li>\n"
"</ul>\n"
"<p>These are in the examples directorys</p>"
"<h2>Building</h2>\n"
"All the examples are built with gcc using a line like:<br/>\n"
"\n"
"<div class='code'>"
"gcc main.c SocketsCon.c FileServer.c WebServer.c -o example.exe\n"
"</div>\n"
"\n"
"<p>To keep the examples simple there are just simple build.sh scripts \n"
"in the example directories. These scripts are a single line that just \n"
"runs GCC directly. This could have been done with a makefile but a script \n"
"is simpler.</p>\n"
"\n"
"<h2>main.c</h2>\n"
"<p>The main.c file is where main() lives. This is the heart of your program\n"
"and in our case will call the init functions and enter a while(1) loop.\n"
"We also have misc function needed by the web server.</p>\n"
"<h2>Options.h</h2>\n"
"<p>This file has defines in it that are used to customize the web server.</p>\n"
"\n"
"<h2>WebServer.c</h2>\n"
"<p>This is the work horse of the system. It handles accepting new connections, "
"process the HTTP requests, send any errors to the client, and call the "
"functions in FileServer.c to get requested web pages.</p>\n"
"\n"
"The API functions in this file are:<br/>\n"
"<table class='FnDescTable'>"
"<tr><td>WS_Init()</td><td>Init the web server</td></tr>\n"
"<tr><td>WS_Shutdown()</td><td>Shut down the web server</td></tr>\n"
"<tr><td>WS_Start()</td><td>Start listening for incoming connections</td></tr>\n"
"<tr><td>WS_Tick()</td><td>Called in the main loop. Runs the web server</td></tr>\n"
"<tr><td>WS_WriteWhole()</td><td>Write a static page</td></tr>\n"
"<tr><td>WS_WriteChunk()</td><td>Write some of page using chunked HTTP data</td></tr>\n"
"<tr><td>WS_Header()</td><td>Add a HTTP header</td></tr>\n"
"<tr><td>WS_GET()</td><td>Read a GET var</td></tr>\n"
"<tr><td>WS_COOKIE()</td><td>Read a cookie</td></tr>\n"
"<tr><td>WS_POST()</td><td>Read a POST var</td></tr>\n"
"<tr><td>WS_SetCookie()</td><td>Set a cookie</td></tr>\n"
"<tr><td>WS_URLEncode()</td><td>Encode a string for use as a URL</td></tr>\n"
"<tr><td>WS_URLDecode()</td><td>Decode a string from a URL</td></tr>\n"
"<tr><td>WS_URLDecodeInPlace()</td><td>Decode a string from a URL writting back out to the same buffer</td></tr>\n"
"</table>\n"
"<h2>WebServer.h</h2>\n"
"<p>This file has the access function prototypes and other needed things for \n"
"the web server.</p>\n"
"\n"
"It includes the following call back functions that will be called when the \n"
"web server needs something:<br/>\n"
"<table class='FnDescTable'>\n"
"<tr><td>FS_GetFileProperties()</td><td>Get info about the requested file (not the file contents)</td></tr>\n"
"<tr><td>FS_SendFile()</td><td>Send the contents of the file that was looked up with FS_GetFileProperties()</td></tr>\n"
"<tr><td>ReadElapsedClock()</td><td>Get the number of seconds elapsed since the time this function was called</td></tr>\n"
"</table>\n"
"\n"
"<p>These will be described later in the FileServer.c and main.c descritions.</p>\n"
"\n"
"<h2>SocketsCon.c</h2>\n"
"This is a wrapper file around the sockets interface. It does 3 things:<br/>\n"
"<ul>\n"
"    <li>it allows the web server to use non standard socket interfaces (this does happen)</li>\n"
"    <li>it changes everything over to nonblocking calls</li>\n"
"    <li>it can be used to handle SSL sockets without having to change the main web server code (you only have to call SocketsCon?_Read() instead of read() or SSL_read())</li>\n"
"</ul>\n"
"\n"
"<h2>FileServer.c</h2>\n"
"<p>This is where the callbacks for processing page requests live.</p>\n"
"This file has the following callback functions in it:<br/>\n"
"<table class='FnDescTable'>\n"
"<tr><td>FS_GetFileProperties()</td><td>This is called when the first line in the HTTP request is processed. It is to return info about this page (like if it should be cached, what GET/POST/COOKIE vars this page is going to use, etc)</td></tr>\n"
"<tr><td>FS_SendFile()</td><td>This is called when the you should send the contents of the requested page (as setup in FS_GetFileProperties())</td></tr>\n"
"</table>\n"
"\n"
"<p>In the examples we also have the functions to send the each page.</p>\n"
"\n"
"";


void File_Doc_TheBasics(struct WebServer *Web)
{
    WS_WriteChunk(Web,m_TheBasicsHTML,sizeof(m_TheBasicsHTML)-1);
}
