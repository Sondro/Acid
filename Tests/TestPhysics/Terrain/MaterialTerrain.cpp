#include "MaterialTerrain.hpp"

#include <Maths/Transform.hpp>

namespace test {
bool MaterialTerrain::registered = Register("terrain");

MaterialTerrain::MaterialTerrain(std::shared_ptr<Image2d> imageR, std::shared_ptr<Image2d> imageG) :
	m_imageR(std::move(imageR)),
	m_imageG(std::move(imageG)) {
}

void MaterialTerrain::CreatePipeline(const Shader::VertexInput &vertexInput, bool animated) {
	m_pipelineMaterial = PipelineMaterial::Create({1, 0}, {{"Shaders/Terrains/Terrain.vert", "Shaders/Terrains/Terrain.frag"}, {vertexInput}});
}

void MaterialTerrain::PushUniforms(UniformHandler &uniformObject, const Transform *transform) {
	if (transform)
		uniformObject.Push("transform", transform->GetWorldMatrix());
}

void MaterialTerrain::PushDescriptors(DescriptorsHandler &descriptorSet) {
	descriptorSet.Push("samplerR", m_imageR);
	descriptorSet.Push("samplerG", m_imageG);
}

const Node &operator>>(const Node &node, MaterialTerrain &material) {
	node["imageR"].Get(material.m_imageR);
	node["imageG"].Get(material.m_imageG);
	return node;
}

Node &operator<<(Node &node, const MaterialTerrain &material) {
	node["imageR"].Set(material.m_imageR);
	node["imageG"].Set(material.m_imageG);
	return node;
}
}
