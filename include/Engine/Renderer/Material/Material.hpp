#pragma once

#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/Renderer/Material/Shaders/ShaderProgram.hpp"
#include "Engine/Renderer/Material/Shaders/Uniform.hpp"
#include "Engine/Renderer/Renderer/RenderState.hpp"
#include "Engine/Renderer/Light3D.hpp"
#include "Engine/Renderer/Material/Shaders/Sampler2D.hpp"
#include "Engine/Renderer/Vertex/VertexDefinition.hpp"

class Material {
public:
	//STRUCTORS
	Material();
	Material(const String& shaderName);
	~Material();

	void Clean();

	//USING MATERIAL
	void UseMaterial(const VertexDefinition& vertexDef);
	void StopUsingMaterial();

	//---------------------------------------------------------------------------------------------------------------------------
	//ADDING UNIFORMS
	//---------------------------------------------------------------------------------------------------------------------------
	void CreateUniform(const String& name, float val);
	void CreateUniform(const String& name, const Vector3& val);
	void CreateUniform(const String& name, const Vector2& val);
	void CreateUniform(const String& name, const Vector4& val);
	void CreateUniform(const String& name, const Matrix4& val);
	void CreateUniform(const String& name, int val);
	void CreateUniform(const String& name, const RGBA& val);
	void CreateUniform(const String& name, const std::vector<float>& val);
	void CreateUniform(const String& name, const std::vector<Vector3>& val);
	void CreateUniform(const String& name, const std::vector<Vector2>& val);
	void CreateUniform(const String& name, const std::vector<Vector4>& val);
	void CreateUniform(const String& name, const std::vector<Matrix4>& val);
	void CreateUniform(const String& name, const std::vector<int> val);
	void CreateUniform(const String& name, const std::vector<RGBA>& val);
	void CreateUniform(const Sampler2D& sampler);

	//UNIFORMS
	Uniform* GetUniform(const String& uniformName);
	ShaderProgram* GetShaderProgram() const { return m_shaderProgram; }
	void UpdateUniform(Uniform* newUniform);

	void CopyTextureToMaterial(Texture* texture);

public:
	std::vector<Uniform*> m_uniforms;
	String m_name;
	ShaderProgram* m_shaderProgram;
	
private:

	void OverrideUniforms();
};