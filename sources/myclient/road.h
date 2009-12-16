
#ifndef _ROAD_H
#define	_ROAD_H


#include <GL/glew.h>
#include <GL/glut.h>
#include <cmath>
#include <ctime>
#include <vcg/space/point3.h>
#include <vector>

#include "../game_client.h"
#include "../game_viewer.h"
#include "../race.h"

#include "../utilities/myfunctions.h"

/* class: Road
 *
 *  Provvede alla generazione ed il rendering del circuito texturizzato
 */

class Road {
public:

    /* constructor: Road */
    Road();
    Road(const Road& orig);
    virtual ~Road();

    /* method: loadTexture
     *
     *  Carica la texture della strada ed inizializza il bind alla texture     
     */
    bool loadTexture(char *filename);


    /* method: render
     *
     *  Dato il path del circuito come argomento, questa funzione provvede alla disegno del circuito
     * come quad strip e mappa la texture.
     *
     */
    void render(std::vector<vcg::Point2<Vertex> > path);


    /* method: release
     *
     *  Rilascia le risorse che sono state impegnate per il rendering del circuito
     */
    void release();
private:

    GLuint m_roadList;
    GLuint m_roadBind;
};


#endif	/* _ROAD_H */

