#ifndef _NVMC_RACE_SIMULATION_
#define _NVMC_RACE_SIMULATION_
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
/*****************************************************************************
  History

$Log: race_simulation.h,v $
Revision 1.4  2008/02/22 16:55:00  ganovelli
compiled for linux

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
extern int gTime ;
#include <player.h>
#include <actions.h>
/**@name simulation
* bla bla bla
*/
//@{ 
///steer about d degrees 
void steer(float d, Player & p);
/// accelerate d meters for square second
void acc(float d, Player & p);
/// update player state
void Update(int ms, Player & p);
/// process an action
void ProcessAction( Action a);
/// main simulation cycle
int run_race(void*);
//@}

#endif

