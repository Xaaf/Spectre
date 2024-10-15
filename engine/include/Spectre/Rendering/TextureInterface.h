#ifndef TEXTUREINTERFACE_H
#define TEXTUREINTERFACE_H

#include "sppch.h"

namespace Spectre {
/**
 * @brief Holds abstract methods related to a basic texture instance.
 *
 * Provides the basic structure of a texture. More importantly, each texture
 * needs at least the functions contained in this interface to be viable for use
 * in a renderer in the engine.
 */
class TextureInterface {
    public:
        /**
         * @brief Destroy the texture object.
         */
        virtual ~TextureInterface() = default;

        /**
         * @brief Binds this texture to be the current active texture..
         */
        virtual void bind() = 0;

        /**
         * @brief Unbinds this texture.
         */
        virtual void unbind() = 0;

    protected:
        /**
         * @brief Filepath of the texture to load.
         */
        std::string texturePath;
};
}  // namespace Spectre

#endif  // TEXTUREINTERFACE_H