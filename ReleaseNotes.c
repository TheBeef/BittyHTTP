/*******************************************************************************
 * FILENAME: ReleaseNotes.c
 *
 * PROJECT:
 *    Bitty HTTP
 *
 * FILE DESCRIPTION:
 *    This file has the release notes in it.  This is also a change log.
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
 * CREATED BY:
 *    Paul Hutchinson (08 Sep 2019)
 *
 ******************************************************************************/

/*** HEADER FILES TO INCLUDE  ***/
#include "ReleaseNotes.h"

/*** DEFINES                  ***/

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/

/*** FUNCTION PROTOTYPES      ***/

/*** VARIABLE DEFINITIONS     ***/

//static struct ReleaseNote m_Notes_Next[]=
//{
//    {
//         "Title",
//         "Description"
//    },
//};

static struct ReleaseNote m_Notes_Next[]=
{
    {
         "Fixed warning in WebServer.c",
         "There was a warning about %ld not matching strlen() return value."
         " Changed to %zd for the correct printf() type"
    },
    {
         "Added support for building for Windows",
         "A build.bat file has been added to build the hello world example"
         " under Windows.  Another set of files (SocketsConWin.c and .h) have"
         " been added to connect to WinSock.\n"
         "Work still needs to be done to update all the examples to have a"
         " build.bat file."
    },
};

static struct ReleaseNote m_Notes_1_4[]=
{
    {
        "Fixed WS_Shutdown() function",
         "The shutdown function didn't do anything.  This wasn't a problem as"
         " long as you quit your program after, but if you shutdown and then"
         " wanted to restart it had a problem.  The old sockets where still"
         " open and binded.\n"
         "Added code to close all the sockets."
    },
};

static struct ReleaseNote m_Notes_1_3[]=
{
    {
        "Fixed similar POST vars not processing",
         "When 2 (or more) POST vars starts with the same chars"
         " (Ie \"Login\" and \"LoginPassword\") the parser was not picking up"
         " the second one and messes up other POST vars that follow it.  This"
         " has been fixed"
    },
};

static struct ReleaseNote m_Notes_1_2[]=
{
    {
        "Updated example BSD sockets to ignore SIGPIPE",
         "The example BSD sockets connector was updated to ignore the"
         " SIGPIPE and return an error instead.  This is needed because"
         " if you do not ignore the signal and the web browser closes the"
         " socket the program just exits (the default SIGPIPE handler)."
    },
};

static struct ReleaseNote m_Notes_1_1[]=
{
    {
        "Added WS_WriteWholeStr() function",
         "A new version of WS_WriteWhole() has been added that works with"
         " C strings instead of known buffer sizes"
    },
    {
        "Added WS_WriteChunkStr() function",
         "A new version of WS_WriteChunk() has been added that works with"
         " C strings instead of known buffer sizes"
    },
};

static struct ReleaseNote m_Notes_1_0[]=
{
    {
        "First Version",
         "This is the first version."
    },
};

const struct ReleaseInfo m_ReleaseNotes[]=
{
    {"1.0","08 Sep 2019","First Release",m_Notes_1_0,sizeof(m_Notes_1_0)/sizeof(struct ReleaseNote)},
    {"1.1","29 Oct 2019","New C String Functions",m_Notes_1_1,sizeof(m_Notes_1_1)/sizeof(struct ReleaseNote)},
    {"1.2","19 Aug 2020","Ignored SIGPIPE",m_Notes_1_2,sizeof(m_Notes_1_2)/sizeof(struct ReleaseNote)},
    {"1.3","31 May 2021","Fixed POST bug",m_Notes_1_3,sizeof(m_Notes_1_3)/sizeof(struct ReleaseNote)},
    {"1.4","02 Jan 2022","Fixed WS_Shutdown()",m_Notes_1_4,sizeof(m_Notes_1_4)/sizeof(struct ReleaseNote)},
};

const unsigned long m_ReleaseNoteCount=sizeof(m_ReleaseNotes)/sizeof(struct ReleaseInfo);
