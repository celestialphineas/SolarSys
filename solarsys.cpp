#include "planet.h"

Planet *sun;
Planet *milky_way;
Planet *mercury;
Planet *venus;
Planet *earth;
Planet *moon;
Planet *mars;
Planet *camera_center;
bool show_orbit = true;
int toggle_time = 1;
GLfloat camera_theta = 0.;
GLfloat camera_phi = 10.;
GLfloat camera_distance = 30.;

static float time_now = 0.;
// The real solar sys is much more harmonic (crazy) than you think
// If we draw everything in real scale, you will only see a few dots
#define TO_SCALED_BODY_RADIUS(x)    (body_scale*log(x))
#define TO_SCALED_ORBIT_SMA(x)      (orbit_scale*pow(x, orbit_power))
#define PLANET_ORBIT_PEROID_SCALING(x)      (10. * x)
#define PLANET_ROTATION_PERIOD_SCALING(x)   (x / 10.)
void init_planets() {
    float body_scale = 0.03;
    float orbit_scale = 0.001;
    float orbit_power = 0.5;
    
    sun = new Sol();
    sun->set_body_radius(TO_SCALED_BODY_RADIUS(696392.));
    sun->set_rotation_period(PLANET_ROTATION_PERIOD_SCALING(606.12f));
    sun->set_rotation_inclination(7.25f);
    sun->set_rotation_epoch_offset(0.f);
    sun->set_texture("textures/gstar.png");
    camera_center = sun;

    milky_way = new Sol();
    milky_way->set_body_radius(5000.);
    milky_way->set_rotation_period(1e4);
    milky_way->set_rotation_inclination(27.13f);
    milky_way->set_rotation_epoch_offset(68.f);
    milky_way->set_texture("textures/mw.jpg");

    mercury = new Planet(*sun);
    mercury->set_body_radius(TO_SCALED_BODY_RADIUS(2439.7));
    mercury->set_semi_majoraxis(TO_SCALED_ORBIT_SMA(57909050.));
    mercury->set_orbit_period(PLANET_ORBIT_PEROID_SCALING(0.2408));
    mercury->set_orbit_epoch_offset(-90.f);
    mercury->set_rotation_period(PLANET_ROTATION_PERIOD_SCALING(1407.5f));
    mercury->set_rotation_inclination(28.55f);
    mercury->set_rotation_epoch_offset(35.f);
    mercury->set_texture("textures/mercury.jpg");

    venus = new Planet(*sun);
    venus->set_body_radius(TO_SCALED_BODY_RADIUS(6051.8));
    venus->set_semi_majoraxis(TO_SCALED_ORBIT_SMA(108208000.));
    venus->set_orbit_period(PLANET_ORBIT_PEROID_SCALING(0.6152));
    venus->set_orbit_epoch_offset(-90.f);
    venus->set_rotation_period(PLANET_ROTATION_PERIOD_SCALING(5832.443616f));
    venus->set_rotation_inclination(157.16f);
    venus->set_rotation_epoch_offset(137.f);
    venus->set_texture("textures/venus.jpg");

    earth = new Planet(*sun);
    earth->set_body_radius(TO_SCALED_BODY_RADIUS(6371.0));
    earth->set_semi_majoraxis(TO_SCALED_ORBIT_SMA(149598023.));
    earth->set_orbit_period(PLANET_ORBIT_PEROID_SCALING(1.));
    earth->set_orbit_epoch_offset(45.f);
    earth->set_rotation_period(PLANET_ROTATION_PERIOD_SCALING(23.93447117f));
    earth->set_rotation_inclination(23.461f);
    earth->set_rotation_epoch_offset(0.f);
    earth->set_texture("textures/earth.png");

    moon = new Planet(*earth);
    moon->set_body_radius(TO_SCALED_BODY_RADIUS(1737.1));
    moon->set_semi_majoraxis(TO_SCALED_ORBIT_SMA(384399.));
    moon->set_orbit_period(1.f);
    moon->set_orbit_epoch_offset(0.f);
    // Tidal locked
    moon->set_rotation_period(moon->get_orbit_period());
    moon->set_rotation_inclination(6.687f);
    moon->set_rotation_epoch_offset(-90.f);
    moon->set_texture("textures/moon.png");

    mars = new Planet(*sun);
    mars->set_body_radius(TO_SCALED_BODY_RADIUS(3396.0));
    mars->set_semi_majoraxis(TO_SCALED_ORBIT_SMA(2.27939e8));
    mars->set_orbit_period(PLANET_ORBIT_PEROID_SCALING(1.8809));
    mars->set_orbit_epoch_offset(237.f);
    mars->set_rotation_period(PLANET_ROTATION_PERIOD_SCALING(24.622962156f));
    mars->set_rotation_inclination(23.461f);
    mars->set_rotation_epoch_offset(0.f);
    mars->set_texture("textures/mars.jpg");
}

