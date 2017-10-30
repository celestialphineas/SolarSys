#ifndef PLANET_H__
#define PLANET_H__

#include <cmath>
#define deg2rad(x)  ((x) * M_PI / 180.)

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

    // Position vec
    float x, y, z;
    float rotation_about_axis;
public:
    Planet(Planet &parent_, float body_radius_,
            float semi_majoraxis_, float orbit_period_,
            float orbit_epoch_offset_,
            float rotation_period_, float rotation_inclination_,
            float rotation_epoch_offset_):
        parent(&parent_), body_radius(1.f),
        semi_majoraxis(10.f), orbit_period(orbit_period_),
        orbit_epoch_offset(orbit_epoch_offset_),
        rotation_period(rotation_period_), 
        rotation_inclination(rotation_inclination_), 
        rotation_epoch_offset(rotation_epoch_offset_) {
            x = parent->x + cos(deg2rad(orbit_epoch_offset));
            y = parent->y + sin(deg2rad(orbit_epoch_offset));
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
    virtual float get_rotation() {return deg2rad(rotation_about_axis); }

    virtual void update(float time);
};

// Class of the sun
// Period         609.12  # 25.38 days
// Inclination      7.25
// AscendingNode   75.77
// MeridianAngle   23.00  # standard meridian
class Sol: public Planet {
private:
    Planet *set_parent(Planet &parent_) { return this; }
    float set_body_radius(float radius_)
        { return 0.; }
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
    void update(float time) {
        rotation_about_axis = rotation_epoch_offset + time/orbit_period*360.;
    }
public:
    Sol(float body_radius_):
        Planet(*this, 1.f, 0.f, 1.f, 0.f, 609.12f, 7.25f,0.f) {
        x = 0.; y = 0.; z = 0.;
        rotation_about_axis = rotation_epoch_offset;
    }
    virtual ~Sol() {}
};

#endif