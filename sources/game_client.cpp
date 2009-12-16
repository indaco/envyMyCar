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

$Log: game_client.cpp,v $
Revision 1.19  2008/03/12 13:19:22  ganovelli
clock in millisecons

Revision 1.18  2008/03/04 14:55:10  ganovelli
DataExchangeThread split into DataReceiveThread and DataSendThread

Revision 1.17  2008/03/04 14:23:49  ganovelli
 *** empty log message ***

Revision 1.16  2008/02/23 15:21:01  ganovelli
typo..

Revision 1.15  2008/02/22 16:54:43  ganovelli
compiled for linux

Revision 1.14  2008/02/21 13:22:34  ganovelli
QT version. Everything working except server and client runing on the same machine.
Network exceptions not handled, when you stop the client is likely the server will crash too.

Revision 1.13  2008/02/20 13:25:48  ganovelli
DO NOT USE THIS VERSION
INTERMEDIATE version> passing from ptypes to qt
client side working, server side still to be done

Revision 1.12  2008/02/18 10:17:23  ganovelli
added mechanism for knowing who's the local player

Revision 1.11  2007/07/17 10:30:11  ganovelli
added local ip

Revision 1.10  2007/07/17 09:44:59  ganovelli
visualization of other snapshots working

Revision 1.9  2007/07/16 17:12:45  ganovelli
exchange of screenshot data-draft of drawing others screenshots

Revision 1.8  2007/07/04 13:28:30  ganovelli
halfway  version for thumbnails

Revision 1.7  2007/04/10 08:22:28  ganovelli
added sun position

Revision 1.6  2007/04/09 23:08:41  ganovelli
added standalone mode

Revision 1.5  2007/03/29 21:52:44  ganovelli
added builder of circuits.

Revision 1.4  2007/03/27 23:10:29  ganovelli
added holes and tunnels to the Street
added buildings to the Circuit
added server to client transmission of each player state
added BRAKING and BOOSTING to the player state
added sun position

Revision 1.3  2007/03/21 10:34:21  ganovelli
added better steering,

Revision 1.2  2007/03/17 12:26:14  ganovelli
 * pragma replaced by #ifndef directive
 * Player operator= added
 * bug in race_simulation.cpp corrected
 * msvc2005 solutions added

Revision 1.1  2007/03/11 15:10:17  ganovelli
first working draft

Revision 1.2  2007/03/11 15:08:51  ganovelli
 *** empty log message ***

Revision 1.1  2007/03/10 16:43:35  ganovelli
first working draft

 ****************************************************************************/

#include <QtCore/qthread.h>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QTcpSocket>
#include <QtCore/QSemaphore>

#include <GL/glew.h>
#include <GL/glu.h>
#include <time.h>

#include "messages.h"
#include "packaging.h"
#include "process_message.h"

#include "actions.h"
#include "game_client.h"
#include <game_viewer.h>
#include "race_simulation.h"

#include <iostream>

#include "myclient/TestEventHandler.h"

/// the single istance of NvmcClient
NvmcClient cli;

/// The single istance of Race
Race race;
/// The adress of the server
QHostAddress server_address;
/// the message queue for standalone mode
std::vector<std::string> c2sMessages;

///
const int in_state_port = 8082;
///
const int out_commands_port = 8084;
///
const int maxtoken = 4096;

const int out_port = 8086; // tcp port to receive snapshots


void * buffer; /// buffer for texture reads
int w, h; /// stores the viewport size
int tw, th; /// stores the texture size
int lastScreenshot; /// last time the screenshot was taken
GLuint buftex; /// buffer texture index
///

int clockms() {
    float clocks = static_cast<float> (clock()) * 1000.0f;
    return static_cast<int> (clocks / static_cast<float> (CLOCKS_PER_SEC));
}

int NvmcClient::Initialize(char * circuitFile, bool st) {

    standalone_mode = st;

    server_address = QHostAddress::Broadcast;
    /** add a simple circuit to the list of circuits */
    circuits.push_back(Circuit());

    if (circuitFile == NULL) CreateCircularCircuit(circuits[0]);
    else circuits[0].Load(circuitFile);
    /** set the circuit as the circuit of the race */
    race.circuit = &circuits[0];
    race.circuit->sun_position = vcg::Point4f(10000, 10000, 10000, 1.0);

    /** initialize w,h and tw,th to 0 (here no window has been created yet) **/
    w = tw = h = th = 0;
    /** initialize the screenshot of the player view **/
    screenshot.Init(256, 256);

    buftex = -1;

    return 0;
};

