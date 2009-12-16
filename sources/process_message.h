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

$Log: process_message.h,v $
Revision 1.3  2008/02/20 13:25:49  ganovelli
DO NOT USE THIS VERSION
INTERMEDIATE version> passing from ptypes to qt
client side working, server side still to be done

Revision 1.2  2007/07/16 09:42:38  ganovelli
exchange of screenshot data-draft of drawing others screenshots

Revision 1.1  2007/04/09 23:08:42  ganovelli
added standalone mode



****************************************************************************/

#ifndef __PROCESS_MESSAGE__
#define __PROCESS_MESSAGE__

#include <string>
#include "messages.h"

int ProcessMessageServer(std::string msg,std::string host);
int ProcessMessageServer(const C2SMessage & msg,const std::string & sender);

int ProcessMessagePlayer(std::string msg,std::string host);
int ProcessMessagePlayer(const S2CMessage & msg);

#endif