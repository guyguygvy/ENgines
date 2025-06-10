#include "GameState.h"
#include "CustomDebugDrawComponent.h"
#include "CustomDebugDrawService.h"

using namespace ENgines;
using namespace ENgines::Math;
using namespace ENgines::Graphics;
using namespace ENgines::Core;
using namespace ENgines::Input;
using namespace ENgines::Audio;

namespace
{
	Component* AddCustomComponent(const std::string& componentName, GameObject& gameObject)
	{
		Component* newComponent = nullptr;
		if (componentName == "CustomDebugDrawComponent")
		{
			newComponent = gameObject.AddComponent<CustomDebugDrawComponent>();
		}

		return newComponent;
	}
	Component* GetCustomComponent(const std::string& componentName, GameObject& gameObject)
	{
		Component* newComponent = nullptr;
		if (componentName == "CustomDebugDrawComponent")
		{
			newComponent = gameObject.GetComponent<CustomDebugDrawComponent>();
		}

		return newComponent;
	}
	Service* AddCustomService(const std::string& serviceName, GameWorld& gameWorld)
	{
		Service* service = nullptr;
		if (serviceName == "CustomDebugDrawService")
		{
			service = gameWorld.AddService<CustomDebugDrawService>();
		}
		return service;
	}
}

void GameState::Initialize()
{
	GameObjectFactory::SetCustomMake(AddCustomComponent);
	GameObjectFactory::SetCustomGet(GetCustomComponent);
	GameWorld::SetCustomService(AddCustomService);
	mGameWorld.LoadLevel(L"../../Assets/Templates/Levels/test_level.json");
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
