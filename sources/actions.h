#ifndef _NVMC_ACTTIONS_
#define _NVMC_ACTTIONS_
/****************************************************************************
* NVMC                                                                      *
* EnVy My Car																																*
*                                                                           *
* Fabio Ganovelli                                                           *
*                                                                           *
* All rights reserved.                                                      *
*                                                                           *
* This program is free software; you can redistribute it and/or modify      *   
* it under the terms of the GNU General Public License as published by      *
* the Free Software Foundation; either version 2 of the License, or         *
* (at your option) any later version.                                       *
*                                                                           *
* This program is distributed in the hope that it will be useful,           *
* but WITHOUT ANY WARRANTY; without even the implied warranty of            *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
* GNU General Public License (http://www.gnu.org/licenses/gpl.txt)          *
* for more details.                                                         *
*                                                                           *
****************************************************************************/
/****************************************************************************
  History

$Log: actions.h,v $
Revision 1.5  2008/02/21 13:22:36  ganovelli
QT version. Everything working except server and client runing on the same machine.
Network exceptions not handled, when you stop the client is likely the server will crash too.

Revision 1.4  2007/07/04 13:28:30  ganovelli
halfway  version for thumbnails

Revision 1.3  2007/03/17 12:26:14  ganovelli
* pragma replaced by #ifndef directive
* Player operator= added
* bug in race_simulation.cpp corrected
* msvc2005 solutions added

Revision 1.2  2007/03/11 15:08:52  ganovelli
*** empty log message ***

Revision 1.1  2007/03/10 16:43:35  ganovelli
first working draft


*****************************************************************************/

#include <race.h>

/// type Action  
typedef std::pair <std::string,C2SMessage> Action;
/// actions to be done
typedef std::vector< Action> Actions;
/// vector forward iterator for vector of Action
typedef Actions::iterator ActionsIterator;
/// actions to be done
extern std::vector< Action> actionsToDo;
/// mutex on the actions to be done 
extern QMutex  mutex_on_actionsToDo; 

#endif
