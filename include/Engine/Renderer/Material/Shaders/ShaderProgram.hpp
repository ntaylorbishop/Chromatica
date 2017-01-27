#pragma once

#include <functional>

#include "Engine/Renderer/Material/Shaders/Uniform.hpp"
#include "Engine/Renderer/Material/Shaders/Shader.hpp"
#include "Engine/Renderer/Vertex/VertexDefinition.hpp"

class ShaderProgram {
public:
	static ShaderProgram* ShaderProgram::CreateOrGetShaderProgram(const String& shaderProgName);
	static void ShaderProgram::DeleteShaderPrograms();

	void UseProgram() const;

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

	Uniform* GetUniform(const String& name);


	void BindAttributes(const VertexDefinition& vertexDef) const;
	void BindUniforms() const;

	int GetProgramID() const { return m_programID; }

private:
	//Private member functions
	//void GetAllActiveUniformsInShaders();

private:
	//STRUCTORS
	ShaderProgram();
	ShaderProgram(const Shader& vShader, const Shader& fShader);
	~ShaderProgram();


	static std::map<size_t, ShaderProgram*, std::less<size_t>, UntrackedAllocator<std::pair<size_t, ShaderProgram*>>> s_shaderProgramRegistry;

	int m_programID;
	Shader m_vertexShader;
	Shader m_fragmentShader;

	std::map<String, Uniform*> m_uniforms;
};

typedef std::map<size_t, ShaderProgram*, std::less<size_t>, UntrackedAllocator<std::pair<size_t, ShaderProgram*>>> ShaderProgramMap;
typedef std::map<size_t, ShaderProgram*, std::less<size_t>, UntrackedAllocator<std::pair<size_t, ShaderProgram*>>>::iterator ShaderProgramMapIter;
typedef std::pair<size_t, ShaderProgram*> ShaderProgramMapPair;
typedef std::map<String, Uniform*>::iterator ShaderProgramUniformMapIter;