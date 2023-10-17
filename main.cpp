#include <GLFW/glfw3.h>
#include <bits/stdc++.h>

#include "vec3.h"
#include "color.h"
#include "cameraSpec.h"
#include "sphere.h"
#include "Cube.h"
#include "hittableObject.h"

color runRaytracing(const cameraSpec& camera, const std::vector<hittableObject*>& objectList, const float& NDC_x, const float& NDC_y) {
    // Compute outgoing ray
    // See documentation
    point3 rayOrigin = camera.position;
    point3 A = point3(NDC_x, NDC_y, -1.f);
    point3 B = A * point3(camera.sensorWidth, camera.sensorHeight, camera.focal_length);
    point3 rayScreenDirection = B; // B rotated by camera.rotation. TODO: Implement matrix multiplication
    ray r(rayOrigin, rayScreenDirection);

    // Compute collision
    std::vector<collisionData> collisions;
    for (auto hittable : objectList) {
        collisionData coll = hittable->rayCollisionPoint(r);
        if (coll.collided) {
            collisions.push_back(coll);
        }
    }
    // STUB: render the first object from collisions.
    // TODO: Include t in collisionData
    if (!collisions.empty()) {
        vec3 targetNormal = collisions[0].normal;
        return 0.5f * (targetNormal + vec3(1.f, 1.f, 1.f));
    }
    else {
        return {0.5f, 0.5f, 0.5f};
    }
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

    // Initialize objects
    std::vector<hittableObject*> objectList;
    /*sphere sphere1(point3(0.f, 0.f, -1.3f), matrix3x3(), 0.5f);
    objectList.push_back(&sphere1);*/
    Cube cube1(point3(0.f, 0.f, -2.3f), matrix3x3(), 0.5f, 0.6f, 0.3f);
    objectList.push_back(&cube1);

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
            color c = runRaytracing(camera, objectList, NDC_x, NDC_y);

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
