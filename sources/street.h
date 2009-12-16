#ifndef _NVMC_STREET_
#define _NVMC_STREET_
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

$Log: street.h,v $
Revision 1.6  2007/04/02 19:15:57  ganovelli
added tunnel generation from bitmap and some better steering

Revision 1.5  2007/03/28 23:58:35  ganovelli
added load/save functions for the circuit, first working draft of the ircuit builder

Revision 1.4  2007/03/27 23:10:30  ganovelli
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

#include <vector>
#include <vcg/space/point3.h>
#include <vcg/space/point2.h>
#include <vcg/simplex/vertexplus/base.h>
#include <vcg/simplex/vertexplus/component.h>

 
class DummyType;
class Vertex : public vcg::VertexSimp1<Vertex,DummyType,vcg::vert::Coord3f>{
public:
	Vertex(){}
	Vertex(vcg::Point3f p){P() = p;}
};

/// In this draft the stree is merely a path
class Street{

public:

	/** street:
		The street is a vector of couple of 3D points. Each couple defines the left and right
		border of the street, respectively, so that the pavement can be rendered as a series
		of quads  { street[i][0],street[i][1],street[i+1][1],street[i+1][0])
	*/
	std::vector<vcg::Point2<Vertex> > path;

	/** entry points */
	std::vector<vcg::Point3f> entry_points;

	/** hole:
		A Hole is stored as the border of the hole ( a sequence of vertices in counter-clock wise order ) and its depth. 
		*/
	struct Hole{
		std::vector<Vertex> border;
		float depth;
	};

	/** holes:
	a vector of all the holes in the street 
	*/
	std::vector<Hole> holes;
	
	/** Tunnel:
			a tunnel is described in the same manner as the path, plus a height value.
			The tunnel is not considered by the server, it only exists for rendering purpose.
	*/
	struct Tunnel{
		std::vector<vcg::Point2<Vertex> > path;
		float heigth;
	};

	/** tunnels:
	a vector of all the tunnels in the circuit 
	*/
	std::vector<Tunnel> tunnels;


	/// iterator over the tiles
	typedef 	std::vector<vcg::Point2<Vertex> >::iterator TilesIterator;

	/// iterator over the holes
	typedef 	std::vector<Hole >::iterator HolesIterator;

	/// iterator over the tunnels
	typedef 	std::vector<Tunnel >::iterator TunnelsIterator;

	/** save */
	void Save(FILE * f);

	/** load */
	void Load(FILE * f);
};
#endif