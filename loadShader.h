#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <vector>

GLuint LoadShaders(const char * vertex_file_path,
                    const char * fragment_file_path);