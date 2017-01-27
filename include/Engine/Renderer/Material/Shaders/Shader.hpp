#pragma once

#include <string>
#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/Renderer/Renderer/TheRenderer.hpp"
#include "Engine/General/Utils/FileUtils.hpp"



class Shader {
public:
	//STRUCTORS
	Shader();
	Shader(const String& fileName, eShaderType type);
	~Shader();

	//LOADING
	void Load();
	void Delete();

	//GETTERS SETTERS
	String GetFileName();
	eShaderType GetShaderType();
	int GetShaderID();

private:
	int GetShaderTypeEnum();

private:
	int m_shaderID;
	String m_fileName;
	eShaderType m_type;
};