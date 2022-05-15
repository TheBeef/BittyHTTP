/*******************************************************************************
 * FILENAME: Links.c
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

const char m_LinksHTML[]=
"<h1><span>1</span>Links</h1>\n"
"<table>\n"

"<tr>\n"
"<td><a href='https://github.com/TheBeef/bittyhttp'>GitHub Project Page</a></td>\n"
"<td>The main project page for "PRODUCTNAME".</td>\n"
"</tr>\n"

"<tr>\n"
"<td><a href='https://www.gnu.org/software/libmicrohttpd/'>GNU Libmicrohttpd</a></td>\n"
"<td>A small C library for adding a http server to an existing application.  "
"It includes a list of other embedded HTTP server libraries at the bottom of "
"the page</td>\n"
"</tr>\n"

"<tr>\n"
"<td><a href='http://webcprecompiler.com'>WebC</a></td>\n"
"<td>This is another project for making web pages in C.  It uses php like "
"escape tags to let you write C code and HTML in the same source.  It "
"uses "PRODUCTNAME" as an example web server.</td>\n"
"</tr>\n"

"<tr>\n"
"<td><a href='http://makemymakefile.com'>Make My Makefile</a></td>\n"
"<td>A web site for generate a makefile for you.  You answer a few \n"
"questions hit the generate button and a good functional makefile.  \n"
"You then can just add new files directly to the makefile without needing \n"
"regenerate it.</td>\n"
"</tr>\n"

"</table>\n"
"";

void File_Links(struct WebServer *Web)
{
    WS_WriteChunk(Web,m_LinksHTML,sizeof(m_LinksHTML)-1);
}
