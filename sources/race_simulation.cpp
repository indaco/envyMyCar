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

$Log: race_simulation.cpp,v $
Revision 1.10  2008/02/21 13:22:37  ganovelli
QT version. Everything working except server and client runing on the same machine.
Network exceptions not handled, when you stop the client is likely the server will crash too.

Revision 1.9  2008/02/20 13:25:49  ganovelli
DO NOT USE THIS VERSION
INTERMEDIATE version> passing from ptypes to qt
client side working, server side still to be done

Revision 1.8  2007/07/16 09:42:38  ganovelli
exchange of screenshot data-draft of drawing others screenshots

Revision 1.7  2007/04/02 19:15:57  ganovelli
added tunnel generation from bitmap and some better steering

Revision 1.6  2007/03/27 23:10:30  ganovelli
added holes and tunnels to the Street
added buildings to the Circuit
added server to client transmission of each player state
added BRAKING and BOOSTING to the player state
added sun position

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

Revision 1.1  2007/03/10 16:43:36  ganovelli
first working draft


*****************************************************************************/

#include "race_simulation.h"
#include "actions.h"


#include <time.h>
#include <race.h>
///
extern Race race;


///
int gTime ;

///
void steer(float d, Player & p){
	if(p.car.steering_angle+d < -M_PI*0.25)p.car.steering_angle=-float(M_PI)*0.25f;else
	if(p.car.steering_angle+d >  M_PI*0.25)p.car.steering_angle= float(M_PI)*0.25f;else
		p.car.steering_angle+=d;
}

///
void acc(float d, Player & p){
		vcg::Point4f  dir =- * (vcg::Point4f*)&p.car.frame[2][0];
		p.car.acc +=  dir * d;
	if(p.car.max_speed < p.car.vel.Norm()) 
	  p.car.vel = p.car.vel / p.car.vel.Norm() * p.car.max_speed;
}

///
void brake(Player & p){
	p.car.vel = p.car.vel*0.8f; 	
	if(p.car.vel.Norm() < 10)
		p.car.vel = vcg::Point4f(0.0,0.0,0.0,0.0);
	p.state |= Player::BRAKING;
}

///
void restart(Player & p){
	p.car.vel = vcg::Point4f(0.0,0.0,0.0,0.0);
	p.car.frame.SetIdentity();
	*(vcg::Point3f*)&p.car.frame[3][0] = race.circuit->street.entry_points[0];
}

///
void Update(int ms, Player & p){
	float delta = ms/(1000.f );
	p.car.vel += p.car.acc * delta;

	float d = -(p.car.vel * p.car.frame.Axis(2))* delta; // delta to move
  float cosa = cos(p.car.steering_angle);	
  float sina = sin(p.car.steering_angle);
	float length = -p.car.front_wheel_pos+p.car.back_wheel_pos;

	float l_prim = (length+d*cosa); 
	float ol = sqrt(l_prim*l_prim + d*d*sina*sina);
	float cosb = l_prim / ol;
	float sinb = d*sina / ol;

	vcg::Point4f w_bw = p.car.frame.O() + p.car.frame.Axis(2)*p.car.back_wheel_pos; 

	vcg::Matrix44f rotb; rotb.SetIdentity();
	rotb[0][0] = cosb;  rotb[0][2] = sinb;
	rotb[2][0] = -sinb; rotb[2][2] = cosb;

	/*rotate the axis */
	p.car.frame.Axis(0) = rotb * p.car.frame.Axis(0); 
	p.car.frame.Axis(1) = rotb * p.car.frame.Axis(1); 
	p.car.frame.Axis(2) = rotb * p.car.frame.Axis(2); 

	/*rotate the velocity vector */
	p.car.vel = rotb * p.car.vel; 

	/* rotate the origin with respect to the position of the back wheel*/
	p.car.frame.O() = rotb* (p.car.frame.O()-w_bw) + w_bw;

	/* move forward by ol-length */
	p.car.frame.O()+= -p.car.frame.Axis(2)*(ol-length);

	p.car.acc = vcg::Point4f(0.0,0.0,0.0,0.0);
	p.car.steering_angle = p.car.steering_angle*(1.0f/(1.0f+0.01f*p.car.vel.Norm()));
}

///
void ProcessAction( Action a){
//	printf("process action, players %d\n",race.players.size());
	Race::PlayersIterator pli;
	race.mutex_on_players.lock();
	pli = race.FindPlayer(a.first);
	race.mutex_on_players.unlock();

	Player & pl = (*pli);

	pl.mutex_on_data.lock();
	// reset action state:
	pl.state &= ~Player::BRAKING;
	pl.state &= ~Player::BOOSTING;

	switch(a.second.header){
		case COMMAND_INCREASE_SPEED: acc(10,pl); break;
		case COMMAND_DECREASE_SPEED: acc(-10,pl); break;
		case COMMAND_TURN_LEFT: steer(0.1f,pl); break;
		case COMMAND_TURN_RIGHT: steer(-0.1f,pl); break;
		case COMMAND_BRAKE: brake(pl); break;
		case COMMAND_RESTART: restart(pl); break;
	}
	pl.mutex_on_data.unlock();

}


