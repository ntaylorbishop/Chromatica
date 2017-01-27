#pragma once

#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/Renderer/Mesh/MeshRenderer.hpp"
#include "Engine/Renderer/Animation/Skeleton.hpp"

class Model {
public:
	//STRUCTORS
	Model();

	void Update(float deltaSeconds);
	void Render();

	//LOADING
	void Load(const String& fileName);

private:
	std::vector<MeshRenderer> m_meshRenderers;
	std::vector<Mesh> m_meshes;
	std::vector<Material*> m_materials;

	Skeleton* m_skeleton;
};