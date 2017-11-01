#ifndef PLANET_H__
#define PLANET_H__

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <GL/glut.h>
#include <cmath>
#include "texture_loader.h"
#define deg2rad(x)  ((x) * M_PI / 180.)
#define N_SEGMENTS  64

class Planet {
protected:
    Planet *parent;
    float body_radius;
    // float body_eccentricity;
    
    // Orbit parameters
    float semi_majoraxis;
    float orbit_period;
    float orbit_epoch_offset;       // In degree
    // float orbit_eccentricity;
    // float orbit_inclination;
    // float orbit_ascending_node;
    // float arg_periapsis;
    // float true_anomaly;

    // Rotation parameters
    float rotation_period;
    float rotation_inclination;
    float rotation_epoch_offset;    // In degree
    // float rotation_ascending_node;
    // float meridian_angle;

    // Texture
    bool texture_set;
    GLuint texture;

    // Position vec
    float x, y, z;
    float rotation_about_axis;
public:
    Planet(Planet &parent_, float body_radius_ = 1.f,
            float semi_majoraxis_ = 10.f, float orbit_period_ = 2.f,
            float orbit_epoch_offset_ = 0.f,
            float rotation_period_ = 1.f, float rotation_inclination_ = 10.f,
            float rotation_epoch_offset_ = 0.f):
        parent(&parent_), body_radius(body_radius_),
        semi_majoraxis(semi_majoraxis_), orbit_period(orbit_period_),
        orbit_epoch_offset(orbit_epoch_offset_),
        rotation_period(rotation_period_), 
        rotation_inclination(rotation_inclination_), 
        rotation_epoch_offset(rotation_epoch_offset_),
        texture_set(false) {
            x = parent->x + semi_majoraxis*cos(deg2rad(orbit_epoch_offset));
            y = parent->y + semi_majoraxis*sin(deg2rad(orbit_epoch_offset));
            z = 0.f;
            rotation_about_axis = rotation_epoch_offset;
    }
    virtual ~Planet() {}
    virtual Planet *set_parent(Planet &parent_)
        { return parent = &parent_; }
    virtual float set_body_radius(float radius_)
        { return body_radius = radius_; }
    virtual float set_semi_majoraxis(float semi_majoraxis_)
        { return semi_majoraxis = semi_majoraxis_; }
    virtual float set_orbit_period(float orbit_period_)
        { return orbit_period = orbit_period_; }
    virtual float set_orbit_epoch_offset(float orbit_epoch_offset_)
        { return orbit_epoch_offset = orbit_epoch_offset_; }
    virtual float set_rotation_period(float rotation_period_)
        { return rotation_period = rotation_period_; }
    virtual float set_rotation_inclination(float rotation_inclination_)
        { return rotation_inclination = rotation_inclination_; }
    virtual float set_rotation_epoch_offset(float rotation_epoch_offset_)
        { return rotation_epoch_offset = rotation_epoch_offset_; }
    virtual bool set_texture(const char *filename);
    
    virtual float get_body_radius() { return body_radius; }
    virtual float get_semi_majoraxis() { return semi_majoraxis; }
    virtual float get_orbit_period() { return orbit_period; }
    virtual float get_orbit_epoch_offset() { return orbit_epoch_offset; }
    virtual float get_rotation_period() { return rotation_period; }
    virtual float get_rotation_inclination() { return rotation_inclination; }
    virtual float get_rotation_epoch_offset() { return rotation_epoch_offset; }
    
    virtual float get_x() { return x; }
    virtual float get_y() { return y; }
    virtual float get_z() { return z; }
    virtual float get_rotation() {return rotation_about_axis; }

    virtual void update(float time);
    virtual void draw();
    virtual void draw_orbit();
};

// Class of the sun
// Period         609.12  # 25.38 days
// Inclination      7.25
// AscendingNode   75.77
// MeridianAngle   23.00  # standard meridian
class Sol: public Planet {
public:
    Planet *set_parent(Planet &parent_) { return this; }
    float set_semi_majoraxis(float semi_majoraxis_)
        { return 0.; }
    float set_orbit_period(float semi_majoraxis_)
        { return 1.; }
    float set_orbit_epoch_offset(float orbit_epoch_offset)
        { return 0.; }
    float set_rotation_period(float rotation_period_)
        { return rotation_period = rotation_period_; }
    float set_rotation_inclination(float rotation_inclination_)
        { return rotation_inclination = rotation_inclination_; }
    float set_rotation_epoch_offset(float rotation_epoch_offset_)
        { return rotation_epoch_offset = rotation_epoch_offset_; }
    void update(float time_) {
        rotation_about_axis = rotation_epoch_offset + time_/orbit_period*360.;
    }
    void draw();
    Sol():
        Planet(*this, 4.260f, 0.f, 1e20f, 0.f, 1e20f, 7.25f,0.f) {
        x = 0.; y = 0.; z = 0.;
        rotation_about_axis = rotation_epoch_offset;
    }
    virtual ~Sol() {}
};

#endif