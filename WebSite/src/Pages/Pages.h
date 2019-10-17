/*******************************************************************************
 * FILENAME: Pages.h
 * 
 * PROJECT:
 *    Bitty HTTP
 *
 * FILE DESCRIPTION:
 *    This file has a list of all the pages function prototypes in it.
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
#ifndef __PAGES_H_
#define __PAGES_H_

/***  HEADER FILES TO INCLUDE          ***/
#include "Base/WebServer.h"

/***  DEFINES                          ***/

/***  MACROS                           ***/

/***  TYPE DEFINITIONS                 ***/
typedef enum
{
    /* Order must match 'g_PageInfo' */
    e_Page_Root,
    e_Page_About,
    e_Page_Download,
    e_Page_ReleaseNotes,
    e_Page_License,
    e_Page_FAQ,
    e_Page_Development,
    e_Page_AutoDocs,
    e_Page_TheBasics,
    e_Page_HelloWorld,
    e_Page_CSS,
    e_Page_Graphics,
    e_Page_DynamicContent,
    e_Page_GETVars,
    e_Page_POSTVars,
    e_Page_CookiesVars,
    e_Page_Headers,
    e_Page_URLEncode,
    e_Page_Waiting,
    e_Page_Error404,
    e_Page_Links,
    e_Page_Contact,
    e_PageMAX
} e_PageType;

/***  CLASS DEFINITIONS                ***/

/***  GLOBAL VARIABLE DEFINITIONS      ***/

/***  EXTERNAL FUNCTION PROTOTYPES     ***/
void File_Root(struct WebServer *Web);
void File_About(struct WebServer *Web);
void File_Download(struct WebServer *Web);
void File_License(struct WebServer *Web);
void File_FAQ(struct WebServer *Web);
void File_Links(struct WebServer *Web);
void File_Development(struct WebServer *Web);
void File_AutoDocs(struct WebServer *Web);
void File_Description(struct WebServer *Web);
void File_Examples(struct WebServer *Web);
void File_Doc_TheBasics(struct WebServer *Web);
void File_Doc_HelloWorld(struct WebServer *Web);
void File_Doc_CSS(struct WebServer *Web);
void File_Doc_Graphics(struct WebServer *Web);
void File_Doc_DynamicContent(struct WebServer *Web);
void File_Doc_GETVars(struct WebServer *Web);
void File_Doc_POSTVars(struct WebServer *Web);
void File_Doc_CookiesVars(struct WebServer *Web);
void File_Doc_HeadersVars(struct WebServer *Web);
void File_Doc_URLEncodingVars(struct WebServer *Web);
void File_Doc_Waiting(struct WebServer *Web);
void File_Doc_Error404(struct WebServer *Web);
void File_ReleaseNotes(struct WebServer *Web);
void File_Contact(struct WebServer *Web);
void File_StatInfo(struct WebServer *Web);

#endif
