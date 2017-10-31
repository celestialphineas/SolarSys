#include "planet.h"

void Planet::update(float time_) {
    x = parent->x + semi_majoraxis*cos(deg2rad(orbit_epoch_offset)
            + time_/orbit_period*2*M_PI);
    y = parent->y + semi_majoraxis*sin(deg2rad(orbit_epoch_offset)
            + time_/orbit_period*2*M_PI);
    z = 0.f;
    rotation_about_axis = rotation_epoch_offset + time_/rotation_period*360.;
}

void Planet::draw() {
    glPushMatrix();
        // Model
        GLfloat light_p[]={-x,-y,-z,0};
        glLightfv(GL_LIGHT0,GL_POSITION,light_p);
        glTranslatef(this->get_x(), this->get_y(), this->get_z());
        glRotatef(this->get_rotation_inclination(), 0.f, 1.f, 0.f);
        glRotatef(this->get_rotation(), 0.f, 0.f, 1.f);
        
        GLUquadricObj *sphere = NULL;
        sphere = gluNewQuadric();
        gluQuadricDrawStyle(sphere, GLU_FILL);
        if(texture_set) {
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            gluQuadricTexture(sphere, true);
        }
        gluQuadricNormals(sphere, GLU_SMOOTH);
        gluSphere(sphere, this->get_body_radius(), 64, 64);
        glEndList();
        gluDeleteQuadric(sphere);
        
    glPopMatrix();
}

bool Planet::set_texture(const char *filename) {
    if(!filename) return false;
    texture = load_texture(filename);
    if(!texture) return false;
    return texture_set = true;
}

void Sol::draw() {
    glPushMatrix();
        // Model
        GLfloat light_p[]={0,0,1,0};
        glLightfv(GL_LIGHT0,GL_POSITION,light_p);
        glTranslatef(this->get_x(), this->get_y(), this->get_z());
        glRotatef(this->get_rotation_inclination(), 0.f, 1.f, 0.f);
        glRotatef(this->get_rotation(), 0.f, 0.f, 1.f);
        
        GLUquadricObj *sphere = NULL;
        sphere = gluNewQuadric();
        gluQuadricDrawStyle(sphere, GLU_FILL);
        if(texture_set) {
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            gluQuadricTexture(sphere, true);
        }
        gluQuadricNormals(sphere, GLU_SMOOTH);
        gluSphere(sphere, this->get_body_radius(), 64, 64);
        glEndList();
        gluDeleteQuadric(sphere);

        // glutSolidSphere(this->get_body_radius(), 64, 64);
        
    glPopMatrix();
}