///

int ProcessMessage(std::string msg, std::string host) {
    const char* p = msg.c_str();
    int state_time;
    vcg::Point4f & sp = race.circuit->sun_position;
    sscanf(p, "%d %f %f %f %f ", &state_time, &sp[0], &sp[1], &sp[2], &sp[3]);
    race.start_time = state_time;

    int pos = msg.find('~');
    msg.erase(0, pos + 1);
    while (!msg.empty()) {
        ProcessMessagePlayer(msg, host);
        pos = msg.find('~');
        msg.erase(0, pos + 1);
    }
    return 0;
}

// thread for one-to-one tcp communication with the server

class DataReceiveThread : public QThread {
public:

    DataReceiveThread() : QThread(0), stop(false) {
        trig = new QSemaphore(0);
    }

    ~DataReceiveThread() {
        stop = true;
        wait();
        delete trig;
    }

    bool stop;
    QSemaphore * trig;
    QTcpSocket * qts;

    void run() {
        printf("DataReceiveeThread started\n");
        while (!stop) {

            int readed = 0;
            S2CMessage msg;
            if (qts->waitForReadyRead(1000)) {
                /* reading of the snapshot: blocking version..it means that since
                the communcation of a snapshot starts until it is completed this thread is stuck*/
                if (qts->bytesAvailable() > sizeof ( C2SMessage)) {
                    readed += qts->read((char*) & msg, sizeof ( C2SMessage));

                    while (qts->bytesAvailable() < msg.body_length)
                        qts-> waitForReadyRead(10);

                    msg.body = malloc(msg.body_length);
                    readed += qts->read((char*) msg.body, msg.body_length);
                    ProcessMessagePlayer(msg);
                    printf("Screenshot updated\n");
                }
            }
        }
        printf("DataReceiveThread stopped\n");
    }
};

class DataSendThread : public QThread {
public:

    DataSendThread() : QThread(0), stop(false) {
        trigNewScreenShot = new QSemaphore(0);
    }

    ~DataSendThread() {
        stop = true;
        trigNewScreenShot->release();
        wait();
        delete trigNewScreenShot;
    }

    bool stop;
    QSemaphore *trigNewScreenShot;
    QTcpSocket * qts;

    void run() {
        printf("DataSendThread started\n");
        while (!stop) {

            int readed = 0;
            S2CMessage msg;

            trigNewScreenShot->acquire();
            if (!stop) {
                cli.mutex_on_dataToSend.lock();
                if (!cli.dataToSend.empty()) {
                    const C2SMessage & mess = cli.dataToSend.back();
                    qts->write((char*) & mess, sizeof ( C2SMessage));
                    qts->write((char*) mess.body, mess.body_length);
                    qts->flush();
                    cli.dataToSend.pop_back();
                }
                cli.mutex_on_dataToSend.unlock();
            }
        }
        printf("DataSendThread stopped\n");

    }
};

DataReceiveThread drt;
DataSendThread dst;

struct DataExchangeThread : public QThread {

    DataExchangeThread() : QThread(0) {
        trig = new QSemaphore(0);
    }

    ~DataExchangeThread() {
        delete trig;
    }

    QSemaphore * trig;

    void run() {
        trig->acquire();
        QTcpSocket * qts = new QTcpSocket(0);
        bool ab = qts->open(QIODevice::ReadWrite);
        qts->connectToHost(server_address, out_port, QIODevice::ReadWrite);
        qts->waitForConnected(-1);
        cli.local_ip = qts->localAddress();

        drt.qts = qts;
        drt.start();

        dst.qts = qts;
        dst.start();


    }
};

DataExchangeThread dt;


//class Waiter:public pt::thread{ public :Waiter():pt::thread(true){} void execute(){relax(5000);}};

///

class MessagesReceiverThread : public QThread {
public:
    ///

    MessagesReceiverThread() : QThread(0), stop(false) {
    }

    ~MessagesReceiverThread() {
        stop = true;
        wait();
    }
    bool stop;
    ///

