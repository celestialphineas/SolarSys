#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <GL/glut.h>
#include "Planet.h"



void redraw(void) {
    // Background color
    glClearColor(0.f, 0.f, 0.f, 0.f);
    // Clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPushMatrix();
        glTranslatef(0.f, 0.f, -2.f);
        glutSolidSphere(0.5f, 32, 32);
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
    redraw();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowSize(1024, 768);
    int glut_window = glutCreateWindow("Solar System");
    // GLUT window display function
    glutDisplayFunc(redraw);
    // Window reshape function
    glutReshapeFunc(reshape);
    // 
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}