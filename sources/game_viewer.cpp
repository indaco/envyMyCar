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

$Log: game_viewer.cpp,v $
Revision 1.9  2007/10/08 13:03:39  ganovelli
 *** empty log message ***

Revision 1.8  2007/07/17 07:39:42  ganovelli
 *** empty log message ***

Revision 1.7  2007/07/16 09:42:38  ganovelli
exchange of screenshot data-draft of drawing others screenshots

Revision 1.6  2007/04/02 19:15:57  ganovelli
added tunnel generation from bitmap and some better steering

Revision 1.5  2007/03/29 21:52:44  ganovelli
added builder of circuits.

Revision 1.4  2007/03/21 10:34:22  ganovelli
added better steering,

Revision 1.3  2007/03/11 18:11:59  ganovelli
minor modif


 ****************************************************************************/

#include <SDL/SDL.h>
#include <math.h>
#include <time.h>
#include <vcg/space/point3.h>

#include <vector>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <algorithm>

#include "game_client.h"
#include "game_viewer.h"
#include "race.h"

#include "TestEventHandler.h"




/** Client  */
extern NvmcClient cli;



/* value of pi */
#define M_PI       3.14159265358979323846

/** viewport size */
int width, height;

bool mouse_BLDown;
int x_1, y_1, x_0, y_0;

vcg::Point3f obs(0, 400, 0);
float vieww = 0.5;

/** inizializzazione lo stato di opengl */
void init_opengl() {
    glPolygonMode(GL_FRONT, GL_FILL); // rasterizza solo i contorni dei poligoni
}

/** callback function for viewport resize.*/
void resize_screen(int w, int h) {

    width = w;
    height = h;
    glViewport(0, 0, width, height);
}

/** draw reference system*/
void draw_axis() {

    glPushAttrib(0xffffffff);
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0, 0, 0); //   X
    glVertex3f(10, 0, 0);

    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0, 0, 0); //   Y
    glVertex3f(0, 10, 0);

    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0, 0, 0); //   Z
    glVertex3f(0, 0, 10);
    glEnd();
    glPopAttrib();
}

