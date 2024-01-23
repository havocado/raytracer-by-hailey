#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <bits/stdc++.h>
#include <ctime>

#include "vec3.h"
#include "cameraSpec.h"
#include "sphere.h"
#include "cube.h"
#include "hittableObject.h"
#include "material.h"
#include "plyImport.h"

const int NUM_BOUNCE = 2;//15;
const int NUM_BOUNCED_RAYS = 2;//5;
const int STOP_DIVIDING_AFTER_K_BOUNCES = 2;

GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
};

static void error_callback(int error, const char* description){
    fprintf(stderr, "Error: %s\n", description);
}

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
        if (closestCollision.isLight()) {
            return closestCollision.getLight();
        }
        if (kthBounce < NUM_BOUNCE) {
            Color resultColor;
            if (kthBounce > STOP_DIVIDING_AFTER_K_BOUNCES) {
                Ray bouncedRay = closestCollision.getNextRay();
                float bounceTheta = std::acos(dot(r.direction(), closestCollision.normal*(-1.f)) / (r.direction().length() * closestCollision.normal.length()));
                Color collidedMaterialColor = closestCollision.getColor();
                return collidedMaterialColor * getColorFromRay(bouncedRay, objectList, kthBounce+1);
            }
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
    glfwSetErrorCallback(error_callback);
    GLFWwindow* window;

    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Material creation
    Material grayMaterial;
    Material whiteMaterial(Color(0.9f, 0.9f, 0.9f));
    Material purpleMaterial(Color(0.45f, 0.9f, 0.9f));
    Material blueMaterial(Color(0.45f, 0.45f, 0.9f));
    Material redMaterial(Color(0.9f, 0.45f, 0.45f));
    Material yellowMaterial(Color(0.9f, 0.9f, 0.45f));

    // Initialize objects
    std::vector<HittableObject*> objectList;
    std::string fileName = "../data/bun_zipper_res2.ply";
    Mesh bunnyMesh = plyImport::read(fileName, whiteMaterial);
    bunnyMesh.moveZ(-0.20f);
    bunnyMesh.moveY(-0.1f);
    bunnyMesh.moveX(0.045f);
    objectList.push_back(&bunnyMesh);

    Cube cube1(Point3(1.f, 0.f, -1.3f), Matrix3x3(), 0.5f, 0.6f, 0.55f, &purpleMaterial);
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
    window = glfwCreateWindow(windowDim.first, windowDim.second, "Raytracer by Hailey", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Make Context
    glfwMakeContextCurrent(window);
    // load GLAD
    gladLoadGL(glfwGetProcAddress);

    float ratio;
    int width, height;

    glfwGetFramebufferSize(window, &width, &height);
    ratio = (float)width / (float)height;
    std::cout << "framebuffer sizes: width " << width << ", height " << height << std::endl;

    // OpenGL stuff
    //unsigned int VBO;
    //glGenBuffers(1, &VBO);
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Set background color to viewport
    glViewport(0, 0, width, height);

    Shader shaderProgram("vertShader.vert", "fragShader.frag");





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
