#include "Spectre/Rendering/Model.h"

using namespace Spectre;

Model::Model(MeshBase* mesh, TextureBase* texture, ShaderBase* shader,
             std::string debugName)
    : mesh(mesh), texture(texture), shader(shader), debugName(debugName) {}

Model::~Model() {
    delete mesh;
    delete texture;
    delete shader;
}