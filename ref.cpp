#include "loadShader.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(int argc, char *argv[])
{
    if(!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);    // 4xAA
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  // OpenGL 3.0
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // Open a window and create its OpenGL context
    GLFWwindow *window = glfwCreateWindow(1024, 768, "Solar System", NULL, NULL);
    if(window == NULL) {
        std::cerr << "Failed to open GLFW window\n";
        glfwTerminate();
        return -2;
    }

    // Initialize GLEW
    glfwMakeContextCurrent(window);
    glewExperimental = true;
    if(glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        glfwTerminate();
        return -3;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
    GLuint programID = LoadShaders("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
        g_vertex_buffer_data, GL_STATIC_DRAW);

    // Main loop
    while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
        !glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);
            glUseProgram(programID);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glDisableVertexAttribArray(0);
            glfwSwapBuffers(window);
            glfwPollEvents();
    }
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);

    // Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

    return 0;
}
