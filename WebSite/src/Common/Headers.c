/*******************************************************************************
 * FILENAME: Headers.c
 *
 * PROJECT:
 *    Bitty HTTP
 *
 * FILE DESCRIPTION:
 *    This file has common header for the web site.
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
#include "Base/WebServer.h"
#include "Base/FileServer.h"
#include "Common/Headers.h"
#include <string.h>
#include <stdio.h>

/*** DEFINES                  ***/

/*** MACROS                   ***/

/*** TYPE DEFINITIONS         ***/
struct MainMenuEntry
{
    const char *Text;
    const char *Link;
    e_PageType PageID;
};

/*** FUNCTION PROTOTYPES      ***/
static void Output_Crumb(struct WebServer *Web,e_PageType PageID,bool First);

/*** VARIABLE DEFINITIONS     ***/
struct MainMenuEntry m_MainMenu[]=
{
    {"Home","/",e_Page_Root},
    {"About","/About.html",e_Page_About},
    {"Download","/Download.html",e_Page_Download},
    {"License","/License.html",e_Page_License},
    {"FAQ","/FAQ.html",e_Page_FAQ},
    {"Development","/Development.html",e_Page_Development},
    {"Links","/Links.html",e_Page_Links},
    {"Contact","/Contact.html",e_Page_Contact},
};

const char m_PageEnd[]=
"<!-- Matomo -->\n"
"<script type=\"text/javascript\">\n"
"  var _paq = window._paq || [];\n"
"  /* tracker methods like \"setCustomDimension\" should be called before \"trackPageView\" */\n"
"  _paq.push(['trackPageView']);\n"
"  _paq.push(['enableLinkTracking']);\n"
"  (function() {\n"
"    var u=\"//matomo.bittyhttp.com/\";\n"
"    _paq.push(['setTrackerUrl', u+'matomo.php']);\n"
"    _paq.push(['setSiteId', '1']);\n"
"    var d=document, g=d.createElement('script'), s=d.getElementsByTagName('script')[0];\n"
"    g.type='text/javascript'; g.async=true; g.defer=true; g.src=u+'matomo.js'; s.parentNode.insertBefore(g,s);\n"
"  })();\n"
"</script>\n"
"<!-- End Matomo Code -->\n"
"</head>\n";

void Start_Head(struct WebServer *Web,const char *PageTitle)
{
    const char *Start=
    "<!doctype html>\n"
    "<html lang='en'>\n"
    "<head>\n"
    "  <meta charset='utf-8'>\n"
    "  <link rel='stylesheet' href='/CommonCSS.css'>\n"
    "  <link href='https://fonts.googleapis.com/css?family=Varela+Round' rel='stylesheet'>\n"
    "  <title>";
    const char *End=
        "</title>\n";

    WS_Header(Web,"Content-Type: text/html; charset=utf-8");

    WS_WriteChunk(Web,Start,strlen(Start));
    WS_WriteChunk(Web,PRODUCTNAME,strlen(PRODUCTNAME));
    WS_WriteChunk(Web," - ",3);
    WS_WriteChunk(Web,PageTitle,strlen(PageTitle));
    WS_WriteChunk(Web,End,strlen(End));
}

void End_Head(struct WebServer *Web)
{
    WS_WriteChunk(Web,m_PageEnd,sizeof(m_PageEnd)-1);
}

void Start_Body(struct WebServer *Web,e_PageType ActivePage)
{
    int entry;
    char buff[100];
    e_PageType RootPageID;
    const char *ActiveLinkTxt;
    const char *Start=
        "<body>\n"
        "\n"
        "<header class='MainHeader'>\n"
        "    <h1>"PRODUCTNAME"</h1>\n"
        "    <nav class='MainMenu' role='navigation'>\n"
        "        <ul>\n";
    const char *End=
        "        </ul>\n"
        "    </nav>\n"
        "</header>\n";
    const char *BodyStart=
        "<article class='MainContent'>\n";

    WS_WriteChunk(Web,Start,strlen(Start));

    /* Find the root parent of the current page */
    RootPageID=ActivePage;
    while(g_PageInfo[RootPageID].ParentID!=e_PageMAX)
        RootPageID=g_PageInfo[RootPageID].ParentID;

    /* Output main menu (only root items) */
    for(entry=0;entry<sizeof(m_MainMenu)/sizeof(struct MainMenuEntry);entry++)
    {
        ActiveLinkTxt="";
        if(m_MainMenu[entry].PageID==RootPageID)
            ActiveLinkTxt="class='active'";

        if(g_PageInfo[m_MainMenu[entry].PageID].ParentID==e_PageMAX)
        {
            sprintf(buff,"<li %s><a href='%s'>%s</a></li>\n",ActiveLinkTxt,
                    m_MainMenu[entry].Link,
                    m_MainMenu[entry].Text);

            WS_WriteChunk(Web,buff,strlen(buff));
        }
    }

    WS_WriteChunk(Web,End,strlen(End));

    /* Bread crumbs */
    WS_WriteChunk(Web,"<div class='Bread'>",19);
    Output_Crumb(Web,ActivePage,true);
    WS_WriteChunk(Web,"</div>",6);

    WS_WriteChunk(Web,BodyStart,strlen(BodyStart));
}

static void Output_Crumb(struct WebServer *Web,e_PageType PageID,bool First)
{
    const char *PagePath;

    if(PageID!=e_PageMAX)
    {
        Output_Crumb(Web,g_PageInfo[PageID].ParentID,false);

        PagePath=FS_FindPagePath(PageID);

        if(!First && PagePath!=NULL)
        {
            WS_WriteChunk(Web,"<a href='",9);
            WS_WriteChunk(Web,PagePath,strlen(PagePath));
            WS_WriteChunk(Web,"'>",2);
        }

        WS_WriteChunk(Web,g_PageInfo[PageID].PageTitle,
                strlen(g_PageInfo[PageID].PageTitle));

        if(!First && PagePath!=NULL)
            WS_WriteChunk(Web,"</a>",4);

        if(!First)
            WS_WriteChunk(Web," &#187; ",8);
    }
}



const char m_BodyEnd[]=
"</article>\n"
"</body>\n"
"</html>\n";
void End_Body(struct WebServer *Web)
{
    WS_WriteChunk(Web,m_BodyEnd,sizeof(m_BodyEnd)-1);
}

void Start_WebPage(struct WebServer *Web,const char *PageTitle,e_PageType ActivePage)
{
    Start_Head(Web,PageTitle);
    End_Head(Web);
    Start_Body(Web,ActivePage);
}

void End_WebPage(struct WebServer *Web)
{
    End_Body(Web);
}

