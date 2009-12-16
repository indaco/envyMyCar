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

$Log: process_message.cpp,v $
Revision 1.11  2008/02/21 13:22:37  ganovelli
QT version. Everything working except server and client runing on the same machine.
Network exceptions not handled, when you stop the client is likely the server will crash too.

Revision 1.10  2008/02/20 13:25:49  ganovelli
DO NOT USE THIS VERSION
INTERMEDIATE version> passing from ptypes to qt
client side working, server side still to be done

Revision 1.9  2007/07/17 09:44:48  ganovelli
visualization of other snapshots working

Revision 1.8  2007/07/17 09:06:46  ganovelli
time of updating

Revision 1.7  2007/07/17 09:03:50  ganovelli
bug: texture ID cannot be assigned here

Revision 1.6  2007/07/17 07:40:45  ganovelli
*** empty log message ***

Revision 1.4  2007/07/16 16:59:41  ganovelli
exchange of screenshot data-draft of drawing others screenshots

Revision 1.3  2007/07/16 09:42:38  ganovelli
exchange of screenshot data-draft of drawing others screenshots

Revision 1.2  2007/07/04 13:28:30  ganovelli
halfway  version for thumbnails

Revision 1.1  2007/04/09 23:08:42  ganovelli
added standalone mode


****************************************************************************/
#include <GL/glew.h>
#include <time.h>
#include <process_message.h>
#include <messages.h>
#include <packaging.h>
#include "race_simulation.h"

void GetNewFrame(Frame & f){f.SetIdentity(); *(vcg::Point3f*)&f[3][0] = race.circuit->street.entry_points[0];}

int ProcessMessageServer(std::string msg,std::string host){
	/*first draft: the messages are only commands. The subscribtion to the game
		is automatic at the first command */
	Race::PlayersIterator pi;
	int st=clock();
	race.mutex_on_players.lock();
	//printf("process message, %d\n",race.players.size());
	pi =race.FindPlayer(host);
	if(pi == race.players.end())
		{//its a new player
			pi = race.AddPlayer();
 //			printf("adding player, now %d",race.players.size());
			(*pi).ip_address = QHostAddress(QString(host.c_str()));
			QString prov = QString(host.c_str());
			//initialization of the player
			GetNewFrame((*pi).car.frame);	
			(*pi).car.vel = vcg::Point4f(0.0,0.0,0.0,0.0);
			(*pi).car.acc = vcg::Point4f(0.0,0.0,0.0,0.0);
			(*pi).car.steering_angle = 0.0;
			(*pi).car.back_wheel_pos = 1.0;
			(*pi).car.front_wheel_pos = -1.0;
			(*pi).car.max_speed = 100; // 360 km/h
			(*pi).state = Player::PLAYING;
			(*pi).screenshot.Init(256,256);
			(*pi).last_updated = 0;
			printf("%s joined the race\n",(*pi).ip_address.toString().toAscii().data()); 
		}
	race.mutex_on_players.unlock();

	/* now queue the action */
	mutex_on_actionsToDo.lock();
	std::string ddd ( (*pi).ip_address.toString().toAscii().data());
	actionsToDo.push_back(Action( ddd,UnPack(msg)));
	mutex_on_actionsToDo.unlock();
	//printf("SERVER: received %s!\n",msg);
	//printf("message processed in %d\n",clock()-st);	
	//printf("process message EXIT, %d\n",race.players.size());


return 0;
}

int ProcessMessageServer(const C2SMessage & msg,const std::string & sender){

	// at the present there is only one message usginthe stream
	// no need to check the message header
	race.mutex_on_players.lock();
	Race::PlayersIterator pi = race.FindPlayer(sender);
	assert(pi != race.players.end());
	memcpy((*pi).screenshot.pixels,msg.body,msg.body_length);
	// deallocate the memory alocated
	// note: the message body is allocated in the DataExchangeThread
	free ( msg.body );
	(*pi).last_updated = clock();
	race.mutex_on_players.unlock();

	return 0;
}


/** process the message: first draft, the message is:
gTime, list of (ip addresses,Frame) */
int ProcessMessagePlayer(std::string msg,std::string host){

	/* we dont't care about the host, in this version it can only be server */
	float fr[16];
	float sa;
	int state;
	const char* p = msg.c_str();
	char  ipaddr[255];
	vcg::Point4f vel;

	int st = clock();
	sscanf(p,"%s %f %f %f %f  %f %f %f %f  %f %f %f %f  %f %f %f %f %f %f %f %f %f",
		ipaddr,		&fr[0],		&fr[1],		&fr[2],		&fr[3],		&fr[4],		&fr[5],		&fr[6],		&fr[7],		&fr[8],
		&fr[9],		&fr[10],		&fr[11],		&fr[12],		&fr[13],		&fr[14],		&fr[15],		&vel[0],		&vel[1],
		&vel[2],		&vel[3]	, &sa, &state	);


	Race::PlayersIterator pi;
	race.mutex_on_players.lock();

	pi = race.FindPlayer(std::string(ipaddr));
	if(pi == race.players.end()){/* it's a new player*/
 			pi = race.AddPlayer();
			(*pi).ip_address = ipaddr;
			(*pi).car.front_wheel_pos = -1;
			(*pi).car.back_wheel_pos =  1;
			(*pi).screenshot.Init(256,256);
	}

	Player & pl = (*pi);

	memcpy(&pl.car.frame[0][0],&fr[0],16*sizeof(float));
	memcpy(&pl.car.vel[0],&vel[0],4*sizeof(float));
	pl.car.steering_angle = sa;
	pl.state = state;
	race.mutex_on_players.unlock();

	return 0;
}



int ProcessMessagePlayer(const S2CMessage & msg){
	unsigned char l;
	memcpy(&l,msg.body,1);// length of the ip_address
	char ipaddress[16];
	unsigned char * data =(unsigned char *)msg.body ;
	memcpy(ipaddress,&(data[1]),l);
	ipaddress[l]='\0';
	std::string ipa(ipaddress);

	Race::PlayersIterator pi;
	race.mutex_on_players.lock();
	pi = race.FindPlayer(ipa);
	assert(pi != race.players.end());
	memcpy((*pi).screenshot.pixels,&data[l+1],256*256*3);
	race.mutex_on_players.unlock();
	(*pi).screenshot.textureUpToDate = false;	
	//SaveFloat("rec.raw",256,256,(*pi).screenshot.pixels);
	// deallocate the memory alocated
	// note: the message body is allocated in the DataExchangeThread
	free ( msg.body );

	return 0;
}