void timer_func(int arg) {
    milky_way->update(time_now);
    sun->update(time_now); mercury->update(time_now); venus->update(time_now);
    earth->update(time_now); moon->update(time_now); mars->update(time_now);
    time_now += 0.001 * toggle_time;
    glutTimerFunc(10, timer_func, 0);
}

void idle() {
    glutPostRedisplay();
}

void mouse_function(int button, int state, int x, int y) {
    // Toggle orbit
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        show_orbit = !show_orbit;
    if(button == 4) { // wheel scroll up
        camera_distance += 0.2;
    } 
    if(button == 3) { // wheel scroll down
        camera_distance -= 0.2;
    }
    // if(button == GLUT_MIDDLE_BUTTON && )
}

void keyboard_function(unsigned char key, int x, int y) {
    if(key == ' ') toggle_time = !toggle_time;
    else if(key == '0') camera_center = sun;
    else if(key == '1') camera_center = mercury;
    else if(key == '2') camera_center = venus;
    else if(key == '3') camera_center = earth;
    else if(key == '4') camera_center = mars;
    else if(key == '5') camera_center = moon;
    else if(key == 'w') camera_phi += 1.f;
    else if(key == 's') camera_phi -= 1.f;
    else if(key == 'a') camera_theta -= 1.f;
    else if(key == 'd') camera_theta += 1.f;
}

void redraw(void) {
    // Clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camera_center->get_x() + camera_distance*cos(deg2rad(camera_theta))*cos(deg2rad(camera_phi)),
        camera_center->get_y() + camera_distance*sin(deg2rad(camera_theta))*cos(deg2rad(camera_phi)),
        camera_center->get_z() + camera_distance*sin(deg2rad(camera_phi)),
        camera_center->get_x(), camera_center->get_y(), camera_center->get_z(),
        0, 0, 1);
    milky_way->draw();
    sun->draw(); mercury->draw(); venus->draw();
    earth->draw(); moon->draw(); mars->draw();
    if(show_orbit) {mercury->draw_orbit(); venus->draw_orbit();
        earth->draw_orbit(); moon->draw_orbit(); mars->draw_orbit();
    }
    glutSwapBuffers();
}

void reshape(int width, int height) {
    // Prevent the zero division
    if(height == 0) {
        height = 1;
    }
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Aspect Ratio
    gluPerspective(45.f, (GLfloat)width/(GLfloat)height, 0.1f, 10000.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init() {
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowSize(1024, 768);
    int glut_window = glutCreateWindow("Solar System");
    init_planets();
    // GLUT window display function
    init();
    glutDisplayFunc(redraw);
    // Window reshape function
    glutReshapeFunc(reshape);
    // Mouse control call back
    glutMouseFunc(mouse_function);
    glutKeyboardFunc(keyboard_function);
    timer_func(0);
    glutIdleFunc(idle);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}