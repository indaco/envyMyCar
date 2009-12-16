#ifndef _NVMC_CAR_
#define _NVMC_CAR_
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

$Log: car.h,v $
Revision 1.5  2007/03/21 10:34:22  ganovelli
added better steering,

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

#include <vcg/space/box3.h>
#include <frame.h>

///
struct Condition;
struct Avatar;

/** this class defines a car. From the simulation point of view a car is identified
by its bounding box  plus a car Condition (damages,dirtyness etc.) and a car avatar*/
struct Car{
	
	/** construction */
	Car(){ }

	/** car destructor */
	~Car(){ }

	/** copy constructor */
	Car(const Car & c){bbox = c.bbox; condition=c.condition; frame = c.frame;}

	/** bounding box of the car */
	vcg::Box3f bbox;

	/** condition of the car */
	Condition * condition;

	/** position of the car */
	Frame  frame;

	/** linear velocity of the car */
	vcg::Point4f vel;

	/** linear acceleration of the car */
	vcg::Point4f acc;

	/** steering angle of the car [-45°,45°]*/
	float steering_angle;

	/** position of the back wheels (along z)*/
	float back_wheel_pos;

	/** position of the front wheels (along z)*/
	float front_wheel_pos;

	/** max speed  of the car (meters/hour) */
	float max_speed;

	/** avatar of the car */
	Avatar * avatar;
};


/** the Condition of a car influences how the car behave (in the server) and how it looks (in the client) */
struct Condition{

	/** max damage that can be inflicted to a car */
	static int & MaxDamage(){ static int max_damage = 0; return max_damage;}

	/** how much  a car can be dirty */
	static int & MaxDirtyness(){ static int max_damage = 0; return max_damage;}

	/** damage of the car, 0: fully functional- MaxDamage(): barely moving */
	int damage_points;

	/** damage of the car, 0: clean - MaxDirtiness(): unwatchable */
	int dirtyness_points;

};

/** the Avatar is the description of the car to be used in all the clients except in the client of 
the car owner, where the rendering is entirely up to the owner. */
struct Avatar{
	// in this release no specification is given
};

#endif