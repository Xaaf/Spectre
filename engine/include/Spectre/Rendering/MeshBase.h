#ifndef MESHBASE_H
#define MESHBASE_H

#include "sppch.h"
#include "Spectre/Rendering/Vertex.h"

namespace Spectre {
/**
 * @brief Holds abstract methods related to a basic mesh instance.
 *
 * Provides the basic structure of a mesh. More importantly, each mesh needs at
 * least the function contained in this interface to be viable for use in the
 * engine's renderers.
 */
class MeshBase {
    public:
        /**
         * @brief Destroy the mesh object.
         */
        virtual ~MeshBase() = default;

        /**
         * @brief Bind the GPU-specfic objects.
         */
        virtual void bind() const = 0;

    protected:
        /**
         * @brief List of the vertices a mesh has.
         */
        std::vector<Vertex> vertices;

        /**
         * @brief List of the indices a mesh has.
         */
        std::vector<int> indices;
};
}  // namespace Spectre

#endif  // MESHBASE_H