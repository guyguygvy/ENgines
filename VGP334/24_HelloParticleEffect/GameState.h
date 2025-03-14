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
	ENgines::Graphics::ParticleSystemEffect mParticleSystemEffect;
	ENgines::Physics::ParticleSystem mParticleSystem;
};