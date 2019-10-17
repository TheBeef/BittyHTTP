/*******************************************************************************
 * FILENAME: CodeExamples.h
 * 
 * PROJECT:
 *    Bitty HTTP
 *
 * FILE DESCRIPTION:
 *    
 *
 * COPYRIGHT:
 *    Copyright 2019 Paul Hutchinson.
 *
 *    This software is the property of Paul Hutchinson and may not be
 *    reused in any manner except under express written permission of
 *    Paul Hutchinson.
 *
 * HISTORY:
 *    Paul Hutchinson (07 Sep 2019)
 *       Created
 *
 *******************************************************************************/
#ifndef __CODEEXAMPLES_H_
#define __CODEEXAMPLES_H_

/***  HEADER FILES TO INCLUDE          ***/
#include "Base/WebServer.h"

/***  DEFINES                          ***/

/***  MACROS                           ***/

/***  TYPE DEFINITIONS                 ***/
struct ExampleCode
{
    const char *Name;
    const char **Files;
    int FileCount;
};

typedef enum
{
    e_ExampleCode_HelloWorld,
    e_ExampleCode_CSS,
    e_ExampleCode_Graphics,
    e_ExampleCode_DynamicContent,
    e_ExampleCode_GETVars,
    e_ExampleCode_POSTVars,
    e_ExampleCode_Cookies,
    e_ExampleCode_ManualHeaders,
    e_ExampleCode_URLEncode,
    e_ExampleCode_Waiting,
    e_ExampleCode_404Error,
    e_ExampleCodeMAX
}e_ExampleCodeType;

/***  CLASS DEFINITIONS                ***/

/***  GLOBAL VARIABLE DEFINITIONS      ***/
extern struct ExampleCode g_Examples[e_ExampleCodeMAX];
extern int g_ExamplesCount;

/***  EXTERNAL FUNCTION PROTOTYPES     ***/
void OutputListOfExampleFiles(struct WebServer *Web,e_ExampleCodeType e);

#endif
