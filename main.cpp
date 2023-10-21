#include <GLFW/glfw3.h>
#include <bits/stdc++.h>

#include "vec3.h"
#include "Color.h"
#include "cameraSpec.h"
#include "sphere.h"
#include "cube.h"
#include "hittableObject.h"

Color runRaytracing(const CameraSpec& camera, const std::vector<HittableObject*>& objectList, const float& NDC_x, const float& NDC_y) {
    // Compute outgoing ray
    // See documentation
    Point3 rayOrigin = camera.position;
    Point3 A = Point3(NDC_x, NDC_y, -1.f);
    Point3 B = A * Point3(camera.sensorWidth, camera.sensorHeight, camera.focal_length);
    Point3 rayScreenDirection = B; // B rotated by camera.rotation. TODO: Implement matrix multiplication
    Ray r(rayOrigin, rayScreenDirection);

    // Compute closest collision
    CollisionData closestCollision(false);
    for (auto hittable : objectList) {
        CollisionData coll = hittable->rayCollisionPoint(r);
        if (!coll.collided) {
            continue;
        }
        if (!closestCollision.collided || coll.t < closestCollision.t) {
            closestCollision = coll;
        }
    }
    if (closestCollision.collided) {
        Vec3 targetNormal = closestCollision.normal;
        return 0.5f * (targetNormal + Vec3(1.f, 1.f, 1.f));
    }
    else {
        return {0.5f, 0.5f, 0.5f};
    }
}

std::pair<int, int> getWindowDim(const CameraSpec& camera, const int& numPixelWidth) {
    return std::pair<int, int>(numPixelWidth,
                               std::round((float)numPixelWidth * camera.sensorHeight / camera.sensorWidth));
}

int main() {
    GLFWwindow* window;

    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    // Initialize objects
    std::vector<HittableObject*> objectList;
    Sphere sphere1(Point3(0.f, 0.f, -1.3f), Matrix3x3(), 0.47f);
    objectList.push_back(&sphere1);
    Cube cube1(Point3(1.f, 0.f, -1.3f), Matrix3x3(), 0.5f, 0.6f, 0.55f);
    cube1.rotateX(-2.f);
    objectList.push_back(&cube1);
    Cube cube2(Point3(-0.7f, 0.f, -1.1f), Matrix3x3(), 0.7f, 0.6f, 0.3f);
    cube2.rotateZ(-1.2f);
    objectList.push_back(&cube2);

    // Initialize Camera
    std::cout << "Initializing Camera ......" << std::endl;
    CameraSpec camera; // Use default constants

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
            Color c = runRaytracing(camera, objectList, NDC_x, NDC_y);

            // Draw point in color
            glColor3f(c.x(),c.y(),c.z());
            glVertex2f(NDC_x,NDC_y);
        }
    }
    // End mode: draw points
    glEnd();
    std::cout << "Rendering done!" << std::endl;

    // Swap front/back buffers
    glfwPollEvents();
    glfwSwapBuffers(window);

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
