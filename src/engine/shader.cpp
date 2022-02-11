#include "shader.h"
#include <gl.h>

namespace zombies {

    Shader::Shader(const char* vertexPath, const char* fragmentPath) {
        std::string vertexCode;
        std::string fragmentCode;

        try {
            std::ifstream vertexShaderFile(vertexPath);
            std::ifstream fragmentShaderFile(fragmentPath);

            if (!vertexShaderFile.good())
            {
                throw std::runtime_error("Shader file is missing.");
            }

            vertexCode = std::string((std::istreambuf_iterator<char>(vertexShaderFile)),
                std::istreambuf_iterator<char>());

            fragmentCode = std::string((std::istreambuf_iterator<char>(fragmentShaderFile)),
                std::istreambuf_iterator<char>());
        }
        catch (std::ifstream::failure& e) {
            std::cout << "Could not read spriteShader file.\n" << vertexPath << std::endl;
        }

        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        // Compile shaders
        unsigned int vertex, fragment;

        // SpriteBatchVertex
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, nullptr);
        glCompileShader(vertex);
        checkCompilationErrors(vertex, GL_VERTEX_SHADER);

        // Fragment
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, nullptr);
        glCompileShader(fragment);
        checkCompilationErrors(fragment, GL_FRAGMENT_SHADER);

        // Shader program
        programId = glCreateProgram();

        // Add attributes
        glBindAttribLocation(programId, 0, "vertexPosition");
        glBindAttribLocation(programId, 1, "vertexColor");
        glBindAttribLocation(programId, 2, "vertexUV");

        glAttachShader(programId, vertex);
        glAttachShader(programId, fragment);
        glLinkProgram(programId);
        checkCompilationErrors(programId, GL_CURRENT_PROGRAM);

        // Delete shaders as they are no longer needed
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void Shader::use() const {
        glUseProgram(programId);
    }

    void Shader::checkCompilationErrors(unsigned int shader, int type) {
        int success;
        char infoLog[1024];
        if (type == GL_CURRENT_PROGRAM) {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (success != 1) {
                glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
                std::stringstream ss;
                ss << "Could not link shaders to the program.\n" << infoLog << std::endl;
                throw std::runtime_error(ss.str());
            }
        }
        else {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (success != 1) {
                glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
                std::stringstream ss;
                ss << "Could not compile spriteShader of type " << type << " to the program.\n" << infoLog << std::endl;
                throw std::runtime_error(ss.str());
            }
        }
    }
}
