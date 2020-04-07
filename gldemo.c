#include <stdio.h>

#ifdef __APPLE__
/* Defined before OpenGL includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include <GLFW/glfw3.h>

void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

void gldemo_draw() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0); /* Red */
    glVertex2f(0.8, -0.8);
    glColor3f(0, 1, 0); /* Green */
    glVertex2f(0, 0.9);
    glColor3f(0, 0, 1); /* Blue */
    glVertex2f(-0.8, -0.8);
    glEnd();
}

void gldemo_run() {
#ifdef __APPLE__
    glfwInitHint(GLFW_COCOA_CHDIR_RESOURCES, GLFW_FALSE);
#endif
    
    if (!glfwInit()) {
        fprintf(stderr, "Error: glfwInit() returned 0");
        return;
    }
    
    printf("glfwGetVersionString(): %s\n", glfwGetVersionString());
    
    glfwSetErrorCallback(error_callback);

    GLFWwindow* window;

#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#endif

    window = glfwCreateWindow(640, 480, "JNI OpenGL Demo", NULL, NULL);
    
    if (!window) {
        glfwTerminate();
        fprintf(stderr, "Error: Failed creating GL window");
        return;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* Render here */
        gldemo_draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}
