#include <GLFW/glfw3.h>
#include <bits/stdc++.h>
#include <ctime>

#include "vec3.h"
#include "cameraSpec.h"
#include "sphere.h"
#include "cube.h"
#include "hittableObject.h"
#include "material.h"

const int NUM_BOUNCE = 10;
const int NUM_BOUNCED_RAYS = 3;

CollisionData getCollision(const Ray& r, const std::vector<HittableObject*>& objectList) {
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
    return closestCollision;
}

Color getColorFromRay(const Ray& r, const std::vector<HittableObject*>& objectList, const int& kthBounce) {
    CollisionData closestCollision = getCollision(r, objectList);
    if (closestCollision.collided) {
        if (kthBounce < NUM_BOUNCE) {
            Color resultColor;
            for (int i = 0; i < NUM_BOUNCED_RAYS; i++) {
                Ray bouncedRay = closestCollision.getNextRay();
                float bounceTheta = std::acos(dot(r.direction(), closestCollision.normal*(-1.f)) / (r.direction().length() * closestCollision.normal.length()));
                Color collidedMaterialColor = closestCollision.getColor();
                //resultColor += collidedMaterialColor * getColorFromRay(bouncedRay, objectList, kthBounce+1) * std::cos(bounceTheta);
                resultColor += collidedMaterialColor * getColorFromRay(bouncedRay, objectList, kthBounce+1);
            }
            resultColor /= (float)NUM_BOUNCED_RAYS;
            return resultColor;
        }
        else {
            return {0.f, 0.f, 0.f};
        }
    }
    else {
        // skybox collision
        return {200.f/255.999f, 244.f/255.999f, 255.f/255.999f};
    }
}

Color runRaytracing(const CameraSpec& camera, const std::vector<HittableObject*>& objectList, const float& NDC_x, const float& NDC_y) {
    // Create initial Ray r
    Ray r(camera.position, camera.getDirection(NDC_x, NDC_y));

    return getColorFromRay(r, objectList, 0);
}

std::pair<int, int> getWindowDim(const CameraSpec& camera, const int& numPixelWidth) {
    return std::pair<int, int>(numPixelWidth,
                               std::round((float)numPixelWidth * camera.sensorHeight / camera.sensorWidth));
}

int main() {
    std::srand(std::time(nullptr));
    GLFWwindow* window;

    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    // Material creation
    Material grayMaterial;
    Material purpleMaterial(Color(0.45f, 0.9f, 0.9f));
    Material blueMaterial(Color(0.45f, 0.45f, 0.9f));
    Material redMaterial(Color(0.9f, 0.45f, 0.45f));
    Material yellowMaterial(Color(0.9f, 0.9f, 0.45f));

    // Initialize objects
    std::vector<HittableObject*> objectList;
    Sphere sphere1(Point3(0.f, 0.f, -1.3f), Matrix3x3(), 0.47f, &purpleMaterial);
    objectList.push_back(&sphere1);
    Cube cube1(Point3(1.f, 0.f, -1.3f), Matrix3x3(), 0.5f, 0.6f, 0.55f, &yellowMaterial);
    cube1.rotateX(-2.f);
    objectList.push_back(&cube1);
    Cube cube2(Point3(-0.7f, 0.f, -1.1f), Matrix3x3(), 0.7f, 0.6f, 0.3f, &redMaterial);
    cube2.rotateZ(-1.2f);
    objectList.push_back(&cube2);
    Cube cube3(Point3(0.f, -0.47f, 0.f), Matrix3x3(), 50.f, 0.2f, 50.f, &blueMaterial);
    objectList.push_back(&cube3);
    Sphere sphere2(Point3(-3.8f, 0.f, -0.5f), Matrix3x3(), 3.f, &yellowMaterial);
    objectList.push_back(&sphere2);

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
    for (int j = 2*height-1; j >= 0; j--) {
        glBegin(GL_POINTS);
        for (int i = 0; i < 2*width; i++) {
            // Compute NDC (Normalized Device Coordinates)
            float NDC_x = (float)i/(float)width-1.f; // [-1, 1]
            float NDC_y = (float)j/(float)height-1.f; // [-1, 1]

            // Get color from NDC coordinates
            Color c = runRaytracing(camera, objectList, NDC_x, NDC_y);

            // Draw point in color
            glColor3f(c.x(),c.y(),c.z());
            glVertex2f(NDC_x,NDC_y);
        }
        // End mode: draw points
        glEnd();
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

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
