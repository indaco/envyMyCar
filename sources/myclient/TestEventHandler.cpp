
#include "../game_client.h"
#include "../game_viewer.h"
#include "../race.h"

#include "TestEventHandler.h"
#include "../utilities/myfunctions.h"
#include "mycircuit.h"


#include <new>
using std::bad_alloc;


#include "../utilities/LogFile.h"
#include "../utilities/tga.h"
#include "buildings.h"


/* file di log */
LogFile *m_log = NULL;
MyCircuit mycircuit;

GLuint macchina = 0;
MyCar *mycar = NULL;


#define cielo_tex "../../../../nvmc/media/textures/cielo.bmp"
GLuint cielo_bind = 3;

#define buildings_tex "../../../../nvmc/media/textures/building.bmp"
GLuint buildings = 0;
GLuint building_bind = 11;


/** Client  */
extern NvmcClient cli;

/* Message IDs per i controlli del client */
MSGID CTestEventHandler::MSGID_StartRace = CMessageHandler::GetNextMSGID();
MSGID CTestEventHandler::MSGID_Slow = CMessageHandler::GetNextMSGID();
MSGID CTestEventHandler::MSGID_TurnLeft = CMessageHandler::GetNextMSGID();
MSGID CTestEventHandler::MSGID_TurnRight = CMessageHandler::GetNextMSGID();
MSGID CTestEventHandler::MSGID_Brake = CMessageHandler::GetNextMSGID();
MSGID CTestEventHandler::MSGID_ResetRace = CMessageHandler::GetNextMSGID();


vcg::Point3f position = vcg::Point3f(0, 0, 0);
vcg::Point3f delta = vcg::Point3f(0, 0, 0);
int ZOOM = 60;
int UPDOWN = 5;


/* valori per il lighting */
GLfloat mat_lig[32];
/* osservatore */
vcg::Point3f obs(0, 400, 0);

CTestEventHandler::CTestEventHandler(const string &str, int width, int height) {
    if (width <= 0 || height <= 0)
        throw CTestEventHandlerException(); // termina la funzione se le dimensioni della finestra sono pari o minori di zero

    iWindowWidth = width;
    iWindowHeight = height;
    sTitle.assign(str);
    m_pDisplaySurface = NULL;
    sendSS = false;
    vieww = 0.5;
    videoFlags = 0;


    setPov(vcg::Point3f(0, 0, 0));

    try {
        m_log = new LogFile();
        m_log->initLog("log.html", "envyMyCar");
        if (m_log->isEnabled()) cout << "\n*** log su file html abilitato ***\n" << endl;
        m_log->writeLog(LOG_PLAINTEXT, "*** Application LOG Started ***");
    } catch (bad_alloc &memoryAllocationException) {
        delete m_log;
        cerr << "Exception occurred: " << memoryAllocationException.what() << endl;
    }


    try {
        mycar = new MyCar("../../../../nvmc/media/models/smart.ply");
        m_log->writeLog(LOG_SUCCESS, "Initializing MyCar --> OK");
    } catch (bad_alloc &maeCar) {
        delete mycar;
        m_log->writeLog(LOG_FAILURE, "Exception occurred initializing MyCar (please read the console log)");
        cerr << "Exception occurred: " << maeCar.what() << endl;
    }


}

/*-------------------------------------------------------------
 * destructor
 * ------------------------------------------------------------*/
CTestEventHandler::~CTestEventHandler() {
    OnExit();
}

bool CTestEventHandler::OnInit(int argc, char* argv[]) {
    // inizializzo il parent
    CEventHandler::OnInit(argc, argv);

    if ((argc <= 1) || (argc > 3)) {
        cerr << "NVMC client.exe STANDALONE [CIRCUIT] \nSTANDALONE: 1: standalone (without launching server), 0: LAN \n" << endl;
        cerr << "If no circuit is specified, a simple one is generated \n" << endl;
        exit(0);
    }

    glutInit(&argc, argv);
    bool stl = (atoi(argv[1]) == 0) ? 0 : 1;
    if (argc == 0) cli.Initialize((char*) NULL, stl);
    else cli.Initialize(argv[2], stl);

    m_log->writeLog(LOG_SUCCESS, "OnInit method called in Main Application");
    m_log->writeLog(LOG_SUCCESS, "Starting client...");


    cli.Start();
    cli.Terminate();

    return (true);
}

