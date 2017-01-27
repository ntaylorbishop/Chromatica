#pragma once

#include "Engine/General.hpp"
#include "Engine/Renderer.hpp"

class Framebuffer {
public:

	//STRUCTORS INITIALIZATION
	Framebuffer();
	Framebuffer(int width, int height, vector<eTextureFormat> color_formats, eTextureFormat depth_stencil_format);
	Framebuffer(std::vector<Texture*> colors, size_t color_count, Texture* depth_stencil_target);
	Framebuffer(std::vector<Texture*> colors, size_t color_count);

	//GETTERS SETTERS
	//GETTERS SETTERS
	int GetPixelWidth() const { return m_pixelWidth; }
	int GetPixelHeight() const { return m_pixelHeight; }
	uint GetFBOHandle() const { return m_fboHandle; }
	int GetColorCount() const { return m_colorTargets.size(); }
	Texture* GetColorTexture() const { 
		return m_colorTargets[0]; 
	}
	Texture* GetDepthTexture() const { return m_depthStencilTarget; }

private:
	uint32_t m_fboHandle;

	std::vector<Texture*> m_colorTargets;
	Texture* m_depthStencilTarget;

	int m_pixelWidth;
	int m_pixelHeight;
};