/*******************************************************************************
 * FILENAME: DownloadInfo.c
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
#include "Common/DownloadInfo.h"
#include <string.h>

/*** DEFINES                  ***/

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/

/*** FUNCTION PROTOTYPES      ***/

/*** VARIABLE DEFINITIONS     ***/

/*******************************************************************************
 * NAME:
 *    BuildReleaseFilename
 *
 * SYNOPSIS:
 *    void BuildReleaseFilename(const char *Version,char *OutBuff);
 *
 * PARAMETERS:
 *    Version [I] -- The version number to use to build the filename.  This
 *                   must be in the format of "x.x.x.x" where 'x' is a number.
 *    OutBuff [O] -- The string to build the filename into.  This should be
 *                   big enough to store the generated filename.
 *
 * FUNCTION:
 *    This function takes a release note version and converts it into the
 *    filename to download that version.
 *
 *    The filename will something in the format of:
 *      "BittyHTTPxxx.tar.gz" where xxx is replaced with the version that
 *      was send in in 'Version'.  Any dots (.) in 'Version' will be converted
 *      to underscores (ie 1.0 becomes 1_0)
 *
 * RETURNS:
 *    NONE
 *
 * LIMITATIONS:
 *    Does not check if 'OutBuff' is big enough, or that there aren't illegal
 *    chars in 'Version'.
 *
 * SEE ALSO:
 *    
 ******************************************************************************/
void BuildReleaseFilename(const char *Version,char *OutBuff)
{
    char *d;
    const char *s;

    strcpy(OutBuff,"BittyHTTP");

    s=Version;
    d=&OutBuff[strlen(OutBuff)];
    while(*s!=0)
    {
        if(*s=='.')
            *d='_';
        else
            *d=*s;
        s++;
        d++;
    }
    *d++=0;

    strcat(OutBuff,".tar.gz");
}