int CTestEventHandler::launchViewer() {
    /* the flags to pass to SDL_SetVideoMode */
    videoFlags = SDL_OPENGL; /* Enable OpenGL in SDL */
    videoFlags |= SDL_GL_DOUBLEBUFFER; /* Enable double buffering */
    videoFlags |= SDL_HWPALETTE; /* Store the palette in hardware */
    videoFlags |= SDL_RESIZABLE; /* Enable window resizing */

    /* this holds some info about our display */
    const SDL_VideoInfo* videoInfo;
    videoInfo = SDL_GetVideoInfo();
    if (!videoInfo) {
        cerr << "Video query failed:" << SDL_GetError() << endl;
        exit(1);
    }
    /* This checks to see if surfaces can be stored in memory */
    videoInfo->hw_available ? videoFlags |= SDL_HWSURFACE : videoFlags |= SDL_SWSURFACE;
    /* This checks if hardware blits can be done */
    if (videoInfo->blit_hw) videoFlags |= SDL_HWACCEL;

    logVideoInfo(videoInfo, m_log);


    /* Sets up OpenGL double buffering */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    glClearAccum(0.0, 0.0, 0.0, 1.0);
    glClear(GL_ACCUM_BUFFER_BIT);

    SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, 16);


    /* get a SDL surface */
    m_pDisplaySurface = SDL_SetVideoMode(getWidth(), getHeight(), 16, videoFlags);
    SDL_WM_SetCaption(sTitle.c_str(), sTitle.c_str());

    setBMin(race.circuit->bbox.min);
    setBMax(race.circuit->bbox.max);

    initGL();
    reshapeFunction(getWidth(), getHeight());

    return 0;
}

void CTestEventHandler::OnIdle() {
    testingGL();
}

void CTestEventHandler::OnExit() {

    iWindowWidth = 0;
    iWindowHeight = 0;
    videoFlags = 0;
    sendSS = false;
    vieww = 0;
    m_log->writeLog(LOG_PLAINTEXT, "*** Closing application... ***");
    m_log->writeLog(LOG_SUCCESS, "deleting pointers to the car and circuit --> OK");
    m_log->writeLog(LOG_SUCCESS, "deleting SDL_Surface --> OK");
    m_log->writeLog(LOG_SUCCESS, "closing SDL window and log file --> OK");
    m_log->writeLog(LOG_PLAINTEXT, "*** CLOSED. ***");
    
    //mycircuit.release();

    
    delete m_log;
    delete mycar;
    
    SDL_FreeSurface(m_pDisplaySurface);
    m_pDisplaySurface = 0;
    m_log = 0;
    mycar = 0;
    SDL_Quit();
}

bool CTestEventHandler::initGL() {
    glPolygonMode(GL_FRONT, GL_FILL); // rasterizza solo i contorni dei poligon;
    glEnable(GL_DEPTH_TEST);

    m_log->writeLog(LOG_PLAINTEXT, "*** Initializing Textures... ***");

    /**********************************************************************
     * Carico le texture degli elementi della scena e la mesh della macchina  *
     **********************************************************************/
    mycircuit.road.loadTexture("../../../../nvmc/media/textures/street.bmp");
    mycircuit.terrain.loadTexture("../../../../nvmc/media/textures/grass.bmp");

      
    GLuint tex3 = 0;
    tex3 = loadBMPTexture(buildings_tex, building_bind, GL_TRUE);

    GLuint tex4 = loadBMPTexture(cielo_tex, cielo_bind, GL_TRUE);
    
    (mycar->loadCar()) ? m_log->writeLog(LOG_SUCCESS, "Loading car mesh --> OK") : m_log->writeLog(LOG_FAILURE, "Loading car mesh --> FAILED!");

    (mycircuit.trees.loadImage("../../../../nvmc/media/textures/albero.tga")) ? m_log->writeLog(LOG_SUCCESS, "Loading trees tga file --> OK") : m_log->writeLog(LOG_FAILURE, "Loading trees tga file --> FAILED!");

    mycircuit.skybox.initialize(400.0f, 100.0f, 400.0f);
    (mycircuit.skybox.loadTextures("../../../../nvmc/media/skybox/land1/Top.bmp",
            "../../../../nvmc/media/skybox/land1/Bottom.bmp",
            "../../../../nvmc/media/skybox/land1/Front.bmp",
            "../../../../nvmc/media/skybox/land1/Back.bmp",
            "../../../../nvmc/media/skybox/land1/Left.bmp",
            "../../../../nvmc/media/skybox/land1/Right.bmp")) ? m_log->writeLog(LOG_SUCCESS, "Loading skybox textures --> OK") : m_log->writeLog(LOG_FAILURE, "Loading skybox textures --> FAILED");

    m_log->writeLog(LOG_PLAINTEXT, "Initializing Textures --> DONE");

    //mycircuit.buildings.loadTexture("../../../../nvmc/media/textures/building.bmp");

    /* Inizializzo le luci della scena*/
    initLights();

    /**************************************************
     * Genero le display list per gli elementi del circuito *
     **************************************************/
    m_log->writeLog(LOG_PLAINTEXT, "*** Generating Display Lists... ***");
    buildings = mycircuit.generateBuildings(building_bind);
    macchina = mycar->generateCar();
    m_log->writeLog(LOG_SUCCESS, "Generating Display Lists --> DONE ");

    return (true);
}

