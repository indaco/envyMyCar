#ifndef __TESTEVENTHANDLER_H__
#define __TESTEVENTHANDLER_H__

#include "../core/EventHandler.h"
#include "CTestEventHandlerException.h"

#include <iostream>
#include <ios>
using std::cout;
using std::cerr;
using std::endl;
using std::fixed;
using std::boolalpha;

#include <iomanip>
using std::setprecision;

#include <string>
using std::string;

#include <cstring>
using std::strcat;

#include <math.h>
#include <time.h>
#include <vcg/space/point3.h>

#include <vector>

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <algorithm>


#include "mycar.h"

/*
 * class: CTestEventHandler
 *
 *  La classe principale dell'applicazione
 */

class CTestEventHandler : public CEventHandler {
public:

    /*-------------------------------------------------------------
     * constructor: CTestEventHandler
     *
     * Lancia una eccezione ed esce dall'applicazione
     *
     *  se si cerca di impostare una o entrame le dimensioni della finestra a  valori minori o pari a 0
     *
     * Arguments: 
     *
     *          - title (string)
     *
     *          - width (int)
     *
     *          - height (int)
     *
     * ------------------------------------------------------------*/
    CTestEventHandler(const std::string &str, int width, int height);



    /* ----------------------------------------------
     * destructor
     * ----------------------------------------------*/
    virtual ~CTestEventHandler();



    /*-------------------------------------------------------------
     * method: OnInit
     *
     * Richiama il costruttore del padre passandogli gli argomenti specificati da linea di comando (circuito e modalita' di gioco). Inizializza glut ed avvia il client.
     *
     *  Arguments:
     *          
     *          - int: argc
     *
     *          - char*: argv[]
     *
     * Return value:
     *          
     *          - bool
     *     
     * ------------------------------------------------------------*/
    bool OnInit(int argc, char* argv[]);



    /*-------------------------------------------------------------
     * method: OnIdle 
     *
     * funzione da richiamare nei cicli di idle
     *
     * Arguments: 
     * 
     *          - none
     *
     * Return Value: 
     *  
     *          - void
     * ------------------------------------------------------------*/
    void OnIdle();

    /*-------------------------------------------------------------
     * method: OnExit 
     *
     * libera la memoria occupata dalla SDL_Surface e chiama SDL_Quit()
     *
     * Arguments: 
     * 
     *          - none
     *
     * Return Value: 
     * 
     *          - void
     *
     * ------------------------------------------------------------*/
    void OnExit();


