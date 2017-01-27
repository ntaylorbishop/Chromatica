#pragma once

#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/Renderer/Framebuffer.hpp"
#include "Engine/Renderer/Material/Material.hpp"
#include "Engine/Renderer/Mesh/Mesh.hpp"
#include "Engine/Renderer/Mesh/MeshRenderer.hpp"

//NOTE: DOES NOT RENDER WITH DEPTH

class FramebufferObject {
public:
	//STRUCTORS INIT
	FramebufferObject();
	FramebufferObject(const String& shaderProgName);
	~FramebufferObject();

	//BIND RENDER
	void Bind() const;
	void Render() const;
	void Render(Material* mat) const;
	void CopyToBack() const;

	//GETTERS SETTERS
	String GetName() const { return m_name; }
	Texture* GetColorTexture() const { return m_fbo.GetColorTexture(); }
	void SetColorTexture(Texture* texture);
	void SetMaterialTexture(Material* mat);
	Material* GetMaterial() { return m_material; }

private:
	void InitializeMeshAndMaterial();
	void InitializeFramebuffer();

	Framebuffer m_fbo;
	Material* m_material;
	Mesh m_mesh;
	MeshRenderer m_meshRenderer;
	String m_name;
	Texture* m_colorTarget;
};

