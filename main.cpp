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

static void error_callback(int error, const char* description){
    fprintf(stderr, "Error: %s\n", description);
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
    std::string fileName = "../data/bun_zipper_res2.ply";
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

    // Create Camera
    std::cout << "Creating Camera ......" << std::endl;
    CameraSpec camera; // Use default constants

    // Create window
    std::cout << "Creating Window ......" << std::endl;
    glfwSetErrorCallback(error_callback);
    GLFWwindow* window;

    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const int screenWidth = 640;
    const std::pair<int, int> resolution = getResolution(camera, screenWidth);
    window = glfwCreateWindow(resolution.first, resolution.second, "Raytracer by Hailey", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);

    // Read actual resolution from created window
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    std::cout << "framebuffer sizes: width " << width << ", height " << height << std::endl;

    std::cout << "Starting Raytracing ......" << std::endl;

    // Generate Sample points on screen
    Sampler sampler;
    std::vector<NdcPoint> samplePoints = sampler.createSamplePoints(width, height);

    // Set background color to viewport
    glViewport(0, 0, width, height);

    // Draw triangle
    float trianglePos[6] = {
            -1.f, -1.0f,
            -1.f, 1.f,
            1.f, 1.0f
    };
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), trianglePos, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    std::string vertShader;
    std::string fragShader;
    readFile2Str(vertShader, "../vertShader.vert");
    readFile2Str(fragShader, "../fragShader.frag");

    unsigned int shader = createShader(vertShader, fragShader);

    glUseProgram(shader);

    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwPollEvents();
    glfwSwapBuffers(window);

    // Creating texture framebuffer
    unsigned int textureBuffer;
    glGenBuffers(1, &textureBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, textureBuffer);

    // Create texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Configure framebuffer


    // Raytracing loop
    //glBegin(GL_POINTS);
    int counter = 0;
    for (auto s: samplePoints) {
        Ray r = camera.getRay(s, width, height);
        Color c = raytrace(r, scene);
        // Draw point in color
        //glColor3f(c.x(),c.y(),c.z());
        //glVertex2f(s.x,s.y);

        counter++;
    }
    // End mode: draw points
    //glEnd();

    std::cout << "Rendering done!" << std::endl;

    // Wait until the window is closed
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // Destroy window
    std::cout << "Closing window ......" << std::endl;
    glfwDestroyWindow(window);
    glDeleteShader(shader);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
