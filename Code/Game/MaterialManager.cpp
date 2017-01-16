#include "Game/MaterialManager.hpp"

MaterialManager* g_theMaterialManager = nullptr;

//---------------------------------------------------------------------------------------------------------------------------
//STRUCTORS
//---------------------------------------------------------------------------------------------------------------------------
MaterialManager::MaterialManager() 
	: m_defaultColorTarget(nullptr)
	, m_blurColorTarget(nullptr)
{
	Vector2 screenSize = g_theRenderer->GetScreenSize();
	m_defaultColorTarget = Texture::CreateOrGetTexture(0, (int)screenSize.x, (int)screenSize.y, eTextureFormat_RGBA8);
	m_blurColorTarget = Texture::CreateOrGetTexture(0, (int)screenSize.x, (int)screenSize.y, eTextureFormat_RGBA8);

	InitializeShaderPrograms();
	InitializeMaterials();
}
MaterialManager::~MaterialManager() {
	Texture::Delete(m_defaultColorTarget);
	Texture::Delete(m_blurColorTarget);
	ShaderProgram::DeleteShaderPrograms();

	std::map<std::string, Material*>::iterator matIt;
	for (matIt = m_materials.begin(); matIt != m_materials.end(); matIt++) {
		delete matIt->second;
		matIt->second = nullptr;
	}
}

//---------------------------------------------------------------------------------------------------------------------------
//UPDATE
//---------------------------------------------------------------------------------------------------------------------------
void MaterialManager::UpdateUniformOnMaterial(const String& materialName, Uniform* uniform) {
	ASSERT_OR_DIE(uniform != nullptr, "NULL UNIFORM PASSED IN IN UPDATEUNIFORMFORMATERIAL");

	std::map<string, Material*>::iterator matIterator = m_materials.find(materialName);

	Material* mat = matIterator->second;

	for (unsigned int i = 0; i < mat->m_uniforms.size(); i++) {
		Uniform* currUniform = mat->m_uniforms[i];

		if (currUniform->GetName() == uniform->GetName()) {
			mat->m_uniforms[i] = uniform;
		}
	}
}
void MaterialManager::UpdateUniformOnAllMaterials(Uniform* uniform) {
	std::map<string, Material*>::iterator matIterator;

	for (matIterator = m_materials.begin(); matIterator != m_materials.end(); ++matIterator) {
		Material* currMat = matIterator->second;

		for (unsigned int i = 0; i < currMat->m_uniforms.size(); i++) {
			Uniform* currUniform = currMat->m_uniforms[i];

			if (currUniform->GetName() == uniform->GetName()) {
				currMat->m_uniforms[i] = uniform;
			}
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------------
//GETTERS SETTERS
//---------------------------------------------------------------------------------------------------------------------------
Material* MaterialManager::GetMaterial(const String& materialName) {
	std::map<string, Material*>::iterator matIterator = m_materials.find(materialName);

	if (matIterator == m_materials.end()) {
		return nullptr;
	}
	else {
		return matIterator->second;
	}
}

//---------------------------------------------------------------------------------------------------------------------------
//PRIVATE MEMBER FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////
//------------------------------------------
//INIT SHADER PROGRAMS
void MaterialManager::InitializeShaderPrograms() {
	InitializeFBOShaders();
}
//---------------------------------------------------------------------------------------------------------------------------
void MaterialManager::InitializeFBOShaders() {
	ShaderProgram* defaultFBOProgram = ShaderProgram::CreateOrGetShaderProgram("DefaultFullScreen");
	
	Sampler2D defaultSampler;
	defaultSampler.AddTexture("gTexDiffuse", Texture::CreateOrGetTexture("Data/Textures/DefaultMaterial.png"));

	defaultFBOProgram->CreateUniform(defaultSampler);
	defaultFBOProgram->CreateUniform("gModel", Matrix4::IDENTITY);
	defaultFBOProgram->CreateUniform("gView", Matrix4::IDENTITY);
	defaultFBOProgram->CreateUniform("gProj", Matrix4::IDENTITY);

	ShaderProgram* blurFBOProgram = ShaderProgram::CreateOrGetShaderProgram("BlurFullScreen");
	
	Sampler2D fboSampler;
	fboSampler.AddTexture("gTexDiffuse", Texture::CreateOrGetTexture("Data/Textures/DefaultMaterial.png"));

	blurFBOProgram->CreateUniform(fboSampler);
	blurFBOProgram->CreateUniform("gModel", Matrix4::IDENTITY);
	blurFBOProgram->CreateUniform("gView", Matrix4::IDENTITY);
	blurFBOProgram->CreateUniform("gProj", Matrix4::IDENTITY);
}

////////////////////////////////////////////////////
//------------------------------------------
//INIT MATS
void MaterialManager::InitializeMaterials() {
	CreateFBOMaterial_1();
}

void MaterialManager::CreateFBOMaterial_1() {

	Material* fbo = new(MEMORY_RENDERING) Material("DefaultFullScreen");

	//Sampler
	Sampler2D fboSampler;
	fboSampler.AddTexture("gTexDiffuse", m_defaultColorTarget);
	fbo->CreateUniform(fboSampler);
	fbo->CreateUniform("gAge", 0.f);

	m_materials.insert(std::pair<string, Material*>("fbo1", fbo));
}