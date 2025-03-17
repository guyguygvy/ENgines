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
		void PlayNextAnimation();

		void PlayBreakSoundEvent();
		void PlayAAASoundEvent();

	ENgines::Graphics::Camera mCamera;
	ENgines::Graphics::DirectionalLight mDirectionalLight;
	ENgines::Graphics::StandardEffect mStandardEffect;
	ENgines::Graphics::RenderGroup mCharacter;
	ENgines::Graphics::RenderGroup mCharacter2;
	ENgines::Graphics::Animator mCharacterAnimator;
	ENgines::Graphics::RenderObject mGround;
	ENgines::Graphics::Animation mCharacterAnimation1;
	ENgines::Graphics::Animation mCharacterAnimation2;

	ENgines::Audio::SoundId mBoneBreakEventId = 0;
	ENgines::Audio::SoundId mScreamEventId = 0;

	bool mShowSkeleton = false;
	float mAnimationTime = 0.0f;
	int mAnimationIndex = -1;
};
