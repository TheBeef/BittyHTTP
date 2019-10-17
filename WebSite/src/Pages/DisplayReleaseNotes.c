/*******************************************************************************
 * FILENAME: DisplayReleaseNotes.c
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
 * CREATED BY:
 *    Paul Hutchinson (08 Sep 2019)
 *
 ******************************************************************************/

/*** HEADER FILES TO INCLUDE  ***/
#include "../../ReleaseNotes.h"
#include "Pages/Pages.h"
#include "Common/Headers.h"
#include <string.h>
#include <stdlib.h>

/*** DEFINES                  ***/

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/

/*** FUNCTION PROTOTYPES      ***/

/*** VARIABLE DEFINITIONS     ***/

void File_ReleaseNotes(struct WebServer *Web)
{
    int r;
    int n;
    const char *Str;
//    char buff[100];
    char buff[10];
    char *d;

    WS_WriteChunk(Web,"<h1><span>1</span>Release Notes</h1>",36);

    for(r=0;r<m_ReleaseNoteCount;r++)
    {
        Str=m_ReleaseNotes[r].Version;
        WS_WriteChunk(Web,"<a class='anchor' id='",22);
        WS_WriteChunk(Web,Str,strlen(Str));
        WS_WriteChunk(Web,"'></a>",6);
        WS_WriteChunk(Web,"<h2>",4);
        WS_WriteChunk(Web,Str,strlen(Str));
        WS_WriteChunk(Web,"</h2>",5);

        for(n=0;n<m_ReleaseNotes[r].NotesCount;n++)
        {
            Str=m_ReleaseNotes[r].Notes[n].Summary;
            WS_WriteChunk(Web,"<h3 class='ReleaseNotes'>",25);
            WS_WriteChunk(Web,Str,strlen(Str));
            WS_WriteChunk(Web,"</h3>",5);

            /* Output the details doing the wiki markup (minimal) */
            WS_WriteChunk(Web,"<p class='ReleaseNotes'>",24);

            Str=m_ReleaseNotes[r].Notes[n].Details;
            d=buff;
            while(*Str!=0)
            {
                if(*Str=='\n')
                {
                    *d=0;
                    WS_WriteChunk(Web,buff,d-buff);
                    WS_WriteChunk(Web,"</p><p class='ReleaseNotes'>",28);
                    d=buff;
                }
                else
                {
                    if(d-buff>=sizeof(buff)-1)
                    {
                        *d=0;
                        WS_WriteChunk(Web,buff,d-buff);
                        d=buff;
                    }
                    *d++=*Str;
                }
                Str++;
            }
            if(d!=buff)
            {
                *d=0;
                WS_WriteChunk(Web,buff,d-buff);
            }
            WS_WriteChunk(Web,"</p>",4);
        }
    }
}
