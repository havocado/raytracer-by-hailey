#include <GLFW/glfw3.h>
#include <bits/stdc++.h>

#include "vec3.h"
#include "color.h"

// Placeholder for raytracing.
color getColorPlaceholder(const float& NDC_x, const float& NDC_y) {
    color c;
    c[0] = (NDC_x+1.f)*0.5f;
    c[1] = (NDC_y+1.f)*0.5f;
    c[2] = 1.f;
    return c;
}

std::pair<int, int> getWindowDim(const std::pair<float, float>& sensorDim, const int& numPixelWidth) {
    return std::pair<int, int>(numPixelWidth,
                               std::round((float)numPixelWidth * sensorDim.second / sensorDim.first));
}

int main() {
    GLFWwindow* window;

    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    // User defined constants
    const std::pair<float, float> sensorDim(2.36f, 1.56f); // APS-C Camera sensor size [cm]
    const int numPixelWidth = 640; // Arbitrary

    // Compute desired number of pixels
    const std::pair<int, int> windowDim = getWindowDim(sensorDim, numPixelWidth);

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

    // Loop
    while (!glfwWindowShouldClose(window)) {
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        // Begin mode: draw points
        glBegin(GL_POINTS);
        for (int i = 0; i < 2*width; i++) {
            for (int j = 0; j < 2*height; j++) {
                glColor3f((float)j/(float)height*0.5f,(float)i/(float)width*0.5f,1.f);
                glVertex2f((float)j/(float)height-1.f,(float)i/(float)width-1.f);
            }
        }
        glEnd();

        // Swap front/back buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
