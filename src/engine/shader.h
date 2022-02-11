#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <gl.h>
#include <glm/gtc/type_ptr.hpp>

namespace zombies {
    class Shader {
    public:
        Shader() = default;

        Shader(const char* vertexPath, const char* fragmentPath);

        void use() const;

        unsigned int getProgramId() const { return programId; }

        void setBool(const char* name, bool value, bool useShader = false) const {
            glUniform1i(glGetUniformLocation(programId, name), value ? 1 : 0);
        }

        void setFloat(const char* name, float value, bool useShader = false) const {
            glUniform1f(glGetUniformLocation(programId, name), value);
        }

        void setInteger(const char* name, int value, bool useShader = false) const {
            glUniform1i(glGetUniformLocation(programId, name), value);
        }

        void setVector2f(const char* name, float x, float y, bool useShader = false) const {
            glUniform2f(glGetUniformLocation(programId, name), x, y);
        }

        void setVector2f(const char* name, const glm::vec2& value, bool useShader = false) const {
            glUniform2f(glGetUniformLocation(programId, name), value.x, value.y);
        }

        void setVector3f(const char* name, float x, float y, float z, bool useShader = false) const {
            glUniform3f(glGetUniformLocation(programId, name), x, y, z);
        }

        void setVector3f(const char* name, const glm::vec3& value, bool useShader = false) const {
            glUniform3f(glGetUniformLocation(programId, name), value.x, value.y, value.z);
        }

        void setVector4f(const char* name, float x, float y, float z, float w, bool useShader = false) const {
            glUniform4f(glGetUniformLocation(programId, name), x, y, z, w);
        }

        void setVector4f(const char* name, const glm::vec4& value, bool useShader = false) const {
            glUniform4f(glGetUniformLocation(programId, name), value.x, value.y, value.z, value.w);
        }

        void setMatrix3(const char* name, const glm::mat3& matrix, bool useShader = false) const {
            glUniformMatrix3fv(glGetUniformLocation(programId, name), 1, false, glm::value_ptr(matrix));
        }

        void setMatrix4(const char* name, const glm::mat4& matrix, bool useShader = false) const {
            glUniformMatrix4fv(glGetUniformLocation(programId, name), 1, false, glm::value_ptr(matrix));
        }

    private:
        unsigned int programId{};

        static void checkCompilationErrors(unsigned int shader, int type);
    };
}

