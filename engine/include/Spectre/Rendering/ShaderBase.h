#ifndef SHADERBASE_H
#define SHADERBASE_H

#include "sppch.h"

namespace Spectre {
/**
 * @brief Holds abstract methods related to a basic shader instance.
 *
 * Provides the basic structure of a shader. More importantly, each shader needs
 * at least the functions contained in this interface to be viable for use in a
 * renderer in the engine.
 */
class ShaderBase {
    public:
        /**
         * @brief Construct a new shader object.
         *
         * Constructs a new instance of a shader object on the given
         * implementation. This constructor also serves as an initialisation
         * point for shaders, e.g. loading the source from the shader files.
         *
         * @param vertexPath Path to the vertex shader source.
         * @param fragmentPath Path to the fragment shader source.
         */
        ShaderBase(const std::string& vertexPath,
                   const std::string& fragmentPath) {};

        /**
         * @brief Destroy the shader object.
         */
        virtual ~ShaderBase() = default;

        /**
         * @brief Activate this shader.
         */
        virtual void use() = 0;

        /**
         * @brief Set the boolean value for a given attribute.
         *
         * @param name Name of the attribute who's value to change.
         * @param value New value for the attribute.
         */
        virtual void setBool(const std::string& name, bool value) const = 0;

        /**
         * @brief Set the integer value for a given attribute.
         *
         * @param name Name of the attribute who's value to change.
         * @param value New value for the attribute.
         */
        virtual void setInt(const std::string& name, int value) const = 0;

        /**
         * @brief Set the float value for a given attribute.
         *
         * @param name Name of the attribute who's value to change.
         * @param value New value for the attribute.
         */
        virtual void setFloat(const std::string& name, float value) const = 0;

    protected:
        /**
         * @brief Path to the vertex shader source.
         */
        std::string vertexPath;

        /**
         * @brief Path to the fragment shader source.
         */
        std::string fragmentPath;
};
}  // namespace Spectre

#endif  // SHADERBASE_H