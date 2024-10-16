#include "Spectre/Rendering/Model.h"

using namespace Spectre;

Model::Model(std::shared_ptr<MeshBase> mesh,
             std::unique_ptr<TextureBase> texture,
             std::unique_ptr<ShaderBase> shader)
    : mesh(mesh), texture(std::move(texture)), shader(std::move(shader)) {}
