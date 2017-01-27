#pragma once

#include "Engine/Renderer/Material/Material.hpp"
#include "Engine/Renderer/Mesh/Mesh.hpp"

class MeshRenderer {
public:
	//STRUCTORS
	MeshRenderer();

	//UPDATE RENDER
	void RenderMeshWithMaterial(const Mesh& mesh, const Material* mat) const;

	//---------------------------------------------------------------------------------------------------------------------------
	//ADDING UNIFORMS
	//---------------------------------------------------------------------------------------------------------------------------
	void CreateUniform(Material* mat, const String& name, float val);
	void CreateUniform(Material* mat, const String& name, const Vector3& val);
	void CreateUniform(Material* mat, const String& name, const Vector2& val);
	void CreateUniform(Material* mat, const String& name, const Vector4& val);
	void CreateUniform(Material* mat, const String& name, const Matrix4& val);
	void CreateUniform(Material* mat, const String& name, int val);
	void CreateUniform(Material* mat, const String& name, const RGBA& val);
	void CreateUniform(Material* mat, const String& name, const std::vector<float>& val);
	void CreateUniform(Material* mat, const String& name, const std::vector<Vector3>& val);
	void CreateUniform(Material* mat, const String& name, const std::vector<Vector2>& val);
	void CreateUniform(Material* mat, const String& name, const std::vector<Vector4>& val);
	void CreateUniform(Material* mat, const String& name, const std::vector<Matrix4>& val);
	void CreateUniform(Material* mat, const String& name, const std::vector<int> val);
	void CreateUniform(Material* mat, const String& name, const std::vector<RGBA>& val);
	void CreateUniform(Material* mat, const Sampler2D& sampler);

	//UNIFORMS
	Uniform* GetUniform(const String& uniformName);
	void UpdateUniform(Uniform* newUniform);

private:
	void UpdateModelUnifomInShaderProgram(const Mesh& mesh, Material* mat) const;
	void OverrideUniforms(const Material* mat) const;
	
private:
	int m_vaoID;

	std::vector<Uniform*> m_uniforms;

};