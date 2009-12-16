#ifndef _NVMC_FRAME_
#define _NVMC_FRAME_
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

$Log: frame.h,v $
Revision 1.7  2008/02/22 16:55:00  ganovelli
compiled for linux

Revision 1.6  2007/06/12 08:38:20  ganovelli
*** empty log message ***

Revision 1.5  2007/05/31 14:26:24  ganovelli
implemented world<->frame transformation

Revision 1.4  2007/03/21 10:34:22  ganovelli
added better steering,

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

#include <vcg/math/matrix44.h>

/// the reference system of the car
class Frame: public vcg::Matrix44f{

public:
	/** transforms a point from word coordinates to this frame coordinates**/ 
	vcg::Point4f FromWordCoord(vcg::Point4f p){
		vcg::Point4f po = (p-O()),res;
		res[0] = Axis(0)*po;
		res[1] = Axis(1)*po;
		res[2] = Axis(2)*po;
		return res;
	}

	/** transforms a point from this frame coordinates to the world coordinates**/ 
	vcg::Point4f ToWordCoord(vcg::Point4f p){ return O() + Axis(0)*p[0]+Axis(1)*p[1]+Axis(2)*p[2];}

	/** origin of the frame **/
	vcg::Point4f & O(){ return *(vcg::Point4f*)&(*this)[3][0];}

	/** axis 0=x, 1=y, 2=z **/
	vcg::Point4f & Axis(const int & i){ assert(i>=0); assert(i<3); return *(vcg::Point4f*)&(*this)[i][0];}
};
#endif
