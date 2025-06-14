#include "EditTemplateState.h"
#include "CustomDebugDrawService.h"
#include "CustomDebugDrawComponent.h"

using namespace ENgines;
using namespace ENgines::Math;
using namespace ENgines::Graphics;
using namespace ENgines::Core;
using namespace ENgines::Input;
using namespace ENgines::Audio;

namespace
{
	Service* CustomServiceMake(const std::string& serviceName, GameWorld& gameWorld)
	{
		if (serviceName == "CustomDebugDrawService")
		{
			return gameWorld.AddService<CustomDebugDrawService>();
		}
		return nullptr;
	}

	Component* CustomComponentMake(const std::string& componentName, GameObject& gameObject)
	{
		if (componentName == "CustomDebugDrawComponent")
		{
			return gameObject.AddComponent<CustomDebugDrawComponent>();
		}
		return nullptr;
	}

	Component* CustomComponentGet(const std::string& componentName, GameObject& gameObject)
	{
		if (componentName == "CustomDebugDrawComponent")
		{
			return gameObject.GetComponent<CustomDebugDrawComponent>();
		}
		return nullptr;
	}
}

void EditTemplateState::Initialize()
{
	GameWorld::SetCustomService(CustomServiceMake);
	GameObjectFactory::SetCustomMake(CustomComponentMake);
	GameObjectFactory::SetCustomGet(CustomComponentGet);

	mGameWorld.LoadLevel(L"../../Assets/Templates/Levels/editor_level.json");
}

void EditTemplateState::Terminate()
{
	mGameWorld.Terminate();
}

void EditTemplateState::Update(float deltaTime)
{
	mGameWorld.Update(deltaTime);
}

void EditTemplateState::Render()
{
	mGameWorld.Render();
	SimpleDraw::AddGroundPlane(10.0f, Colors::White);
}

void EditTemplateState::DebugUI()
{
	ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	mGameWorld.DebugUI();
	if (ImGui::Button("Exit"))
	{
		MainApp().ChangeState("GameState");
	}
	ImGui::End();
}