void gl_print(float x, float y, const char *str) {
    glRasterPos2f(x, y);
    int len = (int) strlen(str);
    for (int i = 0; i < len; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
}

bool sendSS = false;

/** render the scene */
void draw_scene() {
    static int cn = 0;
    static int part = 0;
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_Delay(40);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /* here take the bounding box of the whole circuit */
    vcg::Point3f bmin = race.circuit->bbox.min;
    vcg::Point3f bmax = race.circuit->bbox.max;

    float sidex, sidez;
    sidex = bmax[0] - bmin[0];
    sidez = bmax[2] - bmin[2];

    cli.UpdatePlayers();


    if (!cli.players.empty())
        glOrtho(-6, 6, -6, 6, 0.0, 10.0);
    else
        glOrtho(-sidex*vieww, sidex*vieww, -sidez*vieww, sidez*vieww, 0.0, 400);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (!cli.players.empty()) {
        vcg::Point4f pos = (*cli.players.begin()).car.frame.O();
        gluLookAt(pos[0], 6.0, pos[2], pos[0], pos[1], pos[2], 0, 0, -1);
    } else {
        gluLookAt(obs[0], obs[1], obs[2], obs[0], obs[1] - 400, obs[2], 0, 0, -1);
    }
    // draw bounding box of the terrain
    glColor3f(0.1, 0.2, 0.4);
    glBegin(GL_QUADS);
    glVertex3f(bmin[0], bmin[1], bmin[2]);
    glVertex3f(bmax[0], bmin[1], bmin[2]);
    glVertex3f(bmax[0], bmin[1], bmax[2]);
    glVertex3f(bmin[0], bmin[1], bmax[2]);
    glEnd();

    glPushMatrix();
    glScalef(bmax[0] - bmin[0], bmax[1] - bmin[1], bmax[2] - bmin[2]);
    draw_axis();
    glPopMatrix();

    // draw circuit	
    Street::TilesIterator ti;
    int i;
    glColor3f(1.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT, GL_LINE);
    glBegin(GL_QUAD_STRIP);
    for (i = 0, ti = race.circuit->street.path.begin(); ti != race.circuit->street.path.end(); ++ti, ++i) {
        vcg::Point3f p0, p1;
        p0 = (*ti)[0].P();
        p1 = (*ti)[1].P();
        glVertex3f(p0[0], p0[1] + 0.1, p0[2]);
        glVertex3f(p1[0], p1[1] + 0.1, p1[2]);
    }
    glEnd();

    // draw tunnels	
    Street::TunnelsIterator tni;
    glColor3f(1.0, 1.0, 0.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    for (i = 0, tni = race.circuit->street.tunnels.begin(); tni != race.circuit->street.tunnels.end(); ++tni, ++i) {
        glBegin(GL_QUAD_STRIP);
        for (i = 0, ti = (*tni).path.begin(); ti != (*tni).path.end(); ++ti, ++i) {
            vcg::Point3f p0, p1;
            p0 = (*ti)[0].P();
            p1 = (*ti)[1].P();
            glVertex3f(p0[0], p0[1] + 0.2, p0[2]);
            glVertex3f(p1[0], p1[1] + 0.2, p1[2]);
        }
        glEnd();
    }

    // draw buildings
    Circuit::BuildingsIterator bi;
    glColor3f(1.0, 1.0, 1.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    for (bi = race.circuit->buildings.begin(); bi != race.circuit->buildings.end(); ++bi) {
        glBegin(GL_POLYGON);
        for (i = 0; i < (*bi).footprint.size(); ++i)
            glVertex3f((*bi).footprint[i].P()[0], (*bi).footprint[i].P()[1], (*bi).footprint[i].P()[2]);
        glEnd();
    }

    // draw trees
    Circuit::TreesIterator tsi;
    glColor3f(10.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    for (tsi = race.circuit->trees.begin(); tsi != race.circuit->trees.end(); ++tsi)
        glVertex3f((*tsi).pos[0], (*tsi).pos[1], (*tsi).pos[2]);
    glEnd();

    // draw players
    Race::PlayersIterator pi;
    int st = clock();
    /* updte the state of the players as received by the server */

    for (pi = cli.players.begin(); pi != cli.players.end(); ++pi) {
        glPushMatrix();
        /* apply transformation coded in the frame */
        Frame f = ((*pi).car.frame);
        glMultMatrixf(&f[0][0]);
        glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);

        glRotatef(90, 0, 1, 0);
        glutSolidTeapot(3.0); // draw the teapot (300 meters in size! )

        glColor3f(0, 1, 0);
        glBegin(GL_LINES);
        glVertex3f(0.0, 1.0, 1.0);
        glVertex3f(0.0, 1.0, -1.0);
        glEnd();

        glColor3f(0, 0, 1);
        glTranslatef(0.0, 0.0, (*pi).car.front_wheel_pos);
        glRotatef((*pi).car.steering_angle * 180.0 / M_PI, 0, 1, 0);
        glBegin(GL_LINES);
        glVertex3f(0.0, 1.0, 0.4);
        glVertex3f(0.0, 1.0, -0.4);
        glEnd();

        glPopMatrix();
        glColor3f(1.0, 0.0, 0.0);
        gl_print(100.0, 100.0, ((*pi).ip_address.toString()).toAscii().data()); // write the IP address of the client
        glPopMatrix();


    }

    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /* print the commands */
    glColor3f(1.0, 1.0, 0.0);
    gl_print(-1, 0.8, "accel: w");
    gl_print(-1, 0.7, "slow:  s");
    gl_print(-1, 0.6, "left:  a");
    gl_print(-1, 0.5, "right: d");
    gl_print(-1, 0.4, "brake: x");
    gl_print(-1, 0.3, "reset: p");

    if (sendSS) {
        cli.SendScreenshot();
        sendSS = false;
    }

    cli.DrawScreenshots(std::string());
    SDL_GL_SwapBuffers();
    cn++;
    if (clock() - part > 1000) {
        printf("VIEW fps %d\n", cn);
        part = clock();
        cn = 0;
    }
}



///
bool crtlpressed = false;

void keydown(SDL_Event e) {
    switch (e.key.keysym.sym) {
        case SDLK_w: cli.Command(COMMAND_INCREASE_SPEED);
            break;
        case SDLK_s: cli.Command(COMMAND_DECREASE_SPEED);
            break;
        case SDLK_a: cli.Command(COMMAND_TURN_LEFT);
            break;
        case SDLK_d: cli.Command(COMMAND_TURN_RIGHT);
            break;
        case SDLK_x: cli.Command(COMMAND_BRAKE);
            break;
        case SDLK_p: cli.Command(COMMAND_RESTART);
            break;
        case SDLK_g: sendSS = true;
            break;
        case SDLK_LCTRL: crtlpressed = true;
            break;
    }
}

void mouse_move(SDL_Event e) {
    if (mouse_BLDown) {

        x_0 = e.motion.x - e.motion.xrel;
        y_0 = e.motion.y - e.motion.yrel;
        x_1 = e.motion.x;
        y_1 = e.motion.y;

        if (crtlpressed)
            vieww *= (1 + ((e.motion.yrel > 0) ? 0.01 : -0.01));
        else {
            obs[0] += e.motion.xrel;
            obs[2] += e.motion.yrel;
        }


    }
}
///

int launch_viewer() {
    
}

