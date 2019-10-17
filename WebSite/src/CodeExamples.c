/*******************************************************************************
 * FILENAME: CodeExamples.c
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
 *    Paul Hutchinson (07 Sep 2019)
 *
 ******************************************************************************/

/*** HEADER FILES TO INCLUDE  ***/
#include "CodeExamples.h"
#include <string.h>

/*** DEFINES                  ***/

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/

/*** FUNCTION PROTOTYPES      ***/

/*** VARIABLE DEFINITIONS     ***/
const char *m_HelloWorld[]=
{
    "main.c",
    "Options.h",
    "SocketsCon.c",
    "SocketsCon.h",
    "WebServer.c",
    "WebServer.h",
    "Examples/HelloWorld/FileServer.c",
};

const char *m_CSS[]=
{
    "main.c",
    "Options.h",
    "SocketsCon.c",
    "SocketsCon.h",
    "WebServer.c",
    "WebServer.h",
    "Examples/CSS/FileServer.c",
};

const char *m_Graphics[]=
{
    "main.c",
    "Options.h",
    "SocketsCon.c",
    "SocketsCon.h",
    "WebServer.c",
    "WebServer.h",
    "Examples/Graphics/FileServer.c",
};

const char *m_DynamicContent[]=
{
    "main.c",
    "Options.h",
    "SocketsCon.c",
    "SocketsCon.h",
    "WebServer.c",
    "WebServer.h",
    "Examples/ChunkedOutput/FileServer.c",
};

const char *m_GETVars[]=
{
    "main.c",
    "Options.h",
    "SocketsCon.c",
    "SocketsCon.h",
    "WebServer.c",
    "WebServer.h",
    "Examples/GETVars/FileServer.c",
};

const char *m_POSTVars[]=
{
    "main.c",
    "Options.h",
    "SocketsCon.c",
    "SocketsCon.h",
    "WebServer.c",
    "WebServer.h",
    "Examples/POSTVars/FileServer.c",
};

const char *m_Cookies[]=
{
    "main.c",
    "Options.h",
    "SocketsCon.c",
    "SocketsCon.h",
    "WebServer.c",
    "WebServer.h",
    "Examples/Cookies/FileServer.c",
};

const char *m_ManualHeaders[]=
{
    "main.c",
    "Options.h",
    "SocketsCon.c",
    "SocketsCon.h",
    "WebServer.c",
    "WebServer.h",
    "Examples/Headers/FileServer.c",
};
const char *m_URLEncoding[]=
{
    "main.c",
    "Options.h",
    "SocketsCon.c",
    "SocketsCon.h",
    "WebServer.c",
    "WebServer.h",
    "Examples/URLEncodingDecoding/FileServer.c",
};
const char *m_Waiting[]=
{
    "Examples/Waiting/main.c",
    "Options.h",
    "SocketsCon.c",
    "SocketsCon.h",
    "WebServer.c",
    "WebServer.h",
    "Examples/Waiting/FileServer.c",
};
const char *m_404ErrorPage[]=
{
    "main.c",
    "Options.h",
    "SocketsCon.c",
    "SocketsCon.h",
    "WebServer.c",
    "WebServer.h",
    "Examples/404Errors/FileServer.c",
};

struct ExampleCode g_Examples[e_ExampleCodeMAX]=
{
    {
        "Hello World",
        m_HelloWorld,
        sizeof(m_HelloWorld)/sizeof(const char *)
    },
    {
        "CSS",
        m_CSS,
        sizeof(m_CSS)/sizeof(const char *)
    },
    {
        "Graphics",
        m_Graphics,
        sizeof(m_Graphics)/sizeof(const char *)
    },
    {
        "Dynamic Content",
        m_DynamicContent,
        sizeof(m_DynamicContent)/sizeof(const char *)
    },
    {
        "GET Vars",
        m_GETVars,
        sizeof(m_GETVars)/sizeof(const char *)
    },
    {
        "POST Vars",
        m_POSTVars,
        sizeof(m_POSTVars)/sizeof(const char *)
    },
    {
        "Cookies",
        m_Cookies,
        sizeof(m_Cookies)/sizeof(const char *)
    },
    {
        "Manual Headers",
        m_ManualHeaders,
        sizeof(m_ManualHeaders)/sizeof(const char *)
    },
    {
        "URL Encoding/Decoding",
        m_URLEncoding,
        sizeof(m_URLEncoding)/sizeof(const char *)
    },
    {
        "Waiting on a socket",
        m_Waiting,
        sizeof(m_Waiting)/sizeof(const char *)
    },
    {
        "404 Error Page",
        m_404ErrorPage,
        sizeof(m_404ErrorPage)/sizeof(const char *)
    },
};

int g_ExamplesCount=sizeof(g_Examples)/sizeof(struct ExampleCode);

/*******************************************************************************
 * NAME:
 *    OutputListOfExampleFiles
 *
 * SYNOPSIS:
 *    void OutputListOfExampleFiles(struct WebServer *Web,e_ExampleCodeType e);
 *
 * PARAMETERS:
 *    Web [I] -- The web server to output this list on
 *    e [I] -- The example to output.
 *
 * FUNCTION:
 *    This function outputs all the files in an example.  It will output the
 *    files as a <ul>.
 *
 * RETURNS:
 *    NONE
 *
 * SEE ALSO:
 *    
 ******************************************************************************/
void OutputListOfExampleFiles(struct WebServer *Web,e_ExampleCodeType e)
{
    int f;
    const char *Str;

    WS_WriteChunk(Web,"<ul>\n",5);
    for(f=0;f<g_Examples[e].FileCount;f++)
    {
        WS_WriteChunk(Web,"<li>\n<a href='/source/",22);
        Str=g_Examples[e].Files[f];
        WS_WriteChunk(Web,Str,strlen(Str));
        WS_WriteChunk(Web,"'>",2);
        /* Only the filename part */
        Str+=strlen(Str);
        while(Str>g_Examples[e].Files[f] && *Str!='/')
            Str--;
        if(*Str=='/')
            Str++;
        WS_WriteChunk(Web,Str,strlen(Str));
        WS_WriteChunk(Web,"</a></li>\n",10);
    }
    WS_WriteChunk(Web,"</ul>\n",6);
}
