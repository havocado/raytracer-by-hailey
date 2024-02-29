#include <GLFW/glfw3.h>
#include <bits/stdc++.h>
#include <ctime>

#include "vec3.h"
#include "cameraSpec.h"
#include "sphere.h"
#include "cube.h"
#include "hittableObject.h"
#include "material.h"
#include "plyImport.h"
#include "sampler.h"
#include "scene.h"
#include "utils.h"

const int NUM_BOUNCE = 15;
const int NUM_BOUNCED_RAYS = 5;
const int STOP_DIVIDING_AFTER_K_BOUNCES = 2;

Color raytrace(const Ray& r, Scene& scene) {
    CollisionData closestCollision = scene.findClosestCollision(r);

    if (!closestCollision.collided) {
        return {200.f/255.999f, 244.f/255.999f, 255.f/255.999f};
    }
    else if (closestCollision.isLight()) {
        return closestCollision.getLight();
    }
    else {
        std::vector<Ray> bouncedRays = scene.getBouncedRays(closestCollision,
            NUM_BOUNCE, NUM_BOUNCED_RAYS, STOP_DIVIDING_AFTER_K_BOUNCES);
        if (bouncedRays.empty()) {
            return {0.f, 0.f, 0.f};
        }
        Color resultColor;
        for (Ray br: bouncedRays) {
            Color bouncedColor = raytrace(br, scene);
            float cosTheta = calculateRaySurfaceCosAngle(br, closestCollision.normal);
            resultColor += closestCollision.getColor() * bouncedColor;// * cosTheta;
        }
        resultColor /= (float)bouncedRays.size();
        return resultColor;
    }
}

std::pair<int, int> getWindowDim(const CameraSpec& camera, const int& numPixelWidth) {
    return {numPixelWidth, std::round((float)numPixelWidth * camera.sensorHeight / camera.sensorWidth)};
}

int main() {
    std::srand(std::time(nullptr));

    // Material creation
    Material grayMaterial;
    Material whiteMaterial(Color(0.9f, 0.9f, 0.9f));
    Material purpleMaterial(Color(0.45f, 0.9f, 0.9f));
    Material blueMaterial(Color(0.45f, 0.45f, 0.9f));
    Material redMaterial(Color(0.9f, 0.45f, 0.45f));
    Material yellowMaterial(Color(0.9f, 0.9f, 0.45f));

    // Initialize objects
    Scene scene;
    std::string fileName = "../data/bunny/reconstruction/bun_zipper_res2.ply";
    Mesh bunnyMesh = plyImport::read(fileName, whiteMaterial);
    bunnyMesh.moveZ(-0.20f);
    bunnyMesh.moveY(-0.1f);
    bunnyMesh.moveX(0.045f);
    scene.objectList.push_back(&bunnyMesh);

    Cube cube1(Point3(1.f, 0.f, -1.3f), Matrix3x3(), 0.5f, 0.6f, 0.55f, &purpleMaterial);
    cube1.rotateX(-2.f);
    scene.objectList.push_back(&cube1);
    Cube cube2(Point3(-0.7f, 0.f, -1.1f), Matrix3x3(), 0.7f, 0.6f, 0.3f, &redMaterial);
    cube2.rotateZ(-1.2f);
    scene.objectList.push_back(&cube2);
    Cube cube3(Point3(0.f, -0.47f, 0.f), Matrix3x3(), 50.f, 0.2f, 50.f, &blueMaterial);
    scene.objectList.push_back(&cube3);
    Sphere sphere2(Point3(-3.8f, 0.f, -0.5f), Matrix3x3(), 3.f, &yellowMaterial);
    scene.objectList.push_back(&sphere2);

    // Initialize Camera
    std::cout << "Initializing Camera ......" << std::endl;
    CameraSpec camera; // Use default constants

    // User defined constants
    // Since ratio is determined by the camera specifications, window height is not configurable
    const int numPixelWidth = 640;
    const std::pair<int, int> windowDim = getWindowDim(camera, numPixelWidth);

    // Create window
    std::cout << "Creating Window ......" << std::endl;
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    GLFWwindow* window;
    window = glfwCreateWindow(windowDim.first, windowDim.second, "Raytracer by Hailey", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);

    // Read actual resolution from created window
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    std::cout << "framebuffer sizes: width " << width << ", height " << height << std::endl;

    // Set background color to viewport
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    std::cout << "Starting Raytracing ......" << std::endl;

    // Generate Sample points on screen
    Sampler sampler;
    std::vector<NdcPoint> samplePoints = sampler.createSamplePoints(width, height);

    // Raytracing loop
    glBegin(GL_POINTS);
    int counter = 0;
    for (auto s: samplePoints) {
        Ray r = camera.getRay(s, width, height);
        Color c = raytrace(r, scene);
        // Draw point in color
        glColor3f(c.x(),c.y(),c.z());
        glVertex2f(s.x,s.y);

        counter++;
    }
    // End mode: draw points
    glEnd();
    glfwPollEvents();
    glfwSwapBuffers(window);
    std::cout << "Rendering done!" << std::endl;

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
