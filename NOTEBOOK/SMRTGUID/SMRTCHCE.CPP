//************************************************************
// Notebook Control - Smart Guide Notebook
//
// Classes:  SingleChoiceSmartPage
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc.
// All Rights Reserved.
//************************************************************
#include <irect.hpp>
#include <isplitcv.hpp>
#include <isetcv.hpp>
#include <istring.hpp>
#include <ilistbox.hpp>
#include <iradiobt.hpp>
#include <iselhdr.hpp>
#include <ievtdata.hpp>
#include <iseq.h>
#include "smrtguid.hpp"

///
///  Define the data stored with each Choice in
///  our SingleChoiceSmartPage
class SmartChoice
{
public:
   SmartChoice ( const IString& choiceName,
                 unsigned long  helpId)
      : fChoiceName (choiceName),
        fHelpId (helpId)
    {}
IString
  choiceName    ( ) const
  { return fChoiceName; }

unsigned long
  helpId        ( ) const
  { return fHelpId;  }

private:
IString
  fChoiceName;
unsigned long
  fHelpId;
};


class SmartChoiceList : public ISequence<SmartChoice>
{
public:
  SmartChoiceList () : ISequence<SmartChoice>(10) {}

};

class SmartChoiceSelectHandler : public ISelectHandler
{
public:
  SmartChoiceSelectHandler ( IWindow* commandEventReceiver)
    : fCommandEventReceiver( *commandEventReceiver) {}

protected:
virtual Boolean
  selected ( IControlEvent& event )
  {
     fCommandEventReceiver.sendEvent(IWindow::command,
                        IEventParameter1(CID_REFRESH) );
     return true;
  }
private:

IWindow
 &fCommandEventReceiver;
SmartChoiceSelectHandler ( const SmartChoiceSelectHandler&);
SmartChoiceSelectHandler& operator = ( const SmartChoiceSelectHandler&);
};



static const unsigned long kNotSelected = (unsigned long)-1;



IWindow* SingleChoiceSmartPage::createAndOrphanPage (
                                IWindow*          parent,
                                IWindow*          owner,
                                const IRectangle& initialRect)
{
  // Create a split canvas to house the multicell of our parent on
  // top and our own multicell on the bottom.
  // Note: Create the split canvas invisible to minimize layout.
  ISplitCanvas* client = new ISplitCanvas(WID_CLIENTCANVAS, parent, owner, initialRect,
                            ISplitCanvas::horizontal | ISplitCanvas::noSplitBars  );

  // Create a select handler
  fSelectHandler = new SmartChoiceSelectHandler(client);

  // Ask our parent to create its window in the set canvas.
  Inherited::createAndOrphanPage( client,
                                  client,
                                  initialRect);

  // Create our own set canvas for our choices.
  ISetCanvas* setCanvas = new ISetCanvas (WID_SELECTCANVAS, client, client);

  unsigned long selectedChoice = currentChoice();

  // If greater than 4 choices, create listbox, else create radio buttons
  if (fNumberOfChoices > 4)
  {
     IListBox* listBox = new IListBox( WID_SELECTLISTBOX,
                                       setCanvas,
                                       setCanvas);
     fSelectHandler->handleEventsFor(listBox);
     for(unsigned long choices=0; choices<fNumberOfChoices; choices++)
     {
       listBox->addAsLast(choiceTextAtIndex(choices));
     }
     (*listBox)
       .select(selectedChoice)
       .setAutoDeleteObject( );
     fSelectionWindow = listBox;
  }
  else {
     setCanvas->setDeckOrientation(ISetCanvas::vertical);
     fSelectHandler->handleEventsFor(setCanvas);
     for(unsigned long choices=0; choices<fNumberOfChoices; choices++)
     {
       IRadioButton* button = new IRadioButton( WID_SELECTRADIO+choices,
                                                setCanvas,
                                                setCanvas);
       if (choices==0)
          button->enableGroup();

       (*button)
         .setText(choiceTextAtIndex(choices))
         .setAutoDeleteObject( );

       if(choices == selectedChoice)
       {
         button->select();
         // Save this as the button to query selection later.
         fSelectionWindow = button;
       }
     }
  }
  client->show();
  return client;
}

SingleChoiceSmartPage& SingleChoiceSmartPage::addChoice(
                        const IString& choiceText,
                        unsigned long  helpId)
{
  // Allocate the Smart Choice list if necessary.
  if (fSmartChoiceList == 0)
     fSmartChoiceList = new SmartChoiceList;

  fSmartChoiceList->addAsLast(SmartChoice(choiceText, helpId));
  fNumberOfChoices++;
  return *this;
}

IString SingleChoiceSmartPage::choiceTextAtIndex ( unsigned long index )
{
   // Collections are one based.
   unsigned long sequenceIndex = index+1;
   const SmartChoice& smartChoice =
                 fSmartChoiceList->elementAtPosition(sequenceIndex);
   return smartChoice.choiceName();
}


unsigned long SingleChoiceSmartPage::currentChoice ( ) const
{
  unsigned long selectedIndex = fSelectedChoice;
  if(fSelectionWindow!=0)
  {
    if (fNumberOfChoices > 4)
      selectedIndex = ((IListBox*)fSelectionWindow)->selection();
    else
      selectedIndex = ((IRadioButton*)fSelectionWindow)->selectedIndex();
  }

  return selectedIndex;
}

Boolean SingleChoiceSmartPage::isOKToClose ( IString&  ) const
{
  if (fSelectedChoice != kNotSelected)
     return true;
  else
     return false;
}

unsigned long SingleChoiceSmartPage::numberOfChoices ( ) const
{
   if (fSmartChoiceList != 0)
      return fSmartChoiceList->numberOfElements();
   else
      return 0;
}

unsigned long SingleChoiceSmartPage::helpId ( ) const
{
  if (fSelectedChoice != kNotSelected)
     return Inherited::helpId();
  else
  {
     const SmartChoice& smartChoice = fSmartChoiceList->elementAtPosition(fSelectedChoice+1);
     return smartChoice.helpId();
  }
}

SingleChoiceSmartPage& SingleChoiceSmartPage::setSelectedChoice ( unsigned long selectedChoice )
{
  fSelectedChoice = selectedChoice;
  return *this;
}
ISize SingleChoiceSmartPage::minimumSize ( ) const
{
  // Need to implement
  return ISize(100,100);
}

