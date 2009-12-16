#ifndef _NVMC_PLAYER_
#define _NVMC_PLAYER_
/****************************************************************************
* NVMC                                                                      *
* Visual and Computer Graphics Library                                      *
*                                                                           *
* Copyright(C) 2007                                                         *
* ISTI - Italian National Research Council                                  *
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

$Log: player.h,v $
Revision 1.8  2008/02/21 13:22:36  ganovelli
QT version. Everything working except server and client runing on the same machine.
Network exceptions not handled, when you stop the client is likely the server will crash too.

Revision 1.7  2008/02/20 13:25:49  ganovelli
DO NOT USE THIS VERSION
INTERMEDIATE version> passing from ptypes to qt
client side working, server side still to be done

Revision 1.6  2007/07/16 09:42:38  ganovelli
exchange of screenshot data-draft of drawing others screenshots

Revision 1.5  2007/07/04 13:28:30  ganovelli
halfway  version for thumbnails

Revision 1.4  2007/03/27 23:10:29  ganovelli
added holes and tunnels to the Street
added buildings to the Circuit
added server to client transmission of each player state
added BRAKING and BOOSTING to the player state
added sun position

Revision 1.3  2007/03/17 12:26:14  ganovelli
* pragma replaced by #ifndef directive
* Player operator= added
* bug in race_simulation.cpp corrected
* msvc2005 solutions added

Revision 1.2  2007/03/11 15:08:52  ganovelli
*** empty log message ***

Revision 1.1  2007/03/10 16:43:36  ganovelli
first working draft


*****************************************************************************/

#include <car.h>
#include "messages.h"
#include "screenshot.h"
#include <qt4/QtNetwork/QHostAddress>

/** a player owns a car plus attributes such as pausing, withdrawn etc.. */
struct Player{

	/** constructor */
	Player(){}

	/** copy constructor*/
 	Player(const Player & p){ car = p.car;ip_address = p.ip_address;state = p.state; screenshot = p.screenshot; last_updated = p.last_updated; }

	/** destructor */
	~Player(){}

	void operator=(const Player & p){ car = p.car;ip_address = p.ip_address; state = p.state;last_updated = p.last_updated;}

	/** boolean attributes*/
	enum {
		PLAYING  = 0x001, // it's running or pausing
		PAUSING  = 0x002, // it's pausing
		WAITING  = 0x004, // ready and waiting to run
		WITHDRAWN= 0x008, // withdrawn
		BRAKING  = 0x010, // it is braking
		BOOSTING = 0x020  // it is boosting
	};
	/** state of the player */
	int state;

	/** the player's car*/
	Car car;

	/** ip address of the player */
	QHostAddress ip_address; 

	/** current screenshot of the player */
	Screenshot screenshot;

	/** mutex on the player data	 */
	QMutex  mutex_on_data;

	/** last time data where sent to the id	 */
	int last_sent;

	/** last time data was updated	 */
	int last_updated;

};


#endif
