#ifndef OPENGLSHADER_H
#define OPENGLSHADER_H

#include <fstream>
#include "Spectre/Rendering/ShaderBase.h"
#include "sppch.h"

namespace Spectre {
/**
 * @brief OpenGL implementation of the ShaderBase.
 *
 * Uses the OpenGL API to handle shader creation, compilation and usage.
 */
class OpenGLShader : public ShaderBase {
    private:
        /**
         * @brief ID of the shader program associated with this shader.
         */
        unsigned int programId;

    public:
        /**
         * @brief Construct a new shader object.
         *
         * Constructs a new instance of a shader object using OpenGL. This
         * constructor also serves as an initialisation point for shaders, e.g.
         * loading the source from the shader files.
         *
         * @param vertexPath Path to the vertex shader source.
         * @param fragmentPath Path to the fragment shader source.
         */
        OpenGLShader(const std::string& vertexPath,
                     const std::string& fragmentPath);

        /**
         * @brief Activate this shader.
         */
        void use() override;

        /**
         * @brief Set the boolean value for a given attribute.
         *
         * @param name Name of the attribute who's value to change.
         * @param value New value for the attribute.
         */
        void setBool(const std::string& name, bool value) const override;

        /**
         * @brief Set the integer value for a given attribute.
         *
         * @param name Name of the attribute who's value to change.
         * @param value New value for the attribute.
         */
        void setInt(const std::string& name, int value) const override;

        /**
         * @brief Set the float value for a given attribute.
         *
         * @param name Name of the attribute who's value to change.
         * @param value New value for the attribute.
         */
        void setFloat(const std::string& name, float value) const override;
};
}  // namespace Spectre

#endif  // OPENGLSHADER_H