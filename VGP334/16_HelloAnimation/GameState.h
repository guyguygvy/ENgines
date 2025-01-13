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
	ENgines::Graphics::RenderObject mBall;
	ENgines::Graphics::RenderObject mGround;
	ENgines::Graphics::DirectionalLight mDirectionalLight;
	ENgines::Graphics::StandardEffect mStandardEffect;

	ENgines::Graphics::Animation mAnimation;
	float mAnimationTime = 0.0f;
};