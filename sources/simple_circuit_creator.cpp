#pragma once
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

$Log: simple_circuit_creator.cpp,v $
Revision 1.4  2007/07/04 13:28:30  ganovelli
halfway  version for thumbnails

Revision 1.3  2007/03/27 23:10:30  ganovelli
added holes and tunnels to the Street
added buildings to the Circuit
added server to client transmission of each player state
added BRAKING and BOOSTING to the player state
added sun position

Revision 1.2  2007/03/11 18:11:59  ganovelli
minor modif

Revision 1.1  2007/03/11 15:08:52  ganovelli
*** empty log message ***

Revision 1.1  2007/03/10 16:43:37  ganovelli
first working draft

****************************************************************************/
#include "simple_circuit_creator.h"

#define M_PI       3.14159265358979323846

///
void CreateCircularCircuit(Circuit & c){

	// create a circular circuit centered at 0,0,0 with radius 3000 (meters)
	// the street will be 10 meters large

	int sides = 1000; 
	float step = float(2*M_PI/sides);

	for(int i = 0; i < sides;++i){
		vcg::Point3f l = vcg::Point3f(cos(i*step),0.0,-sin(i*step)) * 3005;
		vcg::Point3f r = vcg::Point3f(cos(i*step),0.0,-sin(i*step)) * 2995;
		c.bbox.Add(l);
		c.bbox.Add(r);
		c.street.path.push_back( vcg::Point2<Vertex>());
		c.street.path.back()[0].P() = l;
		c.street.path.back()[1].P() = r;
	}
	
	c.bbox.max = c.bbox.max*1.1f;
	c.bbox.min = c.bbox.min*1.1f;

	c.street.entry_points.push_back(vcg::Point3f(3000,0,0));
}