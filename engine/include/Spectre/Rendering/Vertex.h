#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>
#include "sppch.h"

namespace Spectre {
/**
 * @brief Structure holding information relevant to a singular vertex.
 */
struct Vertex {
        /**
         * @brief Position of the vertex in 3D space (x, y, z).
         */
        glm::vec3 position;

        /**
         * @brief Colour value of this vertex (r, g, b).
         */
        glm::vec3 colour;
};
}  // namespace Spectre

#endif  // VERTEX_H