#include "mycircuit.h"

#include <math.h>
#include <vector>


#include "../utilities/myfunctions.h"

MyCircuit::MyCircuit() {
}

MyCircuit::~MyCircuit() {
    release();
}

void MyCircuit::drawBuildings(GLuint building_bind) {

    //glDisable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE); //Enable culling
    glCullFace(GL_BACK); //Remove back face
    glEnable(GL_TEXTURE_2D);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, building_bind);

    // ITERATORE PER I PALAZZI
    Circuit::BuildingsIterator bi;
    // ALTEZZA PALAZZI
    float height = 0.0;
    for (bi = race.circuit->buildings.begin(); bi != race.circuit->buildings.end(); ++bi) {
        // RECUPERO ALTEZZA PALAZZO
        height = (*bi).height;
        // ITERATORE PER I VERTICI DEL PALAZZO CORRENTE
        std::vector<Vertex>::iterator vi;
        for (vi = (*bi).footprint.begin(); vi != (*bi).footprint.end() - 1; ++vi) {
            // METTO IL QUAD PER COSTRUIRE IL PALAZZO
            glBegin(GL_QUADS);
            vcg::Point3f p00 = (*vi).P();
            glTexCoord2f(0.01, 0.99);
            glVertex3f(p00.X(), p00.Y(), p00.Z());

            ++vi;
            vcg::Point3f p01 = (*vi).P();
            glTexCoord2f(0.99, 0.99);
            glVertex3f(p01[0], p01[1], p01[2]);
            --vi;
            glTexCoord2f(0.99, 0.01);
            glVertex3f(p01[0], p01[1] + height, p01[2]);
            glTexCoord2f(0.01, 0.01);
            glVertex3f(p00[0], p00[1] + height, p00[2]);
            glEnd();
        }
        glBegin(GL_QUADS);
        vi = (*bi).footprint.end() - 1;
        vcg::Point3f p00 = (*vi).P();
        glTexCoord2f(0.01, 0.99);
        glVertex3f(p00[0], p00[1], p00[2]);
        vi = (*bi).footprint.begin();
        vcg::Point3f p01 = (*vi).P();
        glTexCoord2f(0.99, 0.99);
        glVertex3f(p01[0], p01[1], p01[2]);
        glTexCoord2f(0.99, 0.01);
        glVertex3f(p01[0], p01[1] + height, p01[2]);
        glTexCoord2f(0.01, 0.01);
        glVertex3f(p00[0], p00[1] + height, p00[2]);
        glEnd();
    }

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_CULL_FACE);


}

GLuint MyCircuit::generateBuildings(GLuint building_bind) {
    GLuint buildings = glGenLists(1);
    glNewList(buildings, GL_COMPILE);
    drawBuildings(building_bind);
    glEndList();

    return buildings;
}


void MyCircuit::release() {

    skybox.release();
    terrain.release();
    road.release();
    trees.release();
}