    void run() {
        int part = 0, cl = 0;
        QUdpSocket qs;

        bool bound = qs.bind(in_state_port);
        assert(bound);
        bool quit = false;

        printf("MessagesReceiverThread started\n");

        do {
            ++cl;
            char data[maxtoken];
 while (!qs.waitForReadyRead() && !stop);

            if (!stop) {
                QHostAddress addr;
                qint64 nr = qs.readDatagram(data, maxtoken, &addr);
                data[nr] = '\0';
                std::string msg(data);
                if (server_address == QHostAddress::Broadcast) {
                    server_address = addr;
                    dt.trig->release(1);
                }
                if (!stop)
                    ProcessMessage(msg, std::string(""));

                if (clockms() - part > 1000) {
                    printf("RECEIV fps %d\n", cl);
                    cl = 0;
                    part = clockms();
                }
            }
        } while (!stop);
        printf("MessagesReceiverThread stopped\n");

    }

};


///

class MessagesSenderThread : public QThread {
public:
    ///

    MessagesSenderThread() : QThread(0), stop(false) {
        trig = new QSemaphore(0);
    }

    ~MessagesSenderThread() {
        stop = true;
        trig->release(1);
        wait();
        delete trig;
    }

    ///
    bool stop;
    QSemaphore * trig;
    ///

    void run() {
        printf("MessagesSenderThread started\n");

        QUdpSocket qs;
        std::string msg_str;
        do {
            trig->acquire();
            if (!stop) {
                if (cli.standalone_mode)
                    ProcessMessageServer(cli.messagesToSend.back(), std::string("localhost"));
                else {
                    //msg.send(cli.messagesToSend.back());
                    int size = cli.messagesToSend.back().length();
                    qs.writeDatagram(cli.messagesToSend.back().c_str(), size, server_address, out_commands_port);
                }
            }
        } while (!stop);
        printf("MessagesSenderThread stopped\n");

    }
};

class RaceSimulationThread : public QThread {
public:

    RaceSimulationThread() : QThread(0) {
    }

    void run() {
        gTime = clockms();
        int part = gTime, cl = 0;
        Actions copyof_actionsToDo;
        ActionsIterator ai;
        /* first draft */
        while (true) {
            ++cl;
            msleep(20);

            mutex_on_actionsToDo.lock();
            copyof_actionsToDo = actionsToDo;
            actionsToDo.clear();
            mutex_on_actionsToDo.unlock();

            for (ai = copyof_actionsToDo.begin(); ai != copyof_actionsToDo.end(); ++ai)
                ProcessAction(*ai);

            Race::PlayersIterator pi;

            race.mutex_on_players.lock();
            Race::PlayerContainer players = race.players;
            race.mutex_on_players.unlock();

            for (pi = players.begin(); pi != players.end(); ++pi)
                Update((clockms() - gTime), *pi);

            race.mutex_on_players.lock();
            race.players = players;
            race.mutex_on_players.unlock();


            if (clockms() - part > 1000) {
                printf("SIMU fps %d %d\n", cl, clockms());
                cl = 0;
                part = clockms();
            }

            copyof_actionsToDo.clear();
            gTime = clockms();
        }
    }

};
MessagesSenderThread s;


///

int NvmcClient::Start() {

    ///* start the thread handling ipmessages reception */
    MessagesReceiverThread t;
    if (!standalone_mode) {
        t.start();
        dt.start();
    } else
        local_ip = QHostAddress(QString("localhost"));

    ///* start the thread handling ipmessages sending */
    s.start();

    ///* start the local simulation */
    RaceSimulationThread rs;
    if (standalone_mode) rs.start();

    /* game main loop */
    //launch_viewer();
    TheApp.launchViewer();
    return 0;

};

///

int NvmcClient::Terminate() {
    return 0;
};

///

int NvmcClient::Command(C2SHeaderValue value) {

    // mutex_on_messagesToSend.enter();
    messagesToSend.push_back(Pack(C2SMessage(value)));
    // mutex_on_messagesToSend.leave();

    s.trig->release(1);

    // mutex_on_actionsToDo.enter();
    // actionsToDo.push_back(Action(std::string("nb-ganovelli.isti.cnr.it"),value));
    // mutex_on_actionsToDo.leave();
    return 0;
}

///

void NvmcClient::UpdatePlayers() {
    race.mutex_on_players.lock();
    players = race.players;
    race.mutex_on_players.unlock();

    // now update the reference to the local player
    Race::PlayersIterator hh;
    local_player = players.end();
    for (hh = players.begin(); hh != players.end(); ++hh) {
        if ((*hh).ip_address == cli.local_ip) {
            local_player = hh;
            break;
        }
    }
}

void SaveFloat(char * nf, int x, int y, void * pix) {
    FILE* f = fopen(nf, "wb");
    fwrite(pix, x * y * 3, 1, f);
    fclose(f);
}

