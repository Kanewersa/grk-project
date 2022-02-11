#pragma once

#include "gl.h"
#include "GLFW/glfw3.h"

namespace zombies {
    class WaterFrameBuffers {
    public:
        const int REFLECTION_WIDTH = 320;
        const int REFLECTION_HEIGHT = 180;

        const int REFRACTION_WIDTH = 1280;
        const int REFRACTION_HEIGHT = 720;

        WaterFrameBuffers() {
            reflectionFrameBuffer = createFrameBuffer();
            refractionFrameBuffer = createFrameBuffer();
            reflectionTexture = createTextureAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
            refractionTexture = createTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
            reflectionDepthBuffer = createDepthBufferAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
            refractionDepthBuffer = createDepthTextureAttachment(REFRACTION_WIDTH, REFLECTION_HEIGHT);
        }

        ~WaterFrameBuffers() {
            glDeleteFramebuffers(1, &refractionFrameBuffer);
            glDeleteFramebuffers(1, &reflectionDepthBuffer);
            glDeleteRenderbuffers(1, &refractionDepthBuffer);
            glDeleteRenderbuffers(1, &reflectionDepthBuffer);
            glDeleteTextures(1, &refractionTexture);
            glDeleteTextures(1, &reflectionTexture);
        }

        GLuint getReflectionTexture() const {
            return reflectionTexture;
        }

        GLuint getRefractionTexture() const {
            return refractionTexture;
        }

        void bindRefractionFrameBuffer() {
            bindFrameBuffer(refractionFrameBuffer, REFRACTION_WIDTH, REFRACTION_HEIGHT);
        }

        void bindReflectionFrameBuffer() {
            bindFrameBuffer(reflectionFrameBuffer, REFLECTION_WIDTH, REFLECTION_HEIGHT);
        }

        void unbindWaterFrameBuffer(GLFWwindow* window) {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            int width, height;
            glfwGetWindowSize(window, &width, &height);
            glViewport(0, 0, width, height);
        }

    private:
        GLuint createFrameBuffer() {
            GLuint newFBO;
            glGenFramebuffers(1, &newFBO);
            glBindFramebuffer(GL_FRAMEBUFFER, newFBO);
            glDrawBuffer(GL_COLOR_ATTACHMENT0);
            return newFBO;
        }

        GLuint createTextureAttachment(int width, int height) {
            GLuint textureId;
            glGenTextures(1, &textureId);
            glBindTexture(GL_TEXTURE_2D, textureId);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureId, 0);

            return textureId;
        }

        GLuint createDepthTextureAttachment(int width, int height) {
            GLuint depthTextureId;
            glGenTextures(1, &depthTextureId);
            glBindTexture(GL_TEXTURE_2D, depthTextureId);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTextureId, 0);

            return depthTextureId;
        }

        GLuint createDepthBufferAttachment(int width, int height) {
            GLuint depthBufferId;

            glGenRenderbuffers(1, &depthBufferId);
            glBindRenderbuffer(GL_RENDERBUFFER, depthBufferId);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBufferId);

            return depthBufferId;
        }

        void bindFrameBuffer(GLuint frameBuffer, int width, int height) {
            // Make sure no textures is bound
            glBindTexture(GL_TEXTURE_2D, 0);

            glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
            glViewport(0, 0, width, height);
        }

        GLuint refractionFrameBuffer;
        GLuint refractionTexture;
        GLuint refractionDepthBuffer;

        GLuint reflectionFrameBuffer;
        GLuint reflectionTexture;
        GLuint reflectionDepthBuffer;
    };
}