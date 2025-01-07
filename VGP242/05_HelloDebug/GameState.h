#pragma once
#include <ENgines/Inc/ENgines.h>

class GameState : public ENgines::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Render() override;
	void DebugUI() override;

	void Update(float deltaTime);
protected:
	void UpdateCamera(float deltaTime);

	ENgines::Graphics::Camera mCamera;
	ENgines::Graphics::ConstantBuffer mConstantBuffer;
	ENgines::Graphics::MeshBuffer mMeshBuffer;
	ENgines::Graphics::VertexShader mVertexShader;
	ENgines::Graphics::PixelShader mPixelShader;
	ENgines::Graphics::Texture mDiffuseTexture;
	ENgines::Graphics::Sampler mSampler;
};

class MeshPCCube : public GameState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
};

class MeshPCRect : public GameState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
};

class MeshPCPlane : public GameState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
};

class MeshPCSphere : public GameState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
};

class MeshPCCylinder : public GameState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
};

class MeshPXSkybox : public GameState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
};

class MeshPXSkysphere : public GameState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
};