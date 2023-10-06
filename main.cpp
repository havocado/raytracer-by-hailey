#include <GLFW/glfw3.h>
#include <bits/stdc++.h>

#include "vec3.h"
#include "color.h"
#include "cameraSpec.h"

// Placeholder for raytracing.
color getColorPlaceholder(const float& NDC_x, const float& NDC_y) {
    color c;
    c[0] = (NDC_x+1.f)*0.5f;
    c[1] = (NDC_y+1.f)*0.5f;
    c[2] = 1.f;
    return c;
}

color runRaytracing(const float& NDC_x, const float& NDC_y) {
    color c;
    // do something
    return c;
}

std::pair<int, int> getWindowDim(const cameraSpec& camera, const int& numPixelWidth) {
    return std::pair<int, int>(numPixelWidth,
                               std::round((float)numPixelWidth * camera.sensorHeight / camera.sensorWidth));
}

int main() {
    GLFWwindow* window;

    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    // Initialize Camera
    std::cout << "Initializing Camera ......" << std::endl;
    cameraSpec camera; // Use default constants

    // User defined constants
    const int numPixelWidth = 640; // Arbitrary

    // Compute desired number of pixels
    const std::pair<int, int> windowDim = getWindowDim(camera, numPixelWidth);

    // Create window
    std::cout << "Creating Window ......" << std::endl;
    window = glfwCreateWindow(windowDim.first, windowDim.second, "asdf", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Make Context
    glfwMakeContextCurrent(window);

    float ratio;
    int width, height;

    glfwGetFramebufferSize(window, &width, &height);
    ratio = (float)width / (float)height;
    std::cout << "framebuffer sizes: width " << width << ", height " << height << std::endl;

    // Set background color to viewport
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    // Raytracing loop
    std::cout << "Starting Raytracing ......" << std::endl;
    // Begin mode: draw points
    glBegin(GL_POINTS);
    for (int i = 0; i < 2*width; i++) {
        for (int j = 0; j < 2*height; j++) {
            // Compute NDC (Normalized Device Coordinates)
            float NDC_x = (float)j/(float)height-1.f; // [-1, 1]
            float NDC_y = (float)i/(float)width-1.f; // [-1, 1]

            // Get color from NDC coordinates
            color c = getColorPlaceholder(NDC_x, NDC_y);

            // Draw point in color
            glColor3f(c.x(),c.y(),c.z());
            glVertex2f(NDC_x,NDC_y);
        }
    }
    // End mode: draw points
    glEnd();
    std::cout << "Rendering done!" << std::endl;

    // Swap front/back buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

    // Wait until the window is closed
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    // Destroy window
    std::cout << "Closing window ......" << std::endl;

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
