
#ifndef _TREES_H
#define	_TREES_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <cmath>
#include <ctime>
#include <vcg/space/point3.h>
#include <vector>


#include "../game_client.h"
#include "game_viewer.h"
#include "race.h"

#include "../utilities/tga.h"


/* class: Tree
 *
 *  Questa classe di occupa di renderizzare gli alberi (file TGA).
 *  
 *  Per renderizzare gli alberi uso la tecnica dei billboards. Si tratta di una tecnica di riduzione della geometria, in cui un modello 3D
 *  viene rimpiazzato con una immagine 2D. 
 * 
 * Quando il billboard e' lontano abbastanza e l'angolo di vista e' corretto, rappresenta una buona
 *  approsimazione del modello stesso. Dal punto di vista  della riduzione dei poligoni, risulta difficile riuscire ad ottenere lo stesso risultato con
 *  tecniche diverse da quelle dei billboards. Qualunque sia il numero di poligoni diventa un singolo quad texturizzato.
 *
 *  Gli alberi sono simmetrici rispetto all'asse y. Tendono ad avere un alto numero di poligoni e le scene esterne tendono ad avere molti alberi e foglie.
 *  Se non si usasse una tecnica del genere molti cicli di pipeline sarebbero richiesti solo per renderizzare alberi e foglie.
 *
 *  Dato che il billboard e' simmetrico agli assi, nel disegnarlo si tiene costante l'asse y e si ruota rispetto alla posizione della camera. 
 *  La normale e' la normale dal modello di origine alla camera.
 *  Questo semplifica di molto il posizionamento sulla scena. La y-max e la y-min del quad sono la y-max e la y-min del bounding box dell'oggetto 
 *  (allineato ali assi), mentre la larghezza del quad corrisponde alla larghezza del modello.
 *
 */

class Tree {
public:
    
    /* constructor: Tree */
    Tree();
    Tree(const Tree& orig) {};
    virtual ~Tree();
    
    /* -------------------------------------
     * method: loadImage
     *
     *  Carica il file TGA del modello di albero
     *--------------------------------------*/
    bool loadImage(const char *filename);
    
    /* -------------------------------------
     * method: render
     *
     *  Dato il punto di vista renderizza il modello.
     *--------------------------------------*/
    void render(vcg::Point3f pov);
    
    /* -------------------------------------
     * method: billboard
     *
     *  Dalla posizione della camera e da quella dell'albero
     *  esegue il billboard.
     *--------------------------------------*/
    void billboard(float *cam, float *treePos);
    
    
    /* -------------------------------------
     * method: release
     *
     *  Rilascia le risorse
     *--------------------------------------*/
    void release();
private:

    GLuint m_treeList;
    GLuint m_treeBind;
};



#endif	/* _TREES_H */

