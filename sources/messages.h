#ifndef _NVMC_MESSAGES_
#define _NVMC_MESSAGES_
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
 * History
 *
 * $Log: messages.h,v $
 * Revision 1.5  2007/07/16 09:42:38  ganovelli
 * exchange of screenshot data-draft of drawing others screenshots
 *
 * Revision 1.4  2007/07/04 13:28:30  ganovelli
 * halfway  version for thumbnails
 *
 * Revision 1.3  2007/03/17 12:26:14  ganovelli
 * pragma replaced by #ifndef directive
 * Player operator= added
 * bug in race_simulation.cpp corrected
 * msvc2005 solutions added
 *
 * Revision 1.2  2007/03/11 15:08:52  ganovelli
 *** empty log message ***
 *
 * Revision 1.1  2007/03/10 16:43:36  ganovelli
 * first working draft
 *
 *
 ****************************************************************************/
/**@name  Client server messages
 */
//@{
/// values for a message from a client to the server
typedef enum
{
    // all the command
    COMMAND_INCREASE_SPEED  = 0x01, // this message says to increase speed
    COMMAND_DECREASE_SPEED  = 0x02, // this message says to decrease speed
    COMMAND_TURN_RIGHT      = 0x04, // this message says to turn right
    COMMAND_TURN_LEFT       = 0x08, // this message says to turn left
    COMMAND_BOOST           = 0x10, // this message says to boost (whatever it is)
    COMMAND_BRAKE           = 0x20, // this message says to stop
    COMMAND_RESTART         = 0x40, // this message says to restart
    
    DATA_SNAPSHOT           = 0x80 // the sender transmit a snapshot
}

C2SHeaderValue;

/// values for a message from  the server  to a client
typedef enum
{
    DATA_ALL_CARS_STATE     = 0, // this message contains the state of all the cars
    DATA_PLAYER_SNAPSHOT    = 1, // the snapshot of a player
    COMMAND_SERVER_QUITTING = 2 // the server is quitting
}
S2CHeaderValue;

/** Message  */
struct Message
{
    /** message body lenght */
    int body_length;
    
    /** message header is a HeaderValue value*/
    char header;
    
    /** message body*/
    void * body;
};

/** C2SMessage: client to server message */
struct C2SMessage:public Message
{
///
    C2SMessage()
    {}
///
    C2SMessage(C2SHeaderValue value)
    { header = value;}
    
};

/** S2CMessage: server to client message */
struct S2CMessage:public Message
{
    
};

//@}
#endif

