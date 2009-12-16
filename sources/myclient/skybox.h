
#ifndef _SKYBOX_H
#define	_SKYBOX_H


#include <GL/glew.h>
#include <GL/glut.h>
#include <cmath>
#include <ctime>
#include <vcg/space/point3.h>
#include <vector>

#include "../utilities/myfunctions.h"


/*
 * class: Skybox
 *
 *  Si tratta di una tecnica per  dare una buona illusione del senso di immersione in una scena.
 *  Lo scenario viene renderizzato su 6 textures applicate sulle 6 facce di un cubo allineato con gli assi del mondo. 
 *  La camera e' posizionata al centro del cubo e la distanza dai lati dovrebbe essere mantenuta costante.
 *  
 * E' la prima cosa che dovrebbe essere renderizzata sulla scena, quindi non risulta necessario pulire il color buffer, dato che lo skybox copre sempre l'intera scena.
 *
 * La scrittura sul depth buffer e testing vanno disattivati in modo da ridurre il numero di calcoli eseguiti, questo perche' nella scena finale 
 * niente intersechera' mai con lo skybox.
 *
 * Conviene disabilitare anche i bit di nebbia, texture, lighting e renderizzarlo senza alcun effetto atmosferico.
 *
 * Le dimensioni (larghezza e altezza) vanno scelte in modo che i punti piu' lontani (gli angoli) siano piu' vicini alla camera del piano di clipping, 
 * mentre il formato (size) deve essere tale da farlo rientrare nel cono di vista.
 *  
 * I passi per renderizzare uno skybox sono i seguenti:
 *  - Pulisco il depth buffer
 *  - Disabilito il depth test
 *  - Disabilito il depth writes
 *  - Disabilito fog e lighting
 *  - Renderizzo il cubo
 *  - Abilito il depth test e writes
 *  _ Abilito lighting e fog
 *  - Disegno il resto della scena
 */
class Skybox {
public:
    
    /*-------------------------------------------------------------
     * constructor: Skybox
     * ------------------------------------------------------------*/
    Skybox();

    Skybox(const Skybox& orig) {
    };

    virtual ~Skybox() {
    };
    
    
    /*-------------------------------------------------------------
     * method: initialize
     *
     * Inizializza le dimensioni dello skybox
     *
     *  Arguments:
     *
     *          - float: width
     *
     *          - float: height
     *
     *          - float: size
     * ------------------------------------------------------------*/
    bool initialize(float w, float h, float size);
    
    
    

    /*-------------------------------------------------------------
     * method:loadTextures
     *
     * Carica le texure dello skybox
     *
     *  Arguments:
     *
     *          - char*: top, bottom, front, back, left, right texture filenames
     *
     *  Return value:
     *
     *          - bool
     * ------------------------------------------------------------*/
    bool loadTextures(char *top, char *bottom, char* front, char *back, char*left, char* right);

    /*-------------------------------------------------------------
     * method: render
     *
     * Renderizza lo skybox a schermo. 
     *
     *  Arguments:
     *
     *          - float: x
     *
     *          - float: y
     *
     *          - float: z
     *
     *          - vcg::Pointef: camera
     *
     *  Return value:
     *
     *          - void
     * ------------------------------------------------------------*/
    void render(float x, float y, float z, vcg::Point3f camera);



    /*-------------------------------------------------------------
     * method: release
     *
     * Rilascia le texture e cancella la display list
     *
     * ------------------------------------------------------------*/
    void release();


    /* Il numero di textures */
    const static int counter = 6;

    /* method: setSkyWidth */
    inline void setSkyWidth(float w) {
        fSkyWidth = w;
    }

    /* method: setSkyHeight */
    inline void setSkyHeight(float h) {
        fSkyHeight = h;
    }

    /* method: setSkySize */
    inline void setSkySize(float s) {
        fSkySize = s;
    }

    /* method: getSkyWidth */
    inline float getSkyWidth() {
        return fSkyWidth;
    }

    /* method: getSkyHeight */
    inline float getSkyHeight() {
        return fSkyHeight;
    }

    /* method: getSkySize */
    inline float getSkySize() {
        return fSkySize;
    }

    /* 
     * enumeration: SKY_SIDE
     * Le facce del cubo 
     */
    enum {
        SKY_TOP,
        SKY_BOTTOM,
        SKY_FRONT,
        SKY_BACK,
        SKY_LEFT,
        SKY_RIGHT
    };

private:

    float fSkyWidth, fSkyHeight, fSkySize;
    GLuint m_skyboxTextures[counter]; // 6 texture objects
    GLuint m_skyboxList;
};


#endif	/* _SKYBOX_H */

