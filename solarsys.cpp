#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <GL/glut.h>
#include "Planet.h"

Sol *sun;
Planet *earth;
Planet *moon;
static float time_now = 0.;

void init_planets() {
    float body_scale = 0.1;
    // radius = ln(lg(real_radius))
    // orbit radius = 0.1*real_radius^(1/4)
    sun = new Sol(body_scale * 4.260f);
    earth = new Planet(*sun, body_scale * 1.336f, 11.0594f,
        2.f, 0.f, 0.014f, 23.461f, 0.);
    moon = new Planet(*earth, body_scale * 1.175f, 2.48998f,
        1.f, 0.f, 1.f, 6.687, 0.);
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
    // Background color
    glClearColor(0.f, 0.f, 0.f, 0.f);
    // Clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT, GL_LINE);
    glPushMatrix();
        glTranslatef(0.f, -0.f, -30.f);
        sun->draw(); earth->draw(); moon->draw();
    glPopMatrix();
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
    gluPerspective(45.f, (GLfloat)width/(GLfloat)height, 0.1f, 100.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowSize(1024, 768);
    int glut_window = glutCreateWindow("Solar System");
    init_planets();
    // GLUT window display function
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