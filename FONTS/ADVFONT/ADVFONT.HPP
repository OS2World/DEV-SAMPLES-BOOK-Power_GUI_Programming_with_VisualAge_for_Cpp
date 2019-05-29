//************************************************************
// Fonts - Using Advanced Font Functions
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <idrawcv.hpp>

class FontDrawingArea : public IDrawingCanvas
{
public:
  FontDrawingArea  ( unsigned long windowId,
                     IWindow* parent,
                     IWindow* owner,
                     const IRectangle& initial = IRectangle() );
virtual
 ~FontDrawingArea ( );

private:
  FontDrawingArea ( const FontDrawingArea& fda );
FontDrawingArea
 &operator=       ( const FontDrawingArea& fda );
};

