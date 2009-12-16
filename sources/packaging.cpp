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

$Log: packaging.cpp,v $
Revision 1.7  2008/02/22 16:55:00  ganovelli
compiled for linux

Revision 1.6  2008/02/20 13:25:49  ganovelli
DO NOT USE THIS VERSION
INTERMEDIATE version> passing from ptypes to qt
client side working, server side still to be done

Revision 1.5  2007/03/27 23:10:29  ganovelli
added holes and tunnels to the Street
added buildings to the Circuit
added server to client transmission of each player state
added BRAKING and BOOSTING to the player state
added sun position

Revision 1.4  2007/03/21 10:34:22  ganovelli
added better steering,

Revision 1.3  2007/03/17 12:26:14  ganovelli
* pragma replaced by #ifndef directive
* Player operator= added
* bug in race_simulation.cpp corrected
* msvc2005 solutions added

Revision 1.2  2007/03/11 15:08:52  ganovelli
*** empty log message ***

Revision 1.1  2007/03/10 16:43:36  ganovelli
first working draft

Revision 1.5  2007/03/04 18:34:53  ganovell
*****************************************************************************/


#include "packaging.h"
#include <vcg/space/point4.h>
#include <string>

std::string stringV(const float & v){
	char buf[255];
	sprintf(buf,"%f",v);
	return std::string(&buf[0]);
}
 std::string stringV(const int & v){
	char buf[255];
	sprintf(buf,"%d",v);
	return std::string(&buf[0]);
}
///
std::string Pack(const  vcg::Point4f & f){ 
	std::string s;
	int i;
	for(i = 0; i < 4; ++i)
			s += stringV(f[i]).append(" ");
	return s;
}

///
std::string Pack(const  float & v){ 
	return stringV(v).append(" ");
}
///
std::string Pack(const  Frame & frame){ 
	std::string s,ds;
	int i,j;
	for(i = 0; i < 4; ++i)
		for(j = 0; j < 4; ++j)
			s += stringV(frame[i][j]).append(" ");

	return s;
}

/// 
std::string Pack(const int & v){
	return stringV(v).append(" ");
}

///
C2SMessage UnPack(const std::string & mess){
	C2SMessage m;
	m.header = atoi(&mess[0]);
	return m;
}

///
std::string Pack(const C2SMessage & mess){
	char buffer[10];
	sprintf(buffer,"%d",mess.header);	
	return std::string(buffer);
}

