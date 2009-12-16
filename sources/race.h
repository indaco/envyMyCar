#ifndef _NVMC_RACE_
#define _NVMC_RACE_
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

$Log: race.h,v $
Revision 1.7  2008/02/20 13:25:49  ganovelli
DO NOT USE THIS VERSION
INTERMEDIATE version> passing from ptypes to qt
client side working, server side still to be done

Revision 1.6  2008/02/18 10:17:25  ganovelli
added mechanism for knowing who's the local player

Revision 1.5  2008/02/13 18:59:02  ganovelli
*** empty log message ***

Revision 1.4  2007/03/17 12:26:14  ganovelli
* pragma replaced by #ifndef directive
* Player operator= added
* bug in race_simulation.cpp corrected
* msvc2005 solutions added

Revision 1.3  2007/03/11 18:11:59  ganovelli
minor modif

Revision 1.2  2007/03/11 15:08:52  ganovelli
*** empty log message ***

Revision 1.1  2007/03/10 16:43:36  ganovelli
first working draft

*****************************************************************************/

#include <QtCore/QMutex>
#include <string>
#include <list>
#include <circuit.h>
#include "car.h"
#include "player.h"




/** a Race is a circuit plus a number of players */
class Race{


public:
	typedef  std::list<Player>::iterator PlayersIterator;


	/** constructor */
	Race(){ }

	/** destructor */
	~Race(){}

	/** boolean attributes*/
	enum {
		ONGOING  = 0x001, // the race is going on
		FROZEN   = 0x002, // the race is frozen
	};
	/** state of the race */
	int state;

	/** starting time */
	int start_time;

	/** circuit where the race is taking place*/
	Circuit * circuit;

	/** global time when the state was built */
	int state_time;

	/** type of list of players */
	typedef std::list<Player > PlayerContainer;
	/** players*/
	PlayerContainer players;

	/** find a player */
	PlayersIterator FindPlayer(const std::string  & ip){
		QHostAddress qip(QString(ip.c_str()));
		PlayersIterator pi = players.begin();
		while(pi!=players.end()){
			if( (*pi).ip_address == qip) return pi;
			++pi;
		}
		return pi;
	}

	/** Add a player to the list of players */
	PlayersIterator AddPlayer( ){
			players.push_back(Player()); 
			PlayersIterator i = players.end(); 
			--i;
			return i;
	}


	/** mutex on the lit of players */
	QMutex mutex_on_players;

};

extern Race race;
#endif