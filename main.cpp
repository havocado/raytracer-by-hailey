#include <GLFW/glfw3.h>
#include <bits/stdc++.h>

#include "vec3.h"
#include "color.h"

int main() {
    GLFWwindow* window;

    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    const std::pair<int, int> windowDim(640, 480);
    window = glfwCreateWindow(windowDim.first, windowDim.second, "asdf", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Make Context
    glfwMakeContextCurrent(window);

    // Print something
    std::cout << "Starting program" << std::endl;

    float ratio;
    int width, height;

    glfwGetFramebufferSize(window, &width, &height);
    ratio = (float)width / (float)height;
    std::cout << "framebuffer sizes: width " << width << ", height " << height << std::endl;

    // Set background color to viewport
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    // Begin mode: draw points
    glBegin(GL_POINTS);
    for (int i = 0; i < 2*width; i++) {
        for (int j = 0; j < 2*height; j++) {
            float NDC_x = (float)j/(float)height-1.f; // [-1, 1]
            float NDC_y = (float)i/(float)width-1.f; // [-1, 1]
            glColor3f((float)j/(float)height*0.5f,(float)i/(float)width*0.5f,1.f);
            glVertex2f(NDC_x,NDC_y);
        }
    }
    // End mode: draw points
    glEnd();

    // Swap front/back buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
