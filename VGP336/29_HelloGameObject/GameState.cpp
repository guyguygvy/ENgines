#include "GameState.h"

using namespace ENgines;
using namespace ENgines::Math;
using namespace ENgines::Graphics;
using namespace ENgines::Core;
using namespace ENgines::Input;
using namespace ENgines::Audio;

void GameState::Initialize()
{
	mGameWorld.Initialize();

	GameObject* transformGO = mGameWorld.CreateGameObject("Transform");
	TransformComponent* transformComponent = transformGO->AddComponent<TransformComponent>();

	GameObject* cameraGO = mGameWorld.CreateGameObject("Camera");
	CameraComponent* cameraComponent = cameraGO->AddComponent<CameraComponent>();
	cameraGO->AddComponent<FPSCameraComponent>();
	cameraComponent->GetCamera().SetPosition({ 0.0f, 1.0f, -2.0f });
	cameraComponent->GetCamera().SetLookAt({ 0.0f, 1.0f, 0.0f });
	cameraGO->Initialize();

	mCameraComponent = cameraComponent;
}

void GameState::Terminate()
{
	mGameWorld.Terminate();
}

void GameState::Update(float deltaTime)
{
	mGameWorld.Update(deltaTime);
}

void GameState::Render()
{
	mGameWorld.Render();
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	mGameWorld.DebugUI();
	ImGui::End();

	SimpleDraw::Render(mCameraComponent->GetCamera());
}
