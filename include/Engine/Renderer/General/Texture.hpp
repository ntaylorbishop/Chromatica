#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gl/gl.h>
#include <string>
#include <map>
#include <functional>

#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/General/Core/Memory/UntrackedAllocator.hpp"
#include "Engine/Renderer/OpenGL/OpenGLExtensions.hpp"
#include "Engine/Math/IntVector2.hpp"

enum eTextureFormat {
	eTextureFormat_RGBA8,
	eTextureFormat_D24S8,
};

using namespace std;
class Texture {
public:
	static Texture* Texture::CreateOrGetTexture(int blankTextureID, int width, int height, eTextureFormat format);
	static Texture* Texture::CreateOrGetTexture(const string& imageFilePath);
	static Texture* Texture::GetTextureByName(const string& imageFilePath);
	static void Texture::DeinitTextures();
	static void Texture::Delete(Texture* texture) { delete texture; }

	int GetTextureID() const;

	int GetHeight() const;
	int GetWidth() const;
	
private:
	//TODO: Fix this, it leaks memory
	Texture(int width, int height, eTextureFormat format);
	Texture(const string& imageFilePath);
	~Texture() { }

	static map<size_t, Texture*, std::less<size_t>, UntrackedAllocator<std::pair<size_t, Texture*>>> s_textureRegistry;
	static map<int, Texture*, std::less<int>, UntrackedAllocator<std::pair<const int, Texture*>>> s_blankTextureRegistry;

	GLuint m_openglTextureID;
	String m_name;
	IntVector2 m_texelSize;
};
