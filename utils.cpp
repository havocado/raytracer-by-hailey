#include "utils.h"
#include <glad/gl.h>

void readFile2Str(std::string& content, const std::string& filename) {
    std::ifstream file(filename);
    content = "";

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            content += line + '\n';
        }
        file.close();
    } else {
        std::cerr << "File open failed: " << filename << std::endl;
    }
}

unsigned int compileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = &source[0];
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // Error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* infoLog = new char[length];
        glGetShaderInfoLog(id, length, &length, infoLog);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
        std::cout << infoLog << std::endl;
        free(infoLog);

        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int createShader(const std::string& vertShader, const std::string& fragShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

std::pair<int, int> getResolution(const CameraSpec& camera, const int& screenWidth) {
    return {screenWidth, std::round((float)screenWidth * camera.sensorHeight / camera.sensorWidth)};
}

float calculateRaySurfaceCosAngle(const Ray& r, const Vec3& n) {
    float dotProd = dot(r.direction(), n*(-1.f));
    float dotProdNormalized = dotProd / (r.direction().length() * n.length());
    return dotProdNormalized;
}