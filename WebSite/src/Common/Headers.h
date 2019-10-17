/*******************************************************************************
 * FILENAME: Headers.h
 * 
 * PROJECT:
 *    Bitty HTTP
 *
 * FILE DESCRIPTION:
 *    .h file
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
 *******************************************************************************/
#ifndef __HEADERS_H_
#define __HEADERS_H_

/***  HEADER FILES TO INCLUDE          ***/
#include "Base/WebServer.h"
#include "Pages/Pages.h"

/***  DEFINES                          ***/
#define PRODUCTNAME                     "Bitty HTTP"

/***  MACROS                           ***/

/***  TYPE DEFINITIONS                 ***/

/***  CLASS DEFINITIONS                ***/

/***  GLOBAL VARIABLE DEFINITIONS      ***/

/***  EXTERNAL FUNCTION PROTOTYPES     ***/
void Start_WebPage(struct WebServer *Web,const char *PageTitle,e_PageType ActivePage);
void End_WebPage(struct WebServer *Web);
void Start_Head(struct WebServer *Web,const char *PageTitle);
void End_Head(struct WebServer *Web);
void Start_Body(struct WebServer *Web,e_PageType ActivePage);
void End_Body(struct WebServer *Web);

#endif
