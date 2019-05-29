#ifndef _CMDROUTR_
#define _CMDROUTR_
/***************************************************************
* FILE NAME: cmdroutr.hpp                                      *
*                                                              *
* DESCRIPTION:                                                 *
*   This file contains the declaration(s) of the class(es):    *
*     CMdroutr - Template class that generates simple          *
*                ICommandHandler derived classes to route      *
*                command events to object member functions.    *
*                                                              *
* COPYRIGHT:                                                   *
*   Licensed Materials - Property of Solution Frameworks       *
*   Copyright (C) 1996, Solution Frameworks                    *
*   All Rights Reserved                                        *
***************************************************************/
#ifndef _ICMDHDR_
  #include <icmdhdr.hpp>
#endif

/*---------------------- CommandRouter -------------------------
| Objects of classes generated from this template are used     |
| to route command events to arbitrary member functions of     |
| arbitrary objects.  The template argument is the name of     |
| the class whose member function is to be invoked.            |
|                                                              |
| Usage:                                                       |
|   struct MyClass {                                           |
|     Boolean                                                  |
|       function ( ICommandEvent &cmd );                       |
|   };                                                         |
|   ...                                                        |
|   MyClass                                                    |
|     myObject;                                                |
|   ...                                                        |
|   CommandRouter<MyClass>                                     |
|     router( aWindow, myObject, MyClass::function );          |
--------------------------------------------------------------*/
template < class Handler >
class CommandRouter : public ICommandHandler {
public:
  CommandRouter ( IWindow       &window,
                  Handler       &handler,
                  Boolean (Handler::*memberFn)(ICommandEvent&) )
    : ICommandHandler(),
      handler        ( handler ),
      memberFn       ( memberFn ) {
      this->handleEventsFor( &window );
    }
protected:
virtual Boolean
  command ( ICommandEvent &event ) {
    return (handler.*memberFn)( event );
  }
private:
Handler
 &handler;
Boolean (Handler::*memberFn)( ICommandEvent & );
CommandRouter ( const CommandRouter<Handler>& );
operator = ( const CommandRouter<Handler>& );
}; // class CommandRouter

#endif // _CMDROUTR_
