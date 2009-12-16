
#ifndef _MYCAR_H
#define	_MYCAR_H

#include <iostream>
#include <string>

#include <SDL/SDL.h>

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <vector>

// mesh definition
#include <vcg/simplex/vertexplus/base.h>
#include <vcg/simplex/faceplus/base.h>
#include <vcg/complex/trimesh/base.h>
#include <vcg/complex/trimesh/update/bounding.h>
#include <vcg/complex/trimesh/update/normal.h>
#include <wrap/io_trimesh/import.h>
#include <wrap/gl/trimesh.h>
#include <wrap/gui/trackball.h>


class CEdge; // dummy prototype never used
class CFace;

using namespace std;
using namespace vcg;

class CVertex : public VertexSimp2< CVertex, CEdge, CFace, vert::Coord3f, vert::Normal3f > {
}; //face::WedgeTexture2f

class CFace : public FaceSimp2< CVertex, CEdge, CFace, face::VertexRef, face::Normal3f, face::Color4b> {
};

class CMesh : public vcg::tri::TriMesh< vector<CVertex>, vector<CFace> > {
};


/*
 * class: MyCar
 *
 * Carica la mesh della macchina e si occupa di renderizzarla
 */
class MyCar {
public:

    /* constructor: MyCar - public
     *
     *  Carica il file.ply contenente il modello della auto.
     *
     * Arguments:
     *
     *      - string: la posizione ed il nome del file.ply
     *
     */
    MyCar(const string &filename); 
    
    
    virtual ~MyCar(); 
    
      
     
    /* method: loadCar
     *
     * Importa il file PLY in un oggetto di tipo CMesh usando l'importer vcg::tri::io
     *
     * Esempio: int iCar = vcg::tri::io::Importer<CMesh>::Open(mesh, filename); 
     *
     *  Arguments:
     *
     *          - none
     *
     * Return value:
     *          
     *          - bool
     */
    bool loadCar();
    
    
    
    /* method: drawCar
     *      
     *  Setta le luci ed i materiali e richiama il metodo Draw relativo a vcg::GlTrimesh<CMesh> per renderizzareil modello sul display, dopo aver effettuato alcune trasformazioni.
     *
     * Arguments:
     *  
     *          - none
     *
     * Return value:
     *
     *          - void
     *
     */
    void drawCar();
    
    
    
    /* method: generateCar
     *
     *  Crea una nuova DisplayList con compilazione GL_COMPILE ( gli errori non saranno generati fino a quando la lista non verrà eseguita)
     *  e richiama drawCar.
     *
     *
     *  Aruments:
     *      
     *          - none
     *
     *  Return value:
     *      
     *          - GLuint: da richiamare con il metodo glDisplayList
     *
     *  Vedi anche: 
     *          <drawCar>
     *
     */
    GLuint generateCar();
    
    
    
    /* method: getCarFilename
     *
     *  Il nome del file modello viene passato al costruttore della classe come una stringa di tripo string. 
     * Questa funzione provvede alla conversione in char* per poter passare il nome del file all'Importer
     * del modello.
     *
     *  Arguments:
     *      
     *          - none
     *
     *  Return value:
     *
     *          - char*: la stringa C++-like convertita in una stringa C-like
     *
     *  Vedi anche:
     *      <loadCar>
     *
     */
    char* getCarFilename() const;
    
    
private:
    CMesh mesh;
    vcg::GlTrimesh<CMesh> _car;
    string sCarFilename;

};


#endif	/* _MYCAR_H */

