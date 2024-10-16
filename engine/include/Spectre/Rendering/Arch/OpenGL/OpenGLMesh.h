#ifndef OPENGLMESH_H
#define OPENGLMESH_H

#include "Spectre/Rendering/MeshBase.h"
#include "sppch.h"

namespace Spectre {
/**
 * @brief OpenGL implementation of the MeshBase.
 *
 * Uses the OpenGL API to handle mesh creation and binding.
 */
class OpenGLMesh : MeshBase {
    public:
        /**
         * @brief Creates a new OpenGLMesh.
         *
         * This constructor will create a new OpenGLMesh, with the neccessary
         * API calls for things like creation a VAO, VBO and EBO.
         *
         * @param vertices Vertices for this mesh.
         * @param indices Indices for this mesh.
         */
        OpenGLMesh(std::vector<Vertex> vertices, std::vector<int> indices);

        /**
         * @brief Bind the GPU-specfic objects.
         */
        void bind() const override;

    private:
        /**
         * @brief Vertex Array Object for this mesh.
         */
        unsigned int vao;

        /**
         * @brief Vertex Buffer Object for this mesh.
         */
        unsigned int vbo;

        /**
         * @brief Element Buffer Object for this mesh.
         */
        unsigned int ebo;
};
}  // namespace Spectre

#endif  // OPENGLMESH_H