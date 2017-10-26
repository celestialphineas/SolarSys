#include <GL/glew.h>
#include <GL/glut.h>

void redraw()
{
    glewInit();
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
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
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
    // glBindVertexArray(VertexArrayID);
	// glClear(GL_COLOR_BUFFER_BIT);
	// glBegin(GL_TRIANGLE_FAN);
	// glEnd(); // GL_QUADS
	// glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(500, 500);
    int windowHandle = glutCreateWindow("Solar system");
    glutDisplayFunc(redraw);
	glutMainLoop();
	return 0;
}
