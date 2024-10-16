#include "Spectre/Rendering/Arch/OpenGL/OpenGLShader.h"
#include <filesystem>

using namespace Spectre;

OpenGLShader::OpenGLShader(const std::string& vertexPath,
                           const std::string& fragmentPath)
    : ShaderBase(vertexPath, fragmentPath) {
    LOG_DEBUG("Creating a new shader from '"
              << std::filesystem::absolute(vertexPath) << "', '"
              << std::filesystem::absolute(fragmentPath) << "'");

    // First up, we need to load the source from the given files into the source
    // buffers. We simply use fstreams to achieve this.
    std::string vertexSource, fragmentSource;
    std::ifstream vertexFile, fragmentFile;

    vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vertexFile.open(vertexPath);
        fragmentFile.open(fragmentPath);
        std::stringstream vertexStream, fragmentStream;

        vertexStream << vertexFile.rdbuf();
        fragmentStream << fragmentFile.rdbuf();

        vertexFile.close();
        fragmentFile.close();

        vertexSource = vertexStream.str();
        fragmentSource = fragmentStream.str();
    } catch (std::ifstream::failure e) {
        LOG_ERROR("Failed to read shader files.");
        LOG_ERROR(e.what());
    }
    // Convert to `c_str` for usage in OpenGL calls
    const char* vertexSourceC = vertexSource.c_str();
    const char* fragmentSourceC = fragmentSource.c_str();

    // Second, we need to  compile the shaders.
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // Create and compile vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexSourceC, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        LOG_ERROR("Compile", infoLog);
    }

    // Create and compile fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentSourceC, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        LOG_ERROR("Compile", infoLog);
    }

    // Third, we create te shader program and link
    programId = glCreateProgram();
    glAttachShader(programId, vertex);
    glAttachShader(programId, fragment);
    glLinkProgram(programId);

    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(programId, 512, NULL, infoLog);
        LOG_ERROR("Link", infoLog);
    }

    // Fourth, delete shaders as they're no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void OpenGLShader::use() { glUseProgram(programId); }

void OpenGLShader::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(programId, name.c_str()), (int)value);
}

void OpenGLShader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(programId, name.c_str()), value);
}

void OpenGLShader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(programId, name.c_str()), value);
}
