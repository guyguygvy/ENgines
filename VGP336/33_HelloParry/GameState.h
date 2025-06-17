#pragma once

#include <ENgines/Inc/ENgines.h>


class GameState : public ENgines::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Render() override;
	void Update(float deltaTime);
	void DebugUI() override;
private:
	ENgines::CameraComponent* mCameraComponent = nullptr;

protected:
	ENgines::GameWorld mGameWorld;

	ENgines::Graphics::Camera mCamera;
};
