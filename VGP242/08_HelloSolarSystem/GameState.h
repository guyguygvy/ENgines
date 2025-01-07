#pragma once

#include <ENgines/Inc/ENgines.h>

enum class SolarSystem
{
	MilkyWay,
	Earth,
	Jupiter,
	Mars,
	Mercury,
	Neptune,
	Pluto,
	Saturn,
	Sun,
	Uranus,
	Venus
};

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
	ENgines::Graphics::Camera mRenderTargetCamera;
	ENgines::Graphics::ConstantBuffer mConstantBuffer[11];
	ENgines::Graphics::MeshBuffer mMeshBuffer[11];
	ENgines::Graphics::VertexShader mVertexShader;
	ENgines::Graphics::PixelShader mPixelShader;
	ENgines::Graphics::Texture mDiffuseTexture[11];
	ENgines::Graphics::Sampler mSampler;
	ENgines::Graphics::RenderTarget mRenderTarget;

	SolarSystem mSolarSystem = SolarSystem::Sun;
};