#include "hlppanel.h"   // For preprocessor substitutions.
:userdoc.
.*
:h1 res=PANEL_PRIMARY.Help for the Primary Window
:i1 id=primary.Help for the Primary Window
:p.This is the help for the example program&apos.s primary window.
.*
:i2 refid=secondaryPB.Help for the Show Secondary Window push button
:h2 res=PANEL_SECONDARY_BUTTON.Show Secondary Window Button Help
:p.This is contextual help for the :hp2.Show Secondary Window:ehp2.
push button.
:p.Select this push button to display a secondary window.
.*
:i2 refid=exitPBprimary.Help for the Exit push button
:h2 res=PANEL_EXIT_BUTTON_PRIMARY.Exit Button Help
:p.This is contextual help for the :hp2.Exit:ehp2. push button
on the primary window.
:p.Select this push button to end the example application.
.*
:h2 res=PANEL_FILE.File Help
:p.This is contextual help for the :hp2.File:ehp2. menu choice.
:p.Select this choice to display additional menu choices.
.*
:h3 res=PANEL_CLOSE.Close Help
:p.This is contextual help for the :hp2.Close:ehp2. menu choice.
:p.Select this choice to close the window.
.*
:h2 res=PANEL_HELP.Help Help
:p.This is contextual help for the :hp2.Help:ehp2. menu choice.
:p.Select this choice to display additional menu choices.
.*
#ifndef IC_PM
:h3 res=PANEL_HELPCONTENTS.Help Contents
:p.This is contextual help for the :hp2.Contents:ehp2. menu choice.
:p.Select this choice to display a list of all help topics.
.*
#endif
:h3 res=PANEL_HELPINDEX.Help Index
:p.This is contextual help for the :hp2.Help index:ehp2. menu choice.
:p.Select this choice to display an alphabetical list of
help topics.
.*
:h3 res=PANEL_EXTENDEDHELP.General Help
:p.This is contextual help for the :hp2.General help:ehp2.
menu choice.
:p.Select this choice to display general help for this window.
.*
#ifdef IC_PM
:h3 res=PANEL_USINGHELP.Using Help
:p.This is contextual help for the :hp2.Using help:ehp2. menu choice.
:p.Select this choice for information on using the
help facility.
#else
:h3 res=PANEL_USINGHELP.How to Use Help
:p.This is contextual help for the :hp2.How to use help:ehp2. menu choice.
:p.Select this choice for information on using the help facility.
#endif
.*
:h3 res=PANEL_KEYSHELP.Keys Help
:p.This is contextual help for the :hp2.Keys help:ehp2. menu choice.
:p.Select this choice for information on significant keys used
by the application.
.*
#ifdef IC_PM
:h3 res=PANEL_PRODUCT_INFO.Product Information Help
:p.This is contextual help for the
:hp2.Product Information:ehp2. menu choice.
:p.Select this choice to show information about this example program.
#else
:h3 res=PANEL_PRODUCT_INFO.About this Example... Help
:p.This is contextual help for the
:hp2.About this example...:ehp2. menu choice.
:p.Select this choice to show information about this example program.
#endif
.*
:i1 id=modelessSec.Help for Secondary Windows
:h1 res=PANEL_SECONDARY.
Help for Secondary Windows
:p.This is the help for a secondary window.
.*
:i2 refid=exitPBprimary.Help for the Exit push button
:h2 res=PANEL_EXIT_BUTTON_SECONDARY.Exit Button Help
:p.This is contextual help for the :hp2.Exit:ehp2. push button
on a secondary window.
:p.Select this push button to dismiss the secondary window.
.*
:i1 id=keys.Keys Help
:h1 res=PANEL_KEYS_HELP.Keys Help
:p.This is the help for special keys used in this sample.
:p.There are no such keys.
.*
:h1 res=PANEL_PRODUCT_INFO_MSG.
#ifdef IC_PM
Help for the Product Information Window
#else
Help for the About This Example Window
#endif
:p.This is the help for a message box.
:p.The message box substitutes for a more elaborate product
information window.
.*
:euserdoc.