// INIZIALIZZA LE LUCI

void CTestEventHandler::initLights() {
    m_log->writeLog(LOG_SUCCESS, "Lighting initialized successfull");
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1); //faro 1
    glEnable(GL_LIGHT2); //faro2
    glEnable(GL_NORMALIZE);

    int i;
    //MATERIALE
    for (i = 0; i < 4; ++i) mat_lig[i] = 0.0; //EMISSIVA
    for (i = 4; i < 8; ++i) mat_lig[i] = 0.4; //AMBIENTE
    for (i = 8; i < 12; ++i) mat_lig[i] = 0.6; //DIFFUSA
    for (i = 12; i < 16; ++i) mat_lig[i] = 0.4; //SPECULARE

    for (i = 16; i < 20; ++i) mat_lig[i] = 1.0; //EMISSIVA
    for (i = 20; i < 24; ++i) mat_lig[i] = 0.4; //AMBIENTE
    for (i = 24; i < 28; ++i) mat_lig[i] = 0.6; //DIFFUSA

    for (i = 28; i < 32; ++i) mat_lig[i] = 0.4; //SPECULARE
}



void CTestEventHandler::setLights() {

    /* i parametri del materiale */
    glMaterialfv(GL_FRONT, GL_EMISSION, &mat_lig[0]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, &mat_lig[4]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &mat_lig[8]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, &mat_lig[12]);
    glMaterialf(GL_FRONT, GL_SHININESS, 100);

    /* i parametri della luce */
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, &mat_lig[16]);

    //ligth0
    glLightfv(GL_LIGHT0, GL_AMBIENT, &mat_lig[20]);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, &mat_lig[24]);
    glLightfv(GL_LIGHT0, GL_SPECULAR, &mat_lig[28]);

    //faro 1
    glLightfv(GL_LIGHT1, GL_AMBIENT, &mat_lig[20]);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, &mat_lig[24]);
    glLightfv(GL_LIGHT1, GL_SPECULAR, &mat_lig[28]);

    glLighti(GL_LIGHT1, GL_SPOT_EXPONENT, 110);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 50);

    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.01f);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0f);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.0);

    //faro2
    glLightfv(GL_LIGHT2, GL_AMBIENT, &mat_lig[20]);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, &mat_lig[24]);
    glLightfv(GL_LIGHT2, GL_SPECULAR, &mat_lig[28]);

    glLighti(GL_LIGHT2, GL_SPOT_EXPONENT, 110);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 50);

    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.01f);
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.0f);
    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.0);
}


