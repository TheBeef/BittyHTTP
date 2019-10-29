/*******************************************************************************
 * FILENAME: Contact.c
 *
 * PROJECT:
 *    Bitty HTTP
 *
 * FILE DESCRIPTION:
 *    
 *
 * CREATED BY:
 *    Paul Hutchinson (11 Sep 2019)
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
const char m_ContactHTML[]=
"<h1><span>1</span>Contact</h1>\n"
"You can contact me by email at <a href='mailto:paul@bittyhttp.com'>paul@bittyhttp.com</a><br/>"
"You can also access the project page on GitHub at <a href='https://github.com/TheBeef/BittyHTTP'>https://github.com/TheBeef/BittyHTTP</a><br/>";

void File_Contact(struct WebServer *Web)
{
    WS_WriteChunk(Web,m_ContactHTML,sizeof(m_ContactHTML)-1);
}
