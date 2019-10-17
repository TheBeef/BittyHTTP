/*******************************************************************************
 * FILENAME: StatInfo.c
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
 * CREATED BY:
 *    Paul Hutchinson (30 Sep 2019)
 *
 ******************************************************************************/

/*** HEADER FILES TO INCLUDE  ***/
#include "Pages/Pages.h"
#include "Common/Headers.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <limits.h>

/*** DEFINES                  ***/

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/

/*** FUNCTION PROTOTYPES      ***/

/*** VARIABLE DEFINITIONS     ***/
static void StatInfo_PrintIt(struct WebServer *Web,const char *fmt,...);

void File_StatInfo(struct WebServer *Web)
{
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        StatInfo_PrintIt(Web,"Current working dir: %s<br/>", cwd);
    }
    else
    {
        StatInfo_PrintIt(Web,"getcwd() error<br/>");
    }
}

static void StatInfo_PrintIt(struct WebServer *Web,const char *fmt,...)
{
    char buff[1000];
    va_list args;

    va_start (args, fmt);
    vsnprintf (buff,sizeof(buff),fmt,args);
    va_end (args);

    WS_WriteChunk(Web,buff,strlen(buff));
}
