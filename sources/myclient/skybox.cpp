#include "skybox.h"

Skybox::Skybox() {
    for (int i = 0; i < 6; ++i)
        m_skyboxTextures[i] = 0;

    m_skyboxList = 0;
}

bool Skybox::initialize(float w, float h, float size) {
    fSkyWidth = w;
    fSkyHeight = h;
    fSkySize = size;
    return (true);
}

bool Skybox::loadTextures(char *top, char *bottom, char *front, char *back, char *left, char *right) {

    m_skyboxTextures[SKY_TOP] = 5;
    m_skyboxTextures[SKY_BOTTOM] = 6;
    m_skyboxTextures[SKY_FRONT] = 7;
    m_skyboxTextures[SKY_BACK] = 8;
    m_skyboxTextures[SKY_LEFT] = 9;
    m_skyboxTextures[SKY_RIGHT] = 10;


    loadBMPTexture(top, m_skyboxTextures[SKY_TOP], GL_TRUE);
    loadBMPTexture(bottom, m_skyboxTextures[SKY_BOTTOM], GL_TRUE);
    loadBMPTexture(front, m_skyboxTextures[SKY_FRONT], GL_TRUE);
    loadBMPTexture(back, m_skyboxTextures[SKY_BACK], GL_TRUE);
    loadBMPTexture(left, m_skyboxTextures[SKY_LEFT], GL_TRUE);
    loadBMPTexture(right, m_skyboxTextures[SKY_RIGHT], GL_TRUE);


    return (true);
}

void Skybox::render(float x, float y, float z, vcg::Point3f camera) {

    glDepthMask(GL_FALSE);

    glPushAttrib(GL_FOG_BIT | GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT | GL_TEXTURE_BIT);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);


    // CENTRO LO SKYBOX SULLE POSIZIONI X,Y,Z PASSATE COME PARAMETRI
    x = (x - getSkyWidth()) / 2;
    y = (y - getSkyHeight()) / 2;
    z = (z - getSkySize()) / 2;

    glPushMatrix();
    glTranslatef(camera.X(), camera.Y() + 50, camera.Z());

    if (m_skyboxList == 0) {
        m_skyboxList = glGenLists(1);
        glNewList(m_skyboxList, GL_COMPILE_AND_EXECUTE);

        glDisable(GL_FOG);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);
        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

        // Top
        glBindTexture(GL_TEXTURE_2D, m_skyboxTextures[SKY_TOP]);
        glBegin(GL_QUADS);
        glTexCoord2f(0.999f, 0.999f);
        glVertex3f(x + getSkyWidth(), y + getSkyHeight(), z);
        glTexCoord2f(0.001f, 0.999f);
        glVertex3f(x + getSkyWidth(), y + getSkyHeight(), z + getSkySize());
        glTexCoord2f(0.001f, 0.001f);
        glVertex3f(x, y + getSkyHeight(), z + getSkySize());
        glTexCoord2f(0.999f, 0.001f);
        glVertex3f(x, y + getSkyHeight(), z);
        glEnd();

        // Bottom
        glBindTexture(GL_TEXTURE_2D, m_skyboxTextures[SKY_BOTTOM]);
        glBegin(GL_QUADS);
        glTexCoord2f(0.999f, 0.999f);
        glVertex3f(x, y, z);
        glTexCoord2f(0.001f, 0.999f);
        glVertex3f(x, y, z + getSkySize());
        glTexCoord2f(0.001f, 0.001f);
        glVertex3f(x + getSkyWidth(), y, z + getSkySize());
        glTexCoord2f(0.999f, 0.001f);
        glVertex3f(x + getSkyWidth(), y, z);
        glEnd();

        // Front
        glBindTexture(GL_TEXTURE_2D, m_skyboxTextures[SKY_FRONT]);
        glBegin(GL_QUADS);
        glTexCoord2f(0.999f, 0.999f);
        glVertex3f(x + getSkyWidth(), y, z);
        glTexCoord2f(0.001f, 0.999f);
        glVertex3f(x + getSkyWidth(), y, z + getSkySize());
        glTexCoord2f(0.001f, 0.001f);
        glVertex3f(x + getSkyWidth(), y + getSkyHeight(), z + getSkySize());
        glTexCoord2f(0.999f, 0.001f);
        glVertex3f(x + getSkyWidth(), y + getSkyHeight(), z);
        glEnd();

        // Back
        glBindTexture(GL_TEXTURE_2D, m_skyboxTextures[SKY_BACK]);
        glBegin(GL_QUADS);
        glTexCoord2f(0.001f, 0.001f);
        glVertex3f(x, y + getSkyHeight(), z);
        glTexCoord2f(0.999f, 0.001f);
        glVertex3f(x, y + getSkyHeight(), z + getSkySize());
        glTexCoord2f(0.999f, 0.999f);
        glVertex3f(x, y, z + getSkySize());
        glTexCoord2f(0.001f, 0.999f);
        glVertex3f(x, y, z);
        glEnd();

        // Left
        glBindTexture(GL_TEXTURE_2D, m_skyboxTextures[SKY_LEFT]);
        glBegin(GL_QUADS);
        glTexCoord2f(0.001f, 0.999f);
        glVertex3f(x + getSkyWidth(), y, z);
        glTexCoord2f(0.001f, 0.001f);
        glVertex3f(x + getSkyWidth(), y + getSkyHeight(), z);
        glTexCoord2f(0.999f, 0.001f);
        glVertex3f(x, y + getSkyHeight(), z);
        glTexCoord2f(0.999f, 0.999f);
        glVertex3f(x, y, z);
        glEnd();


        // Right
        glBindTexture(GL_TEXTURE_2D, m_skyboxTextures[SKY_RIGHT]);
        glBegin(GL_QUADS);
        glTexCoord2f(0.001f, 0.999f);
        glVertex3f(x, y, z + getSkySize());
        glTexCoord2f(0.001f, 0.001f);
        glVertex3f(x, y + getSkyHeight(), z + getSkySize());
        glTexCoord2f(0.999f, 0.001f);
        glVertex3f(x + getSkyWidth(), y + getSkyHeight(), z + getSkySize());
        glTexCoord2f(0.999f, 0.999f);
        glVertex3f(x + getSkyWidth(), y, z + getSkySize());
        glEnd();

        glEndList();
    } else
        glCallList(m_skyboxList);

    glPopAttrib();
    glPopMatrix();

    glDepthMask(GL_TRUE);

}

void Skybox::release() {
    for (int i = 0; i < 6; ++i)
        m_skyboxTextures[i] = 0;
    glDeleteLists(m_skyboxList, 1);
    m_skyboxList = 0;
}