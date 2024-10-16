#ifndef OPENGLTEXTURE_H
#define OPENGLTEXTURE_H

#include "Spectre/Rendering/TextureBase.h"
#include "sppch.h"

namespace Spectre {
/**
 * @brief OpenGL implementation of the TextureBase.
 *
 * Uses the OpenGL API to handle texture creation, loading and binding.
 */
class OpenGLTexture : TextureBase {
    private:
        /**
         * @brief Width of the texture in pixels.
         */
        int width;

        /**
         * @brief Height of the texture in pixels.
         */
        int height;

        /**
         * @brief Number of channels in the texture.
         */
        int channels;

        /**
         * @brief Data of the texture after it has been loaded.
         */
        unsigned char* data;

        /**
         * @brief ID of the texture.
         */
        unsigned int id;

    public:
        OpenGLTexture(const std::string& texturePath);

        ~OpenGLTexture();

        void bind() override;
        void unbind() override;
};
}  // namespace Spectre

#endif  // OPENGLTEXTURE_H