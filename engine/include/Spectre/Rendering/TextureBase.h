#ifndef TEXTUREBASE_H
#define TEXTUREBASE_H

#include "sppch.h"

namespace Spectre {
/**
 * @brief Holds abstract methods related to a basic texture instance.
 *
 * Provides the basic structure of a texture. More importantly, each texture
 * needs at least the functions contained in this interface to be viable for use
 * in a renderer in the engine.
 */
class TextureBase {
    public:
        /**
         * @brief Destroy the texture object.
         */
        virtual ~TextureBase() = default;

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

#endif  // TEXTUREBASE_H