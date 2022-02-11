#include <gl.h>
#include <stdexcept>
#include "texture_render_target.h"
#include "texture.h"

namespace zombies {

    TextureRenderTarget::TextureRenderTarget(int width, int height) : Texture(width, height) {
        glGenFramebuffers(1, &FBO);

        glBindFramebuffer(GL_FRAMEBUFFER, FBO);

        // Attach texture to framebuffer
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, getGLTexture(), 0);

        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            throw std::runtime_error("Could not create Framebuffer object.");
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    TextureRenderTarget::~TextureRenderTarget() {
        glDeleteFramebuffers(1, &FBO);
    }

    void TextureRenderTarget::bind() {
        glClearColor(0.4f, 0.2f, 0.3f, 1.0f);

        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void TextureRenderTarget::reallocateTexture(int newWidth, int newHeight) {
        width = newWidth;
        height = newHeight;

        glBindTexture(GL_TEXTURE_2D, getGLTexture());

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

        glBindTexture(GL_TEXTURE_2D, 0);
    }
}