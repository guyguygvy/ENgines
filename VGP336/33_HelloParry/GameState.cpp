#include "GameState.h"
#include "PlayerComponent.h"
#include "EnemyComponent.h"


using namespace ENgines;
using namespace ENgines::Math;
using namespace ENgines::Graphics;
using namespace ENgines::Core;
using namespace ENgines::Input;
using namespace ENgines::Audio;

Component* CustomComponentMake(const std::string& componentName, GameObject& gameObject)
{
	if (componentName == "PlayerComponent")
	{
		return gameObject.AddComponent<PlayerComponent>();
	}
	if (componentName == "EnemyComponent")
	{
		return gameObject.AddComponent<EnemyComponent>();
	}
	return nullptr;
}

Component* CustomComponentGet(const std::string& componentName, GameObject& gameObject)
{
	if (componentName == "PlayerComponent")
	{
		return gameObject.GetComponent<PlayerComponent>();
	}
	if (componentName == "EnemyComponent")
	{
		return gameObject.GetComponent<EnemyComponent>();
	}
	return nullptr;
}


void GameState::Initialize()
{
	GameObjectFactory::SetCustomMake(CustomComponentMake);
	GameObjectFactory::SetCustomGet(CustomComponentGet);
	mGameWorld.LoadLevel(L"../../Assets/Templates/Levels/parry_level.json");

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
}
