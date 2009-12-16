#include "road.h"

Road::Road() {
    m_roadList = 0;
    m_roadBind = 0;
}

Road::~Road() {

}

bool Road::loadTexture(char *filename) {
    m_roadBind = 1;

    loadBMPTexture(filename, m_roadBind, GL_TRUE);
}

void Road::render(std::vector<vcg::Point2 <Vertex> >path) {
    if (m_roadList == 0) {

        glEnable(GL_LIGHTING);
        glCullFace(GL_BACK);

        m_roadList = glGenLists(1);
        glNewList(m_roadList, GL_COMPILE);

        // draw circuit	
        Street::TilesIterator ti;
        vcg::Point3f p0, p1;
        glEnable(GL_TEXTURE_2D);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        glBindTexture(GL_TEXTURE_2D, m_roadBind);
        glBegin(GL_QUAD_STRIP);
        // with following code we loose the last quad
        for (ti = race.circuit->street.path.begin(); ti != race.circuit->street.path.end() - 1; ++ti) {
            p0 = (*ti)[0].P();
            p1 = (*ti)[1].P();
            glTexCoord2d(0.0, 0.0);
            glVertex3f(p0[0], p0[1] + 0.01, p0[2]);
            glTexCoord2d(1.0, 0.0);
            glVertex3f(p1[0], p1[1] + 0.01, p1[2]);
            ++ti;
            p0 = (*ti)[0].P();
            p1 = (*ti)[1].P();
            glTexCoord2d(0.0, 1.0);
            glVertex3f(p0[0], p0[1] + 0.01, p0[2]);
            glTexCoord2d(1.0, 1.0);
            glVertex3f(p1[0], p1[1] + 0.01, p1[2]);
            --ti;
        }
        glEnd();
        //street closure the last quad
        glCullFace(GL_BACK);
        glBegin(GL_QUADS);
        ti = race.circuit->street.path.end();
        --ti;
        p0 = (*ti)[0].P();
        p1 = (*ti)[1].P();
        glTexCoord2d(1, 0);
        glVertex3f(p0[0], p0[1] + 0.01, p0[2]);
        glTexCoord2d(0, 0);
        glVertex3f(p1[0], p1[1] + 0.01, p1[2]);
        ti = race.circuit->street.path.begin();
        p0 = (*ti)[0].P();
        p1 = (*ti)[1].P();
        glTexCoord2d(1, 1);
        glVertex3f(p0[0], p0[1] + 0.01, p0[2]);
        glTexCoord2d(0, 1);
        glVertex3f(p1[0], p1[1] + 0.01, p1[2]);
        glEnd();

        glEndList();
    } else
        glCallList(m_roadList);

    glDisable(GL_BLEND);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_TEXTURE_2D);

}

void Road::release() {
    glDeleteLists(m_roadList, 1);
    m_roadList = 0;
    m_roadBind = 0;
}