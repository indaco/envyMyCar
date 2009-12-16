#ifndef _BUILDINGS_H
#define	_BUILDINGS_H


#include <math.h>
#include <time.h>
#include <vcg/space/point3.h>
#include <vector>
#include <GL/glew.h>
#include <GL/glut.h>
#include "../utilities/myfunctions.h"

#include "../game_client.h"
#include "../game_viewer.h"
#include "../race.h"

/* ---------------------------------------------
 *  class: Buildings
 *
 *  Disegna i palazzi come quad di altezza ricavata 
 *  durante il loop con l'iteratore.
 * ---------------------------------------------*/
class Buildings {
public:
    /* constructor: Buildings */
    Buildings();
    Buildings(const Buildings& orig);
    virtual ~Buildings();

    /* method: loadTexture */
    bool loadTexture(char *filename);
    void drawBuildings();
    GLuint generateBuildings(GLuint building_bind);
    
    void build_palace(vector<Vertex> &footprint, vector<vcg::Point3f> *palace, float height);
    
    /* method: render */
    void render();
    
    /* method: release */
    void release();

private:

    GLuint m_buildingBind;
    GLuint m_buildingList;


};


#endif	/* _BUILDINGS_H */

