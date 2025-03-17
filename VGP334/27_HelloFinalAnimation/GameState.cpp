#include "GameState.h"

using namespace ENgines;
using namespace ENgines::Math;
using namespace ENgines::Graphics;
using namespace ENgines::Core;
using namespace ENgines::Input;
using namespace ENgines::Audio;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 2.0f, -5.0f });
	mCamera.SetLookAt({ 0.0f, 1.0f, 0.0f });

	mDirectionalLight.direction = Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.3f, 0.3f, 0.3f, 1.0f };
	mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
	mDirectionalLight.specular = { 0.9f, 0.9f, 0.9f, 1.0f };

	Mesh mesh = MeshBuilder::CreateSphere(300, 300, 1.0f);

	std::filesystem::path shaderFile = L"../../Assets/Shaders/Standard.fx";
	mStandardEffect.Initialize(shaderFile);
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);

	mCharacter.Initialize(L"../../Assets/Models/Remy/Remy.model", &mCharacterAnimator);
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Remy/SillyDancing.model");
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Remy/TwistDance.model");
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Remy/SillyDancing.model");
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Remy/TwistDance.model");
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Remy/HouseDancing.model");
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Remy/ChickenDance.model");
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Remy/BackFlip.model");
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Remy/FallingFlatImpact.model");
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Remy/StandUp.model");
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Remy/Dying.model");
	mCharacterAnimator.Initialize(mCharacter.modelId);

	AnimationKeyEvent ake;
	ake.SetIndex(2);

	Mesh groundMesh = MeshBuilder::CreateGroundPlane(100, 100, 1.0f);
	mGround.meshBuffer.Initialize(groundMesh);
	mGround.diffuseMapId = TextureCache::Get()->LoadTexture(L"misc/concrete.jpg");
	mGround.material.ambient = { 0.3f, 0.3f, 0.3f, 1.0f };
	mGround.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	mGround.material.specular = { 0.9f, 0.9f, 0.9f, 1.0f };
	mGround.material.power = 20.0f;

	mCharacterAnimation1 = AnimationBuilder()
	.AddEventKey(std::bind(&GameState::PlayNextAnimation, this), 0.1f)
		.AddPositionKey({ 1.0f, 0.5f, 0.0f }, 0.4f)
		.AddEventKey(std::bind(&GameState::PlayNextAnimation, this), 10.0f)
		.AddEventKey(std::bind(&GameState::PlayNextAnimation, this), 20.0f)
		.AddEventKey(std::bind(&GameState::PlayNextAnimation, this), 27.0f)
		.AddEventKey(std::bind(&GameState::PlayNextAnimation, this), 35.0f)
		.AddEventKey(std::bind(&GameState::PlayNextAnimation, this), 40.0f)
		.AddEventKey(std::bind(&GameState::PlayNextAnimation, this), 45.0f)
		.AddEventKey(std::bind(&GameState::PlayBreakSoundEvent, this), 45.8f)
		.AddEventKey(std::bind(&GameState::PlayAAASoundEvent, this), 46.1f)
		.AddEventKey(std::bind(&GameState::PlayNextAnimation, this), 46.7f)
		.AddPositionKey({ 1.0f, 0.5f, -15.0f }, 47.0f)
		.AddEventKey(std::bind(&GameState::PlayNextAnimation, this), 48.0f)
		.AddEventKey(std::bind(&GameState::PlayNextAnimation, this), 53.0f)
		.Build();

	mAnimationTime = 0.0f;

	EventManager* em = EventManager::Get();
	mScreamEventId = SoundEffectManager::Get()->Load("goat.wav");
	mBoneBreakEventId = SoundEffectManager::Get()->Load("bone-crack.wav");
}

void GameState::Terminate()
{
	mGround.Terminate();
	mCharacter.Terminate();
	mStandardEffect.Terminate();
}


void GameState::Update(float deltaTime)
{
	UpdateCamera(deltaTime);
	if (mCharacterAnimation1.GetDuration() > 0.0f)
	{
		float prevTime = mAnimationTime;
		mAnimationTime += deltaTime;
		mCharacterAnimation1.PlayEvent(prevTime, mAnimationTime);
		Event event;
		mCharacterAnimation1.PlayParameterEvent(prevTime, mAnimationTime, event);
	}

	mCharacterAnimator.Update(deltaTime);
}

void GameState::UpdateCamera(float deltaTime)
{
	auto input = InputSystem::Get();
	const float moveSpeed = (input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f) * deltaTime;
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
}

void GameState::PlayBreakSoundEvent()
{
	SoundEffectManager::Get()->Play(mBoneBreakEventId);
}
void GameState::PlayAAASoundEvent()
{
	SoundEffectManager::Get()->Play(mScreamEventId);
}

void GameState::PlayNextAnimation()
{
	mAnimationIndex++;
	if (mAnimationIndex >= mCharacterAnimator.GetAnimationCount())
	{
		mAnimationIndex = 0;
	}
	mCharacterAnimator.PlayAnimation(mAnimationIndex, true);
}

void GameState::Render()
{
	mStandardEffect.Begin();
	if (mShowSkeleton)
	{
		AnimationUtil::BoneTransforms boneTransforms;
		AnimationUtil::ComputeBoneTransforms(mCharacter.modelId, boneTransforms, &mCharacterAnimator);
		AnimationUtil::DrawSkeleton(mCharacter.modelId, boneTransforms);
	}
	else
	{
		mStandardEffect.Render(mCharacter);
	}
	mStandardEffect.Render(mGround);
	mStandardEffect.End();
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


	ImGui::Checkbox("ShowSkeleton", &mShowSkeleton);

	int maxAnimations = mCharacterAnimator.GetAnimationCount();
	mStandardEffect.DebugUI();
	ImGui::End();

	SimpleDraw::Render(mCamera);
}