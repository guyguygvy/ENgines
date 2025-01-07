#include "GameState.h"

using namespace ENgines;
using namespace ENgines::Math;
using namespace ENgines::Graphics;
using namespace ENgines::Core;
using namespace ENgines::Input;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 2.0f, -5.0f });
	mCamera.SetLookAt({ 0.0f, 1.0f, 0.0f });

	mDirectionalLight.direction = Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.3f, 0.3f, 0.3f, 1.0f };
	mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
	mDirectionalLight.specular = { 0.9f, 0.9f, 0.9f, 1.0f };

	float x = 0.0f;
	Mesh mesh = MeshBuilder::CreateSphere(300, 300, 1.0f);

	std::filesystem::path shaderFile = L"../../Assets/Shaders/Standard.fx";
	mStandardEffect.Initialize(shaderFile);
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);

	mTerrainEffect.Initialize();
	mTerrainEffect.SetCamera(mCamera);
	mTerrainEffect.SetDirectionalLight(mDirectionalLight);

	mCharacter.Initialize(L"../../Assets/Models/Remy/Remy.model");

	mTerrain.Initialize(L"../../Assets/Images/terrain/heightmap_512x512.raw", 20.0f, 10.0f);

	mGround.meshBuffer.Initialize(mTerrain.GetMesh());
	mGround.diffuseMapId = TextureCache::Get()->LoadTexture("terrain/dirt_seamless.jpg");
	mGround.normalMapId = TextureCache::Get()->LoadTexture("terrain/grass_2048.jpg");
}

void GameState::Terminate()
{
	mGround.Terminate();
	mCharacter.Terminate();
	mTerrainEffect.Terminate();
	mStandardEffect.Terminate();
}


void GameState::Update(float deltaTime)
{
	UpdateCamera(deltaTime);
}

void GameState::UpdateCamera(float deltaTime)
{
	auto input = InputSystem::Get();
	const float moveSpeed = (input->IsKeyDown(KeyCode::LSHIFT) ? 15.0f : 5.0f) * deltaTime;
	const float turnSpeed = 0.1f * deltaTime;
	if (input->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-moveSpeed);
	}
	if (input->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed);
	}
	if (input->IsKeyDown(KeyCode::E))
	{
		mCamera.Rise(moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::Q))
	{
		mCamera.Rise(-moveSpeed);
	}
	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(input->GetMouseMoveX() * turnSpeed);
		mCamera.Pitch(input->GetMouseMoveY() * turnSpeed);
	}

	Vector3 camPos = mCamera.GetPosition();
	float height = mTerrain.GetHeight(camPos);
	camPos.y = height + 1.5f;
	mCamera.SetPosition(camPos);
}

bool checkBox = true;

void GameState::Render()
{
	mStandardEffect.Begin();
	mStandardEffect.Render(mCharacter);
	mStandardEffect.End();

	mTerrainEffect.Begin();
	mTerrainEffect.Render(mGround);
	mTerrainEffect.End();
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::DragFloat3("Direction", &mDirectionalLight.direction.x, 0.01f))
		{
			mDirectionalLight.direction = Normalize(mDirectionalLight.direction);
		}

		ImGui::ColorEdit4("Ambient##Light", &mDirectionalLight.ambient.r);
		ImGui::ColorEdit4("Diffuse##Light", &mDirectionalLight.diffuse.r);
		ImGui::ColorEdit4("Specular##Light", &mDirectionalLight.specular.r);
	}

	ImGui::Separator();
	ImGui::Text("RenderTarget");

	ImGui::Checkbox("CheckBox", &checkBox);
	mStandardEffect.DebugUI();
	mTerrainEffect.DebugUI();
	ImGui::End();
}