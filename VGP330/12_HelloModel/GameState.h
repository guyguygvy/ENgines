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
	ENgines::Graphics::RenderGroup mCharacter1;
	ENgines::Graphics::RenderGroup mCharacter2;
	ENgines::Graphics::DirectionalLight mDirectionalLight;
	ENgines::Graphics::StandardEffect mStandardEffect;
	ENgines::Graphics::StandardEffect mRenderTargetStandardEffect;
	ENgines::Graphics::RenderTarget mRenderTarget;
};