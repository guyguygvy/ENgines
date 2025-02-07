#pragma once

#include <ENgines/Inc/ENgines.h>


class GameState : public ENgines::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime);
	void Render() override;
	void DebugUI() override;

protected:
	void UpdateCamera(float deltaTime);

	ENgines::Graphics::Camera mCamera;
	ENgines::Graphics::DirectionalLight mDirectionalLight;
	ENgines::Graphics::StandardEffect mStandardEffect;
	ENgines::Graphics::RenderGroup mCharacter;
	ENgines::Graphics::Animator mCharacterAnimator;
	ENgines::Graphics::RenderObject mGround;

	bool mShowSkeleton = false;
	int mAnimationIndex = -1;
};
