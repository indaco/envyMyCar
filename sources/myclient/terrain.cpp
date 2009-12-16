#include "terrain.h"

Terrain::Terrain() {
    m_terrainList = 0;
    m_terrainBind = 0;
}

Terrain::~Terrain() {
}

bool Terrain::loadTexture(char *filename) {
    m_terrainBind = 2;
    loadBMPTexture(filename, m_terrainBind, GL_TRUE);
}

void Terrain::render(vcg::Point3f bmin, vcg::Point3f bmax) {
    //cout << "Sono Bmin: " << bmin[0] << bmin[1] <<bmin[2] << endl;
    //cout << "Sono Bmax: " << bmax[0] << bmax[1] <<bmax[2] << endl;

    glPushMatrix();

    if (m_terrainList == 0) {

        glEnable(GL_LIGHTING);
        glCullFace(GL_FRONT);

        m_terrainList = glGenLists(1);
        glNewList(m_terrainList, GL_COMPILE);
        glEnable(GL_TEXTURE_2D);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        glBindTexture(GL_TEXTURE_2D, m_terrainBind);
        glBegin(GL_QUADS); //terrain
        glTexCoord2d(0, 0);
        glVertex3f(bmin[0], bmin[1], bmin[2]);
        glTexCoord2d(3000, 0);
        glVertex3f(bmax[0], bmin[1], bmin[2]);
        glTexCoord2d(3000, 3000);
        glVertex3f(bmax[0], bmin[1], bmax[2]);
        glTexCoord2d(0, 3000);
        glVertex3f(bmin[0], bmin[1], bmax[2]);
        glEnd();
        glEndList();
    } else
        glCallList(m_terrainList);

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void Terrain::release() {
    glDeleteLists(m_terrainList, 1);
    m_terrainList = 0;
    m_terrainBind = 0;
}