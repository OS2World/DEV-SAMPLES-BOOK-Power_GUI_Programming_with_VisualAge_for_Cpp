//*********************************************************
// Menus - Dynamic Accelerator Keys
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//*********************************************************
#include <iaccelky.hpp>
#include <iacceltb.hpp>
#include <icconst.h>
#include <icmd.hpp>
#include <isetbut.hpp>
#include <istring.hpp>
#include "accelupd.hpp"

IBase::Boolean
  AccelSelectHandler::selected ( IControlEvent& event )
{
  Boolean
    stopProcessingEvent = false;
  ISettingButton
   *accelButton = (ISettingButton*)( event.controlWindow() );

  // Find the accelerator keys associated with the specified
  // window.  Changes to this IAcceleratorTable object can
  // optionally be immediately reflected in the window.
  IAcceleratorTable
    accelTable( &fAccelWindow );

  // Add or remove the indicated accelerator key.
  switch ( event.controlId() )
  {
    case ID_RED:
    {
      // Add or remove accelerator keys for:
      //   Ctrl+r = red
      //   Ctrl+R = red
      IAcceleratorKey
        key1( "r", IKey::ctrl,
              ICommand::applicationCommand, CMD_RED ),
        key2( "R", IKey::ctrl,
              ICommand::applicationCommand, CMD_RED );
      if ( accelButton->isSelected() )
      {
         accelTable
          .addKey( key1, false );
         accelTable
          .addKey( key2, true );
      }
      else
      {
         accelTable
          .removeKeyLike( key1, false );
         accelTable
          .removeKeyLike( key2, true );
      }
      stopProcessingEvent = true;
      break;
    }
    case ID_GREEN:
    {
      // Add or remove accelerator keys for F5 = green.
      IAcceleratorKey
        key( IKey::kF5, IKey::noModifier,
             ICommand::applicationCommand, CMD_GREEN );
      if ( accelButton->isSelected() )
      {
         accelTable
          .addKey( key );
      }
      else
      {
         accelTable
          .removeKeyLike( key );
      }
      stopProcessingEvent = true;
      break;
    }
    case ID_CYAN:
    {
      // Add or remove accelerator keys for Ctrl+\ = cyan.
      IAcceleratorKey
        key( "\\", IKey::ctrl,
             ICommand::applicationCommand, CMD_CYAN );
      if ( accelButton->isSelected() )
      {
         accelTable
          .addKey( key );
      }
      else
      {
         accelTable
          .removeKeyLike( key );
      }
      stopProcessingEvent = true;
      break;
    }
    case ID_PINK:
    {
      // Add or remove accelerator keys for
      // Ctrl+Shift+Alt+Home = cyan.
      IAcceleratorKey
        key( IKey::kHome,
             IKey::ctrl | IKey::shift | IKey::alt,
             ICommand::applicationCommand, CMD_PINK );
      if ( accelButton->isSelected() )
      {
         accelTable
          .addKey( key );
      }
      else
      {
         accelTable
          .removeKeyLike( key );
      }
      stopProcessingEvent = true;
      break;
    }
    default:
      break;
  }
  return stopProcessingEvent;
}
