#include "Planet.h"

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
        glTranslatef(this->get_x(), this->get_y(), this->get_z());
        glRotatef(this->get_rotation_inclination(), 0.f, 1.f, 0.f);
        glRotatef(this->get_rotation(), 0.f, 0.f, 1.f);
        glutSolidSphere(this->get_body_radius(), 16, 16);
    glPopMatrix();
}