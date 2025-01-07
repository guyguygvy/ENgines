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
	ENgines::Graphics::DirectionalLight mDirectionalLight;
	ENgines::Graphics::StandardEffect mStandardEffect;
	ENgines::Graphics::ShadowEffect mShadowEffect;
	ENgines::Graphics::RenderGroup mCharacter;
	ENgines::Graphics::RenderObject mGround;
};