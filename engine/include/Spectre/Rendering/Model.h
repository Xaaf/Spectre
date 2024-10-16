#ifndef MODEL_H
#define MODEL_H

#include "sppch.h"
#include "Spectre/Rendering/MeshBase.h"
#include "Spectre/Rendering/ShaderBase.h"
#include "Spectre/Rendering/TextureBase.h"

namespace Spectre {
/**
 * @brief Holds an instance of a model.
 *
 * In Spectre, a model is an object in 3D-space with a mesh, a texture and a
 * shader. These models can then be used further for rendering, GameObject
 * creation, or other purposes.
 */
class Model {
    private:
        /**
         * @brief Reference to the model's mesh.
         */
        std::shared_ptr<MeshBase> mesh;

        /**
         * @brief Texture of the model.
         */
        std::unique_ptr<TextureBase> texture;

        /**
         * @brief Shader of the model.
         */
        std::unique_ptr<ShaderBase> shader;

    public:
        /**
         * @brief Construct a new model insance.
         *
         * Creates a new Model instance with the given mesh, texture and shader.
         * This model can then be used in rendering and the like.
         *
         * @param mesh Mesh reference for the model.
         * @param texture Texture for the model.
         * @param shader Shader for the model.
         */
        Model(std::shared_ptr<MeshBase> mesh,
              std::unique_ptr<TextureBase> texture,
              std::unique_ptr<ShaderBase> shader);

        /**
         * @brief Get the mesh for this model.
         *
         * @return Reference to the mesh.
         */
        std::shared_ptr<MeshBase> getMesh() const { return mesh; }

        /**
         * @brief Get the texture for this model.
         *
         * @return `TextureBase` instance.
         */
        TextureBase* getTexture() const { return texture.get(); }

        /**
         * @brief Get the shader for this model.
         *
         * @return `ShaderBase` instance.
         */
        ShaderBase* getShader() const { return shader.get(); }
};
}  // namespace Spectre

#endif  // MODEL_H