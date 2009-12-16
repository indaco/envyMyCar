
#ifndef _VCG_CLIENTITEMS_H
#define	_VCG_CLIENTITEMS_H

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <math.h>
#include <time.h>
#include <vcg/space/point3.h>
#include <vector>
#include <GL/glut.h>
#include <GL/glu.h>

#include "../game_client.h"
#include "game_viewer.h"
#include "race.h"

#include "../utilities/LogFile.h"

#include "skybox.h"
#include "road.h"
#include "terrain.h"
#include "tree.h"
#include "buildings.h"

/*
 * class: MyCircuit
 *
 * Questa classe gestisce tutti gli elementi costituenti il circuto (strada, terreno, skybox, alberi...). Ogni elemento e' in relazione
 * di aggregazione con la classe MyCircuit
 *
 */

class MyCircuit {
public:

    MyCircuit();

    MyCircuit(const MyCircuit& orig) {
    };

    virtual ~MyCircuit();


    /***********************************************  
     *                  BUILDINGS SECTION                       *
     ***********************************************/
    void drawBuildings(GLuint building_bind);
    GLuint generateBuildings(GLuint building_bind);
    
    void release();

    Skybox skybox;
    Terrain terrain;
    Road road;
    Tree trees;
    //Buildings buildings;
private:
    
};


#endif	/* _VCG_CLIENTITEMS_H */

