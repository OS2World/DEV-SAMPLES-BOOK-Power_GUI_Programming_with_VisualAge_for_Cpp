#ifndef _DECKCV_
#define _DECKCV_
//*********************************************************
// Canvas - ISetCanvas Deck Operations
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <icmdhdr.hpp>
#include <isetcv.hpp>
#include <istattxt.hpp>
#include <iseq.h>

class DeckCanvas : public ISetCanvas {
public:
  DeckCanvas     ( unsigned long id,
                   IWindow* parentAndOwner,
                   IWindow* frameOrClient );
virtual
 ~DeckCanvas     ( );
unsigned long
  childCount     ( ) const;
DeckCanvas
 &setChildCount  ( unsigned long count ),
 &setUpChild     ( IStaticText* child ),
 &addAsFirst     ( ),
 &addAsLast      ( ),
 &removeFirst    ( ),
 &removeLast     ( ),
 &makeHorizontal ( ),
 &makeVertical   ( );

private:
  DeckCanvas ( const DeckCanvas& );
DeckCanvas
 &operator=  ( const DeckCanvas& );

class DeckCommandHandler : public ICommandHandler {
  public:
    DeckCommandHandler ( DeckCanvas* canvas );
  protected:
  virtual Boolean
    command            ( ICommandEvent& event );
  private:
  DeckCanvas
   *deckCanvas;
  }; // DeckCanvas::DeckCommandHandler
DeckCommandHandler
  cmdHandler;
class ChildList : public ISequence< IStaticText* > {
  public:
    ChildList ( )
      : ISequence< IStaticText* >( 10 )
    { }
  }; // DeckCanvas::ChildList
ChildList
  children;
unsigned long
  childrenCreated;
friend Boolean
  ChildDeleter ( IStaticText* const& element,
                 void* )
  {
    delete element;
    return true;
  }
}; // DeckCanvas

#endif // _DECKCV_
