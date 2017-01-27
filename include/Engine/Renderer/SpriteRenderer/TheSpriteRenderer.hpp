#pragma once

#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/Math/MathUtils.hpp"
#include "Engine/Renderer/Camera2D.hpp"
#include "Engine/Renderer/Mesh/MeshRenderer.hpp"
#include "Engine/Renderer/SpriteRenderer/SpriteLayer.hpp"
#include "Engine/Renderer/SpriteRenderer/SpriteResource.hpp"

class TheSpriteRenderer;
extern TheSpriteRenderer* g_theSpriteRenderer;

class TheSpriteRenderer {
public:
	//INIT
	static void Initialize(float virtualSize, float aspectRatio);
	static void RegisterSpriteRendererCommands();
	static void Destroy();

	static void RegisterSprite(Sprite* sprite);
	static void UnregisterSprite(Sprite* sprite);

	static void CreateLayer(const String& layer);

	//UPDATE RENDER
	static void Update(float deltaSeconds) { s_theSpriteRenderer->Update(deltaSeconds); }
	static void Render(const Camera2D& cam) { s_theSpriteRenderer->UpdateViewAndRender(cam); }
	static void Render() { s_theSpriteRenderer->InternalRender(); }


	//GETTERS SETTERS
	static AABB2 GetRect() { return s_theSpriteRenderer->m_virtualRect; }
	static void SetImportSize(float importSize) { s_theSpriteRenderer->InternalSetImportSize(importSize); }
	static Vector2 GetBounds() { return s_theSpriteRenderer->m_virtualBounds; }
	static void SetClearColor(const RGBA& col) { g_theRenderer->ClearScreen(col); }
	static Material* GetDefaultMaterial() { return s_theSpriteRenderer->m_defaultMaterial; }
	static float GetImportSize() { return s_theSpriteRenderer->m_importSize; }
	static float GetVirtualSize() { return s_theSpriteRenderer->m_virtualSize; }

	//LAYER EFFECTS
	static void AddLayerEffect(const String& layerName, const String& shaderProgName) { s_theSpriteRenderer->InternalAddLayerEffect(layerName, shaderProgName); }
	static void EnableLayer(const String& layerName);
	static void DisableLayer(const String& layerName);

	//CAMERA
	static void UpdateCamera(const Camera2D& cam);

private:
	//STRUCTORS
	TheSpriteRenderer(float virtualSize, float aspectRatio);
	~TheSpriteRenderer();

	void InitializeDefaultShaders();
	void InternalSetImportSize(float importSize);

	//UPDATE
	void InternalUpdate(float deltaSeconds);

	//RENDER
	void UpdateViewAndRender(const Camera2D& cam);
	void InternalRender();
	void RenderLayer(SpriteLayer* currLayer);
	void DrawSprite(Sprite* sprite);

	Vector2 InternalGetBounds() const { return m_virtualBounds; }
	Material* InternalGetDefaultMaterial() { return m_defaultMaterial; }
	float InternalGetImportSize() { return m_importSize; }

	static void CopyToMesh(Sprite* sprite);
	bool Cull(Sprite* s) const;

	//LAYER EFFECTS
	void InternalAddLayerEffect(const String& layerName, const String& shaderProgName);
	void RenderFullScreenQuad(Material* mat);
	SpriteLayer* GetLayer(const String& name);

	//CAMERA
	void UpdateViewMatrix(const Camera2D& cam);
	void UpdateViewInMaterial(Material* mat) const;
	
	
	////////////////////////////////////////////////////
	//------------------------------------------
	//MEMBERS VARS
	MeshRenderer m_meshRenderer;
	Material* m_defaultMaterial;

	std::vector<SpriteLayer*> m_layers;
	float m_virtualSize;
	Vector2 m_virtualBounds;
	float m_aspectRatio;
	Matrix4 m_ortho;
	float m_importSize;
	AABB2 m_virtualRect;
	std::vector<Sprite*> m_sprites;
	Matrix4 m_view;

	Framebuffer* m_currentSurface;
	Framebuffer* m_effectSurface;

	Texture* m_currentColorTarget;
	Texture* m_effectColorTarget;

	////////////////////////////////////////////////////
	//------------------------------------------
	//STATIC MEMBER VARS
	static TheSpriteRenderer* s_theSpriteRenderer;
	static Mesh* s_mesh;
	static Mesh* s_fullScreenMesh;
};

//CONSOLE COMMANDS
void LayerToggle(Command& args);