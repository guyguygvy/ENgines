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
	void OnMoveEvent();
	void OnSpacePressedEvent(const ENgines::Event& e) const;
	void OnLShiftPressedEvent(const ENgines::Event& e) const;
	void PlayBlastSoundEvent();
	void PlayExplosionSoundEvent();

	ENgines::Graphics::Camera mCamera;
	ENgines::Graphics::RenderObject mBall;
	ENgines::Graphics::RenderObject mGround;
	ENgines::Graphics::DirectionalLight mDirectionalLight;
	ENgines::Graphics::StandardEffect mStandardEffect;

	ENgines::Math::Vector3 mOffset = { 0.0f, 0.0f, 0.0f };
	ENgines::ListenerId mSpacePressedEventId = 0;
	ENgines::ListenerId mLShiftPressedEventId = 0;
	ENgines::Audio::SoundId mShotEventId = 0;
	ENgines::Audio::SoundId mBlastEventId = 0;
	ENgines::Audio::SoundId mExplosionEventId = 0;
	ENgines::Audio::SoundId mGoatEventId = 0;

	ENgines::Graphics::Animation mAnimation;
	float mAnimationTime = 0.0f;
};