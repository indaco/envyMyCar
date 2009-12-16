

#ifndef _TERRAIN_H
#define	_TERRAIN_H


#include <math.h>
#include <time.h>
#include <vcg/space/point3.h>
#include <vector>
#include <GL/glew.h>
#include <GL/glut.h>
#include "../utilities/myfunctions.h"

#include <iostream>
using std::cout;
using std::endl;

/* class: Terrain
 * 
 */
class Terrain {
public:
    /* constructor: Terrain */
    Terrain();
    Terrain(const Terrain& orig){};
    virtual ~Terrain();
    
    /* method: loadTexture */
    bool loadTexture(char* filename);
    
    /* method: render */
    void render(vcg::Point3f bmin, vcg::Point3f bmax);
    
    /* method: release */
    void release();
    
private:
    GLuint m_terrainList;
    GLuint m_terrainBind;
};





#endif	/* _TERRAIN_H */

