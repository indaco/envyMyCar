#ifndef _NVMC_CIRCUIT_
#define _NVMC_CIRCUIT_

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

$Log: circuit.h,v $
Revision 1.9  2007/07/04 13:28:30  ganovelli
halfway  version for thumbnails

Revision 1.8  2007/03/29 21:52:44  ganovelli
added builder of circuits.

Revision 1.7  2007/03/28 23:58:35  ganovelli
added load/save functions for the circuit, first working draft of the ircuit builder

Revision 1.6  2007/03/28 20:14:16  ganovelli
added trees

Revision 1.5  2007/03/27 23:10:29  ganovelli
added holes and tunnels to the Street
added buildings to the Circuit
added server to client transmission of each player state
added BRAKING and BOOSTING to the player state
added sun position

Revision 1.4  2007/03/17 12:26:14  ganovelli
* pragma replaced by #ifndef directive
* Player operator= added
* bug in race_simulation.cpp corrected
* msvc2005 solutions added

Revision 1.3  2007/03/11 18:11:59  ganovelli
minor modif

Revision 1.2  2007/03/11 15:08:52  ganovelli
*** empty log message ***

Revision 1.1  2007/03/10 16:43:35  ganovelli
first working draft


*****************************************************************************/

#include <vector>
#include <vcg/space/box3.h>
#include "street.h"

/** A Circuit is a street, a number of entry points and the bounding box. 
In the final version the circuit will entirely describe the place where the race is taking place,
therefore this class is bound to be reatly extended.
*/
class Circuit{

public:
	/** the street	*/
	Street street;

	/** the bounding box of the whole circuit */
	vcg:: Box3f bbox;

	/** The position  of the sun */
	vcg::Point4f sun_position;

	/** A Building is stored as its footprint and its height 
	*/
	struct Building{
		std::vector<Vertex> footprint;
		float height;
	};

	/** buildings: a vector containing all the buildings */
	std::vector<Building> buildings;

	/** BuildingsIterator an iterator over the buildings */
	typedef std::vector<Building>::iterator BuildingsIterator;

	/** A Tree is stored as its position and  its height 
	*/
	struct Tree{
		vcg::Point3f pos;
		float height;
	};

	/** trees: a vector containing all the trees */
	std::vector<Tree> trees;

	/** TreesIterator an iterator over the trees */
	typedef std::vector<Tree>::iterator TreesIterator;

	/** Save the circuit */
	void Save(char * filename);

	/** Load the circuit */
	void Load(char * filename);
};

#endif