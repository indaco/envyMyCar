
#include "mycar.h"

MyCar::MyCar(const string &filename) {
    sCarFilename.assign(filename);
}

MyCar::~MyCar() {
}

bool MyCar::loadCar() {
    cout << " --> Loading " << this->sCarFilename;
    int iCar = vcg::tri::io::Importer<CMesh>::Open(mesh, getCarFilename());

    if (iCar == 0) {
        // update bounding box
        vcg::tri::UpdateBounding<CMesh>::Box(this->mesh);
        vcg::tri::UpdateNormals<CMesh>::PerVertexPerFace(this->mesh);

        this->_car.m = &this->mesh;
        this->_car.Update();

        cout << " --> OK" << endl;
        return true;
    }

    return false;

}

void MyCar::drawCar() {
    glPushMatrix();
    //glScalef(0.7, 0.7, 0.7);
    glTranslatef(-2.0, 1.3, 0);
   
    glMateriali(GL_FRONT, GL_SHININESS, 55);
    glPushMatrix();
    float d = mesh.bbox.Diag();
    glScale(3 / d);
    glRotatef(90, 0, 1, 0);
    glRotatef(-90, 1, 0, 0);
    

    vcg::Point4f spotpos = vcg::Point4f(-0.9, 0.3, -4, 1.0);
    vcg::Point4f spotpos2 = vcg::Point4f(0.9, 0.3, -4, 1.0);
    vcg::Point4f spotdir = vcg::Point4f(0.0, 0.0, -1.0, 0.0);
    glLightfv(GL_LIGHT1, GL_POSITION, &spotpos[0]);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, &spotdir[0]);
    glLightfv(GL_LIGHT2, GL_POSITION, &spotpos2[0]);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, &spotdir[0]);

    glTranslate(-(_car.m->bbox.Center()));
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    _car.Draw<vcg::GLW::DMSmooth, vcg::GLW::CMPerFace, vcg::GLW::TMNone > ();
    glPopMatrix();
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
}

GLuint MyCar::generateCar() {
    GLuint car = glGenLists(1);
    glNewList(car, GL_COMPILE);
    drawCar();
    glEndList();
    return car;
}

char* MyCar::getCarFilename() const {
    int length = sCarFilename.length();
    char *ptr2 = new char[length + 1];

    sCarFilename.copy(ptr2, length, 0);

    return ptr2;
}