    /*-------------------------------------------------------------
     * method: OnKeyDown 
     *
     * key press handler
     *
     * Arguments: 
     *
     *          - sym (SDLSym)
     *
     *          - mod (SDLMod)
     *
     *          - unicode (Uint16)
     *
     * Return Value: 
     * 
     *          - void
     *
     * ------------------------------------------------------------*/
    void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);


    /*-------------------------------------------------------------
     * method: OnMessage
     *
     * gestore dei messaggi che gli oggetti si scambiano
     *
     * Arguments: 
     *
     *          - MsgID (MSGID)
     *
     *          - Parm1, Parm2, Parm3 (MSGPARAM) opzionali
     *
     * Return Value: 
     * 
     *          - void
     *
     * ------------------------------------------------------------*/
    bool OnMessage(MSGID MsgID, MSGPARM Parm1, MSGPARM Parm2, MSGPARM Parm3, MSGPARM Parm4);

    /*-------------------------------------------------------------
     * method: testingGL 
     *
     * Uso questa funzione come test generale dell'applicazione
     *
     * Arguments: 
     *
     *          - none
     * 
     * Return Value: 
     *
     *          - void
     *
     * ------------------------------------------------------------*/
    void testingGL();


    /*--------------------------------------------------------------
     * method: initGL 
     * 
     * carica le texture degli elementi presenti sulla scena, genera le display list corrispondenti ed inizializza l'illuminazione
     *
     * Arguments:
     *
     *          - none
     *
     * Return Value: 
     * 
     *          - bool
     * -------------------------------------------------------------*/
    bool initGL();



    /*--------------------------------------------------------------
     * method: reshapeFunction
     * 
     * si occupa di disegnare la finestra
     *
     * Arguments:
     *
     *          - w: int
     * 
     *          - h: int
     *
     * Return Value: 
     * 
     *          - void
     * -------------------------------------------------------------*/
    void reshapeFunction(int w, int h);



    /*--------------------------------------------------------------
     * method: drawGLScene
     *
     * disegna la scena GL
     *
     * Arguments: 
     * 
     *          - none
     *
     * Return Value: 
     *
     *          - void
     * ------------------------------------------------------------*/
    void drawGLScene(bool dyn_cm);




    /*--------------------------------------------------------------
     * method: initLights
     *
     * inizializza le luci della  scena
     *
     * Arguments: 
     * 
     *          - none
     *
     * Return Value: 
     * 
     *          - void
     * -------------------------------------------------------------*/
    void initLights();




    /*--------------------------------------------------------------
     * method: setLights
     *
     * impostazioni dell'illuminazione
     *
     * Arguments: 
     * 
     *          - none
     *
     * Return Value: 
     * 
     *          - void
     * -------------------------------------------------------------*/
    void setLights();




    /*-------------------------------------------------------------
     * method: launchViever
     *
     *  Il loop principale. 
     * 
     * Imposta i flag che serviranno a creare la finestra SDL e gli attributi per il supporto ad OpenGL, 
     * oltre che ad impostare i punti di minimo e massimo del circuito.
     *
     *
     *  Arguments:
     *          
     *          - none
     *
     *  Return value:
     *      
     *          - int: 0 se tutto è andato bene
     *
     *  Nota:
     *      
     *      Questa funzione va richiamata in  cli.Start
     * ------------------------------------------------------------*/
    int launchViewer();




    /*--------------------------------------------------------------
     * method: glPrint 
     * 
     * Scrive la sequenza una sequenza di caratteri sulla finestra 
     *  principale alla posizione specificata dai parametri
     *
     * Arguments:
     *
     *          - float: x 
     *
     *          - float: y
     *
     *          - char*: str
     *
     * Return Value: 
     *      
     *          - void
     * -------------------------------------------------------------*/
    void glPrint(float x, float y, const char *str);



    /*-------------------------------------------------------------
     * method: drawAxis 
     * 
     * Disegna il sistema di riferimento
     *
     * Arguments: 
     *      
     *          - none
     *
     * Return Value: 
     * 
     *          - void
     * ------------------------------------------------------------*/
    void drawAxis();



    /* riferimento ai flag di inizializzazione di SDL */
    int videoFlags;

    /** I controlli del client **/
    static MSGID MSGID_StartRace; //accellerazione ed inizio gioco
    static MSGID MSGID_Slow; //decellerazione
    static MSGID MSGID_TurnLeft;
    static MSGID MSGID_TurnRight;
    static MSGID MSGID_Brake;
    static MSGID MSGID_ResetRace;

    /* method: getWidth */
    inline int getWidth() {
        return iWindowWidth;
    }

    /* method: getHeight */
    inline int getHeight() {
        return iWindowHeight;
    }

    /* method: setBMin */
    inline void setBMin(vcg::Point3f min) {
        bmin = min;
    }

    /* method: setBMax */
    inline void setBMax(vcg::Point3f max) {
        bmax = max;
    }

    /* method: getBMin */
    inline vcg::Point3f getBMin() {
        return bmin;
    }

    /* method: getBMax */
    inline vcg::Point3f getBMax() {
        return bmax;
    }

    /* method: setPov */
    inline void setPov(vcg::Point3f p) {
        pov = p;
    }

    /* method: getPov */
    inline vcg::Point3f getPov() {
        return pov;
    }


private:
    //main display surface
    SDL_Surface* m_pDisplaySurface;
    
    int iWindowWidth;
    int iWindowHeight;
    std::string sTitle;

    bool sendSS;
    float vieww;

    vcg::Point3f bmin;
    vcg::Point3f bmax;
    vcg::Point3f pov;

};

#endif //#ifndef __TESTEVENTHANDLER_H__
