
#include "buildings.h"

Buildings::Buildings() {
    m_buildingBind = 0;
    m_buildingList = 0;
}

Buildings::~Buildings() {
    m_buildingBind = 0;
    m_buildingList = 0;
}

bool Buildings::loadTexture(char *filename) {

    m_buildingBind = 5;

    loadBMPTexture(filename, m_buildingBind, GL_TRUE);

    return (true);
}

void Buildings::render() {

    glEnable(GL_CULL_FACE); //Enable culling
    glCullFace(GL_BACK); //Remove back face
    glEnable(GL_TEXTURE_2D);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    if (m_buildingList == 0) {
        m_buildingList = glGenLists(1);
        glNewList(m_buildingList, GL_COMPILE);
        glBindTexture(GL_TEXTURE_2D, m_buildingBind);

        // iteratore dei palazzi
        Circuit::BuildingsIterator bi;
        // altezza
        float height = 0.0;
        for (bi = race.circuit->buildings.begin(); bi != race.circuit->buildings.end(); ++bi) {
            // altezza del palazzo
            height = (*bi).height;
            // iteratore dei vertici del palazzo
            std::vector<Vertex>::iterator vi;
            for (vi = (*bi).footprint.begin(); vi != (*bi).footprint.end() - 1; ++vi) {
                // uso un quad per costruire un palazzo
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

            // ultimo palazzo
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

        glEndList();
    } else
        glCallList(m_buildingList);

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_CULL_FACE);


}

void Buildings::release() {
    glDeleteLists(m_buildingList, 1);
    m_buildingBind = 0;
    m_buildingList = 0;
}