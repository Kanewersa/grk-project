#include <gl.h>
#include "skybox.h"

namespace zombies {
    Skybox::Skybox() {
        skyboxShader = Shader("shaders/skybox.vs", "shaders/skybox.fs");

        glGenVertexArrays(1, &skyboxVAO);
        glGenBuffers(1, &skyboxVBO);
        glBindVertexArray(skyboxVAO);
        glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(SkyboxVertices), &SkyboxVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

        skyboxShader.use();
        skyboxShader.setInteger("skybox", 0);

        cubemap = new Cubemap({"textures/skybox/right.jpg",
                               "textures/skybox/left.jpg",
                               "textures/skybox/top.jpg",
                               "textures/skybox/bottom.jpg",
                               "textures/skybox/front.jpg",
                               "textures/skybox/back.jpg"});
    }

    Skybox::~Skybox() {
        delete cubemap;
    }

    void Skybox::draw(Camera &camera, glm::mat4 projection, LightingData *lightingData) {
        // Change depth function to fail the depth test wherever there's a different object in front of skybox.
        // This gives performance boost by not running the fragment shader for each pixel on the screen, even if it's not
        // going to be visible.
        glDepthFunc(GL_LEQUAL);
        skyboxShader.use();
        glm::mat4 view = glm::mat4(glm::mat3(camera.getViewMatrix()));
        skyboxShader.setMatrix4("view", view);
        skyboxShader.setMatrix4("projection", projection);
        skyboxShader.setVector3f("fogColor", lightingData->fogColor.x, lightingData->fogColor.y, lightingData->fogColor.z);
        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap->getTexture());
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        // Restore depth function to default
        glDepthFunc(GL_LESS);
    }
}