void NvmcClient::SendScreenshot() {
    if (standalone_mode) return;
    // read the back buffer, resample and queue it to be sent to the server
    //tmp
    float sizeB = 0.6f;
    GLint vp[4];

    lastScreenshot = clockms();
    glGetIntegerv(GL_VIEWPORT, vp);
    if ((vp[2] != w) || (vp[3] != h)) {
        w = vp[2];
        h = vp[3];
        int i = 0;
        while ((1 << i) < vp[2])++i;
        tw = (1 << i);
        i = 0;
        while ((1 << i) < vp[3])++i;
        th = (1 << i);
        if (buffer) delete buffer;
        buffer = new char[tw * th * 3];
    }

    assert(glGetError() == 0);
    if (buftex == -1)
        glGenTextures(1, &buftex);

    glBindTexture(GL_TEXTURE_2D, buftex);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tw, th, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, tw, th);
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, tw, th, GL_RGB, GL_UNSIGNED_BYTE, buffer);

    // get the level corresponding to 256
    int twi = tw, thi = th, i = 0;
    while ((thi > screenshot.h) && (twi > screenshot.w)) {
        thi = thi >> 1;
        twi = twi >> 1;
        ++i;
    }

    glGetTexImage(GL_TEXTURE_2D, i, GL_RGB, GL_UNSIGNED_BYTE, screenshot.pixels);
    //SaveFloat("buf1.raw",twi,thi,buffer1);
    assert(glGetError() == 0);

    // prepare the data to be sent
    mutex_on_dataToSend.lock();
    dataToSend.push_back(C2SMessage(DATA_SNAPSHOT));
    dataToSend.back().body = screenshot.pixels;
    dataToSend.back().body_length = twi * thi * 3;
    mutex_on_dataToSend.unlock();

    dst.trigNewScreenShot->release();
}

void NvmcClient::DrawScreenshots(std::string big_ip_address) {
    if (standalone_mode) return;
    float size = 0.2f, sizeB = 0.6f;
    Race::PlayersIterator pi, big;
    float cx = -1.0f, cy = -0.9f;
    int i;


    if (!race.players.empty()) {

        for (pi = race.players.begin(); pi != race.players.end(); ++pi) {


            if (!(*pi).screenshot.textureIDAssigned) {
                glGenTextures(1, & (*pi).screenshot.textureID);

                glBindTexture(GL_TEXTURE_2D, (*pi).screenshot.textureID);
                glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

                (*pi).screenshot.textureIDAssigned = true;
            }

            if (!(*pi).screenshot.textureUpToDate) {
                glBindTexture(GL_TEXTURE_2D, (*pi).screenshot.textureID);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, (*pi).screenshot.pixels);
                (*pi).screenshot.textureUpToDate = true;
            }
        }

        glPushAttrib(0xfffffff);
        race.mutex_on_players.lock();
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        assert(glGetError() == 0);

        big = race.players.begin();
        for (pi = race.players.begin(); pi != race.players.end(); ++pi)
            if ((*pi).ip_address != local_ip) {
                big = pi;
                break;
            }

        for (pi = race.players.begin(); pi != race.players.end(); ++pi) {
            if ((*pi).ip_address == QHostAddress(QString(big_ip_address.c_str())))
                big = pi;
        }

        // draw the biggest in the lower left 20% x 20% of the screen
        glBindTexture(GL_TEXTURE_2D, (*big).screenshot.textureID);

        glPushMatrix();
        glLoadIdentity();
        glTranslatef(-1.0f, -0.99f, 0.0f);
        glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(0.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(sizeB, 0.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(sizeB, sizeB);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(0, sizeB);
        glEnd();
        glPopMatrix();

        i = 1;
        for (pi = race.players.begin(); pi != race.players.end(); ++pi, ++i)
            if ((pi != big) && ((*pi).ip_address != local_ip)) {
                glBindTexture(GL_TEXTURE_2D, (*pi).screenshot.textureID);
                glPushMatrix();
                glLoadIdentity();
                glTranslatef(-1.0f + i*size, -0.99f, 0.0f);
                glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 0.0f);
                glVertex2f(0.0f, 0.0f);
                glTexCoord2f(1.0f, 0.0f);
                glVertex2f(size, 0.0f);
                glTexCoord2f(1.0f, 1.0f);
                glVertex2f(size, size);
                glTexCoord2f(0.0f, 1.0f);
                glVertex2f(0, size);
                glEnd();
                glPopMatrix();
            }

        race.mutex_on_players.unlock();
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glPopAttrib();
    }
}