void CTestEventHandler::glPrint(float x, float y, const char *str) {
    glRasterPos2f(x, y);
    int len = (int) strlen(str);

    for (int i = 0; i < len; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
}


void CTestEventHandler::reshapeFunction(int w, int h) {
    GLfloat ratio;

    if (h == 0) h = 1;

    ratio = static_cast<float> (w) / h;
    //cout << "Ratio: " << setprecision(2) << fixed << ratio << endl;

    glViewport(0, 0, (GLsizei) w, (GLsizei) h); // imposta la viewport.

    /* cambia la matrice di proiezione ed imposta il volume di vista. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f, ratio, 0.1f, 100.0f); // Imposta la prospettiva 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // resetto la vista

}


void CTestEventHandler::drawGLScene(bool dyn_cm) {
    static int cn = 0;
    static int part = 0;

    setLights();
    /* imposta l'intero color buffer al valore impostate con glClearColor (nero per default) */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    SDL_Delay(40);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float sidex, sidez;
    sidex = getBMax()[0] - getBMin()[0];
    sidez = getBMax()[2] - getBMin()[2];

    cli.UpdatePlayers();

    Race::PlayersIterator fpi;
    position = vcg::Point3f(0, 0, 0);
    delta = vcg::Point3f(0, 0, 0);
    vcg::Point3f delta2, pov2;
    Frame myf;

    if (cli.players.size() > 0) {
        fpi = cli.players.begin();
        myf = (*fpi).car.frame;
        position = myf.GetRow3(3);
        delta = myf.GetRow3(2)*15 + myf.GetRow3(1) * UPDOWN;
    }

    // Punto di vista
    setPov(position + delta);

    gluPerspective(ZOOM, static_cast<float> (getWidth()) / getHeight(), 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(getPov().X(), getPov().Y(), getPov().Z(), position.X(), position.Y(), position.Z(), 0, 1, 0);

    // Skybox
    mycircuit.skybox.render(0.0f, 0.0f, 0.0f, position);

    // disegno il terreno
    mycircuit.terrain.render( getBMin(), getBMax());

    glPushMatrix();
    glScalef(getBMax()[0] - getBMin()[0], getBMax()[1] - getBMin()[1], getBMax()[2] - getBMin()[2]);
    drawAxis();
    glPopMatrix();

     // disegno la strada
    mycircuit.road.render(race.circuit->street.path);

    
    // disegno i palazzi
    glCallList(buildings);
    //mycircuit.buildings.render();

    // disegno gli albei
    mycircuit.trees.render(getPov());


    // disegno i giocatori
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

        /* Disegno la macchina */
        glCallList(macchina);

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
        glPrint(100.0, 100.0, ((*pi).ip_address.toString()).toAscii().data()); // write the IP address of the client
        glPopMatrix();

    }

    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // print the commands 
    glColor3f(1.0, 0.0, 0.0);
    glPrint(-1, 0.8, "accel: w");
    glPrint(-1, 0.7, "slow:  s");
    glPrint(-1, 0.6, "left:  a");
    glPrint(-1, 0.5, "right: d");
    glPrint(-1, 0.4, "brake: x");
    glPrint(-1, 0.3, "reset: p");


    if (sendSS) {
        cli.SendScreenshot();
        sendSS = false;
    }

    cli.DrawScreenshots(std::string());
    SDL_GL_SwapBuffers();
    cn++;
    if (clock() - part > 1000) {
        //printf("VIEW fps %d\n", cn);
        part = clock();
        cn = 0;
    };
}

void CTestEventHandler::drawAxis() {

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

void CTestEventHandler::testingGL() {

    reshapeFunction(getWidth(), getHeight());
    drawGLScene(false);
}

void CTestEventHandler::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
    switch (sym) {
        case SDLK_w: SendMessage(MSGID_StartRace);
            break;
        case SDLK_s: SendMessage(MSGID_Slow);
            break;
        case SDLK_a: SendMessage(MSGID_TurnLeft);
            break;
        case SDLK_d: SendMessage(MSGID_TurnRight);
            break;
        case SDLK_x: SendMessage(MSGID_Brake);
            break;
        case SDLK_p: SendMessage(MSGID_ResetRace);
            break;
        case SDLK_ESCAPE:
            break;
        default:
            break;
    }
}

bool CTestEventHandler::OnMessage(MSGID MsgID, MSGPARM Parm1, MSGPARM Parm2, MSGPARM Parm3, MSGPARM Parm4) {
    if (MsgID == MSGID_StartRace) {
        cli.Command(COMMAND_INCREASE_SPEED);
        return (true);
    } else if (MsgID == MSGID_Slow) {
        cli.Command(COMMAND_DECREASE_SPEED);
        return (true);
    } else if (MsgID == MSGID_TurnLeft) {
        cli.Command(COMMAND_TURN_LEFT);
        return (true);
    } else if (MsgID == MSGID_TurnRight) {
        cli.Command(COMMAND_TURN_RIGHT);
        return true;
    } else if (MsgID == MSGID_Brake) {
        cli.Command(COMMAND_BRAKE);
        return true;
    } else if (MsgID == MSGID_ResetRace) {
        cli.Command(COMMAND_RESTART);
        return true;
    } else return (CEventHandler::OnMessage(MsgID, Parm1, Parm2, Parm3, Parm4));
}


/*----------------------------------------------------
 * L'applicazione principale
----------------------------------------------------*/
CTestEventHandler TheApp("envyMyCar", 600, 480);
/*--------------------------------------------------*/