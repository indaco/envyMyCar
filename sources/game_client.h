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

$Log: game_client.h,v $
Revision 1.10  2008/02/21 13:22:34  ganovelli
QT version. Everything working except server and client runing on the same machine.
Network exceptions not handled, when you stop the client is likely the server will crash too.

Revision 1.9  2008/02/20 13:25:48  ganovelli
DO NOT USE THIS VERSION
INTERMEDIATE version> passing from ptypes to qt
client side working, server side still to be done

Revision 1.8  2008/02/18 10:17:23  ganovelli
added mechanism for knowing who's the local player

Revision 1.7  2007/07/17 10:30:11  ganovelli
added local ip

Revision 1.6  2007/07/16 17:12:45  ganovelli
exchange of screenshot data-draft of drawing others screenshots

Revision 1.5  2007/07/04 13:28:30  ganovelli
halfway  version for thumbnails

Revision 1.4  2007/04/09 23:08:41  ganovelli
added standalone mode

Revision 1.3  2007/03/29 21:52:44  ganovelli
added builder of circuits.

Revision 1.2  2007/03/11 18:11:59  ganovelli
minor modif

 *****************************************************************************/

#include <QtNetwork/QHostAddress>
#include <race.h>
#include "simple_circuit_creator.h"
#include <messages.h>
#include <data.h>

#include "myclient/TestEventHandler.h"
/** Application */
extern CTestEventHandler TheApp;
///

struct NvmcClient {
///all the circuits
    std::vector<Circuit> circuits;

    /// is in standalone mode
    bool standalone_mode;

    /** start up the game client */
    int Initialize(char * circuitFile, bool standalone);

    /** start the main loop */
    int Start();

    /** close the client  */
    int Terminate();

    /** post a command */
    int Command(C2SHeaderValue value);

    /** copy of race.players made by UpdatePlayers */
    Race::PlayerContainer players;

    /** copy of race.players made by UpdatePlayers */
    Race::PlayersIterator local_player;

    /** makes a copy of race.players (accessed by the receiver thread */
    void UpdatePlayers();

    /** snapshot of the local viewer */
    Screenshot screenshot;

    /** ip of the local player **/
    QHostAddress local_ip;

    /** take a snapshot and put it in dataToSend */
    void SendScreenshot();

    /** draw the other screenshots */
    void DrawScreenshots(std::string big_ip_address);

    /** messages to send to the  server (UDP)*/
    std::vector<std::string> messagesToSend;

    /** mutex on  messagesToSend	 (UDP*/
    QMutex mutex_on_messagesToSend;

    /** data to send to the server (TCP) **/
    std::vector<C2SMessage> dataToSend;

    /** mutex on data to send **/
    QMutex mutex_on_dataToSend;

};

///
extern NvmcClient cli;