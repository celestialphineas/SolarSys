#include "planet.h"

Sol *sun;
Planet *earth;
Planet *moon;
static float time_now = 0.;

void init_planets() {
    float body_scale = 1.;
    // The radi of the objects are calculated as:
    // radius = ln(lg(real_radius))
    // orbit radius = 0.1*real_radius^(1/4)
    sun = new Sol();
    sun->set_body_radius(body_scale * 4.260f);
    sun->set_rotation_period(606.12f);
    sun->set_rotation_inclination(7.25f);
    sun->set_rotation_epoch_offset(0.f);
    sun->set_texture("textures/gstar.png");

    earth = new Planet(*sun);
    earth->set_body_radius(body_scale * 1.336f);
    earth->set_semi_majoraxis(11.0594f);
    earth->set_orbit_period(2.f);
    earth->set_orbit_epoch_offset(0.f);
    earth->set_rotation_period(0.014f);
    earth->set_rotation_inclination(23.461f);
    earth->set_rotation_epoch_offset(0.f);
    earth->set_texture("textures/earthmap2k.jpg");

    moon = new Planet(*earth);
    moon->set_body_radius(body_scale * 1.175f);
    moon->set_semi_majoraxis(2.48998f);
    moon->set_orbit_period(1.f);
    moon->set_orbit_epoch_offset(0.f);
    moon->set_rotation_period(1.f);
    moon->set_rotation_inclination(6.687f);
    moon->set_rotation_epoch_offset(0.f);

    moon = new Planet(*earth, body_scale * 1.175f, 2.48998f,
        1.f, 0.f, 1.f, 6.687, 0.);
    moon->set_texture("textures/moon.png");
}

void timer_func(int arg) {
    sun->update(time_now);
    earth->update(time_now);
    moon->update(time_now);
    time_now += 0.001;
    glutTimerFunc(10, timer_func, 0);
}

void idle() {
    glutPostRedisplay();
}

void redraw(void) {
    // Clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, -30, 30, 0, 0, 0, 0, 1, 0);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glTranslatef(0.f, -0.f, -30.f);
    sun->draw(); earth->draw(); moon->draw();
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
    gluPerspective(45.f, (GLfloat)width/(GLfloat)height, 0.1f, 1000.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init() {
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
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
    // 
    timer_func(0);
    glutIdleFunc(idle);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}