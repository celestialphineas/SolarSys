#include "loadShader.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Background color
#define GL_CLEAR_COLOR 0.f, 0.f, 0.f, 0.f

GLFWwindow *init_glfw();
bool init_glew();
void display(GLFWwindow*);

void display(GLFWwindow *window) {
    // Clear colored background
    glClearColor(GL_CLEAR_COLOR);
    // Here for creating objects and sessions
    // ----
    // Display main loop
    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

int main(int argc, char **argv) {
    // Initialize GLFW
    GLFWwindow *window;
    if(!(window = init_glfw())) {
        std::cerr << "Failed to open GLFW window.\n";
        try {glfwTerminate();} catch(int) {}
        return -1;
    }
    // Initialize GLEW
    if(!init_glew()) {
        std::cerr << "Failed to initialize GLEW.\n";
        try {glfwTerminate();} catch(int) {}
        return -2;
    }

    display(window);
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
}

// Initialize glfw
GLFWwindow *init_glfw() {
    // Initialize GLFW
    if(!glfwInit()) return NULL;
    glfwWindowHint(GLFW_SAMPLES, 4);    // 4xAA
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  // OpenGL 3.3
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Open a window and create its OpenGL context
    GLFWwindow *window = glfwCreateWindow(1024, 768, "Solar System",
        NULL, NULL);
    if(window) glfwMakeContextCurrent(window);
    return window;
}

// Initialize glew
// return 1 for success
bool init_glew() {
    glewExperimental = true;
    return glewInit() == GLEW_OK;
}