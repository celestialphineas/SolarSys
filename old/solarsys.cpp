#include "gl_necessities.h"
#include "load_shaders.h"

// Background color
#define GL_CLEAR_COLOR 0.f, 0.f, 0.f, 0.f

GLFWwindow *init_glfw();
bool init_glew();
void display(GLFWwindow*);

class Sphere {
protected:
    GLfloat *vb_data;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> tex_coords;
    std::vector<GLuint> indices;
    unsigned stacks, slices, n_indices;
    GLuint vao;     // Vertex array object
    GLuint vbo[2];     // Vertex buffer object
    GLuint shader_program;
    GLfloat radius;
public:
    Sphere() {
        radius = 1.f;
        stacks = 32; slices = 32;
        n_indices = (slices * stacks + slices) * 6;
        for(unsigned i = 0; i <= stacks; i++) {
            // V texture coord
            float v = i / (float)stacks;
            float phi = v * M_PI;

            for(unsigned j = 0; j <= slices; j++) {
                float u = j / (float)slices;
                float theta = u * 2.f * M_PI;
                float x = glm::cos(theta) * glm::sin(phi);
                float y = glm::cos(phi);
                float z = glm::sin(theta) * glm::sin(phi);
                vertices.push_back(glm::vec3(x, y, z) * radius);
                normals.push_back(glm::vec3(x, y, z));
                tex_coords.push_back(glm::vec2(u, v));
            }
        }

        for(unsigned i = 0; i < slices * stacks + slices; i++) {
            indices.push_back(i);
            indices.push_back(i+slices+1);
            indices.push_back(i+slices);
            indices.push_back(i+slices+1);
            indices.push_back(i);
            indices.push_back(i+1);
        }

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        shader_program = load_shaders(
            "shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
        vb_data = new GLfloat[9];
        vb_data[0] = -1.f; vb_data[1] = -1.f; vb_data[2] = 0.f;
        vb_data[3] = 1.f; vb_data[4] = -1.f; vb_data[5] = 0.f;
        vb_data[6] = 0.f; vb_data[7] = 1.f; vb_data[8] = 0.f;
        // glGenBuffers(1, &vbo);
        // glBindBuffer(GL_ARRAY_BUFFER, vbo);
        // glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat),
        //     vb_data, GL_STATIC_DRAW);
        glGenBuffers(2, vbo);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3),
            vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
            indices.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    ~Sphere() {
        glDeleteBuffers(1, vbo);
        glDeleteVertexArrays(1, &vao);
        glDeleteProgram(shader_program);
        delete[] vb_data;
    }
    void draw() {
        glUseProgram(shader_program);
        glDrawElements(GL_TRIANGLES, n_indices, GL_UNSIGNED_INT, (void*)0);
        glDisableVertexAttribArray(0);
    }
};

void display(GLFWwindow *window) {
    // Clear colored background
    glClearColor(GL_CLEAR_COLOR);
    // Here for creating objects and sessions
    // ----
    Sphere sphere;
    // Display main loop
    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        sphere.draw();
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