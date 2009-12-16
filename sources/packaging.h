#ifndef _NVMC_PACKAGING_
#define _NVMC_PACKAGING_
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

$Log: packaging.h,v $
Revision 1.7  2008/02/21 13:22:36  ganovelli
QT version. Everything working except server and client runing on the same machine.
Network exceptions not handled, when you stop the client is likely the server will crash too.

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

*****************************************************************************/
#include "messages.h"
#include <frame.h>

 
/**@name Packaging
* these function convert Messages to string and string to messages
*/
//@{ 
///pack a frame into a string
std::string Pack(const Frame & frame);
///pack a float into a string
std::string Pack(const  float & v);
/// unpack a string containint a frame in a C2SMessage
C2SMessage UnPack(const std::string & mess);
/// pack a C2SMessage message in a string
std::string Pack(const C2SMessage & mess);
/// pack a vcg::Point4f in a string
std::string Pack(const  vcg::Point4f & f);
/// pack an integer in a string
std::string Pack(const int & v);
//@}
#endif