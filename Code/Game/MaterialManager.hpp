#pragma once

#include "Engine/Renderer/Material/Material.hpp"

class MaterialManager;
extern MaterialManager* g_theMaterialManager;

const RGBA MATERIAL_AMBIENT_LIGHT = RGBA(1.f, 1.f, 1.f, 0.f);
const float MATERIAL_SPEC_POWER = 64.f;
const float MATERIAL_MIN_FOG_DISTANCE = 10.f;
const float MATERIAL_MAX_FOG_DISTANCE = 20.f;
const RGBA MATERIAL_FOG_COLOR = RGBA(1.f, 0.f, 0.f, 1.f);

class MaterialManager {
public:
	//STRUCTORS
	MaterialManager();
	~MaterialManager();

	//UPDATE
	void UpdateUniformOnMaterial(const String& materialName, Uniform* uniform);
	void UpdateUniformOnAllMaterials(Uniform* uniform);

	//GETTERS SETTERS
	Material* GetMaterial(const String& materialName);

private:
	void InitializeShaderPrograms();
	void InitializeFBOShaders();

	void InitializeMaterials();

	void CreateFBOMaterial_1();

	Texture* m_defaultColorTarget;
	Texture* m_blurColorTarget;

private:
	std::map<String, Material*> m_materials;
};