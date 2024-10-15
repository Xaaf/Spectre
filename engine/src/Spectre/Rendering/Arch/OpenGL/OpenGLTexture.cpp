#include "Spectre/Rendering/Arch/OpenGL/OpenGLTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace Spectre;

OpenGLTexture::OpenGLTexture(const std::string& texturePath) {
    this->texturePath = texturePath;

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    // Set the texture filtering on the currently bound object
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // By default, stbi seems to flip the textures, so this counter-acts that
    stbi_set_flip_vertically_on_load(true);
    // Load the actual texture data
    data = stbi_load(texturePath.c_str(), &width, &height, &channels, 0);

    if (!data) {
        LOG_ERROR("Failed to load texture from '" << texturePath << "'!");
        return;
    }

    // Generate the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    // Generate the mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

OpenGLTexture::~OpenGLTexture() { glDeleteTextures(1, &id); }

void OpenGLTexture::bind() { glBindTexture(GL_TEXTURE_2D, id); }

void OpenGLTexture::unbind() { glBindTexture(GL_TEXTURE_2D, 0); }
