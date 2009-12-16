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
 * History
 *
 * $Log: main_clt.cpp,v $
 * Revision 1.4  2007/07/04 13:28:30  ganovelli
 * halfway  version for thumbnails
 *
 * Revision 1.3  2007/04/09 23:08:41  ganovelli
 * added standalone mode
 *
 * Revision 1.2  2007/03/29 21:52:44  ganovelli
 * added builder of circuits.
 *
 * Revision 1.1  2007/03/11 15:10:17  ganovelli
 * first working draft
 *
 * Revision 1.2  2007/03/11 15:08:51  ganovelli
 *** empty log message ***
 *
 * Revision 1.1  2007/03/10 16:43:35  ganovelli
 * first working draft
 *
 ****************************************************************************/
#include <iostream>
using std::cerr;
using std::endl;

#include "game_client.h"
#include <GL/glut.h>
#include "myclient/TestEventHandler.h"


int main(int argc, char**argv) {
    try {
        return (CTestEventHandler::Execute(argc, argv));
    } catch (CTestEventHandlerException &ex) {
        cerr << "Exception Occurred: " << ex.what() << endl;
    }
}