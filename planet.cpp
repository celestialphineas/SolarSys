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
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
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
        gluSphere(sphere, this->get_body_radius(), N_SEGMENTS, N_SEGMENTS);
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

void Planet::draw_orbit() {
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glPushMatrix();
        // Model
        GLfloat light_p[]={-x,-y,-z,0};
        glLightfv(GL_LIGHT0,GL_POSITION,light_p);
        glTranslatef(parent->get_x(), parent->get_y(), parent->get_z());
        glScalef(this->get_semi_majoraxis(), this->get_semi_majoraxis(),
            this->get_semi_majoraxis());
        int n_sample = 1024;
        glBegin(GL_LINE_LOOP);
        glColor3f(1.0f, 1.0f, 1.0f);
        for(int j = 0;j < n_sample;++j)
        {
            glVertex2f(cos(2*M_PI*j/(float)n_sample),
                sin(2*M_PI*j/(float)n_sample));
        }
        glEnd();
    glPopMatrix();
}

void Sol::draw() {
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glPushMatrix();
        // Model
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
        gluSphere(sphere, this->get_body_radius(), N_SEGMENTS, N_SEGMENTS);
        glEndList();
        gluDeleteQuadric(sphere);
        
    glPopMatrix();
}
