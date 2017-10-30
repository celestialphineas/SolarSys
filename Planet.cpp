#include "Planet.h"

void Planet::update(float time) {
    x = parent->x + cos(deg2rad(orbit_epoch_offset)
            + time/orbit_period*2*M_PI);
    y = parent->y + sin(deg2rad(orbit_epoch_offset)
            + time/orbit_period*2*M_PI);
    z = 0.f;
    rotation_about_axis = rotation_epoch_offset + time/orbit_period*360.;
}