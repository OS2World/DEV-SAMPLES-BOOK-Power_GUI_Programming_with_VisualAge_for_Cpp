#ifndef _THREAD_
#define _THREAD_
/***************************************************************
* FILE NAME: thread.hpp                                        *
*                                                              *
* DESCRIPTION:                                                 *
*   This file contains the declaration(s) of the class(es):    *
*     Thread - Container object representing a "visual" thread *
*                                                              *
* COPYRIGHT:                                                   *
*   Licensed Materials - Property of Solution Frameworks       *
*   Copyright (C) 1996, Solution Frameworks                    *
*   All Rights Reserved                                        *
***************************************************************/
#ifndef _ICNROBJ_
  #include <icnrobj.hpp>
#endif

class IContainerColumn;
class IMenuEvent;
class ICommandEvent;
class ThreadData;

/*-------------------------- Thread ----------------------------
| Objects of this class are used to visually represent threads |
| within a container control.                                  |
|                                                              |
| The constructor requires the container control that that     |
| new object is to be inserted into.  The second argument      |
| indictes whether the thread is to represent the (already     |
| started) primary thread.                                     |
|                                                              |
| Use these function to utilize Thread objects with your       |               
| container control(s):                                        |               
|   addColumnsTo  - Adds appropriate container columns to      |
|                   given container.                           |                    
|   makePopUpMenu - Creates appropriate Thread pop-up menu.    |
|   handleCommand - Applies command to a Thread.               |               
--------------------------------------------------------------*/
class Thread : public IContainerObject {
public:
  Thread ( IContainerControl &cnr, Boolean primary = false );

  ~Thread ( );

static void
  addColumnsTo ( IContainerControl &cnr );

Boolean
  makePopUpMenu ( IMenuEvent    &event ),
  handleCommand ( ICommandEvent &cmd );

private: 
Boolean
  performAction ( );
void
  timerTick ( ),
  refreshInfo ( );
static void
  run ( void *arg );

IString
  threadId,
  status,
  priorityClass,
  priorityLevel;

ThreadData
 *data;

static IContainerColumn
  iconColumn,
  nameColumn,
  threadIdColumn,
  statusColumn,
  priorityClassColumn,
  priorityLevelColumn;
}; // class Thread

#endif // _CNRTHRD_
