
#include "tree.h"

Tree::Tree() {
    m_treeList = 0;
    m_treeBind = 0;
}

Tree::~Tree() {

}

bool Tree::loadImage(const char *filename) {
    CTargaImage *tgaFile = 0;
    tgaFile = new CTargaImage;
    if (!tgaFile->Load(filename)) {
        delete tgaFile;
        return (false);
    }

    m_treeBind = 12;
    
    glBindTexture(GL_TEXTURE_2D, m_treeBind);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tgaFile->GetWidth(), tgaFile->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tgaFile->GetImage());
    delete tgaFile;

    return (true);

}

void Tree::render(vcg::Point3f pov) {
    glEnable(GL_TEXTURE_2D);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0);
    glBindTexture(GL_TEXTURE_2D, m_treeBind);
    // Iteratore sugli alberi
    Circuit::TreesIterator ti;
    for (ti = race.circuit->trees.begin(); ti != race.circuit->trees.end(); ++ti) {
        glPushMatrix();
        // posizione dell'albero
        vcg::Point3f pos = (*ti).pos;
        // altezza
        float height = (*ti).height;
        // punto di vista
        float cam[3] = {pov[0], pov[1], pov[2]};
        // mi sposto sulla posizione dell'albero
        float treePos[3] = {pos[0], pos[1], pos[2]};
        glTranslatef(treePos[0], treePos[1], treePos[2]);

        // billboard
        billboard(cam, treePos);

        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3f(-(height), 0.0f, 0.0f);
        glTexCoord2f(1, 0);
        glVertex3f((height), 0.0f, 0.0f);
        glTexCoord2f(1, 1);
        glVertex3f((height), height * 2, 0.0f);
        glTexCoord2f(0, 1);
        glVertex3f(-(height), height * 2, 0.0f);
        glEnd();

        glPopMatrix();
    }
    glDisable(GL_BLEND);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_TEXTURE_2D);
}


/* Billboarding */
void Tree::billboard(float *cam, float *treePos) {

    // il quad guarda verso di me (+z)
    Point3f lookAt = vcg::Point3f(0, 0, 1);

    // proiezione su xz del vettore camera-albero
    Point3f objToCamProj = vcg::Point3f(cam[0] - treePos[0], 0, cam[2] - treePos[2]);
    objToCamProj = objToCamProj.Normalize();

    // vettore camera albero
    Point3f objToCam = vcg::Point3f(cam[0] - treePos[0], cam[1] - treePos[1], cam[2] - treePos[2]);
    objToCam = objToCam.Normalize();

    // prodotto vettoriale => mi dice il segno dell'angolo di rotazione
    // + => upAux punta nella direzione positiva delle y
    // -  => punterà in basso e la rotazione sarà negativa
    Point3f upAux = lookAt^objToCamProj;

    // il coseno dell'angolo è dato dal profotto scalare tra i due vettori
    float angleCosine = lookAt*objToCamProj;

    // rotazione
    //  se lookAt e il vettore v sono troppo vicini  allora |aux| dovrebbe essere
    // maggiore di 1 a causa di una mancanza di precisione
    if ((angleCosine < 0.99990) && (angleCosine > -0.9999))
        glRotatef(acos(angleCosine)*180 / 3.14, upAux[0], upAux[1], upAux[2]);

    // rotazione rispetto ad x (visto dall'alto)
    angleCosine = objToCamProj*objToCam;

    // rotazione intorno ad x per migliorare la vista dall'alto
    if ((angleCosine < 0.99990) && (angleCosine> -0.9999))
        if (objToCam[1] < 0)
            glRotatef(acos(angleCosine)*180 / 3.14, 1, 0, 0);
        else
            glRotatef(acos(angleCosine)*180 / 3.14, -1, 0, 0);

}

void Tree::release() {
    m_treeBind = 0;
    m_treeList = 0;
}