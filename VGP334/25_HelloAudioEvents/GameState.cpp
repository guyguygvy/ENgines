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

	Mesh ball = MeshBuilder::CreateSphere(60, 60, 0.5f);
	mBall.meshBuffer.Initialize(ball);
	mBall.diffuseMapId = TextureCache::Get()->LoadTexture("misc/basketball.jpg");

	Mesh ground = MeshBuilder::CreateGroundPlane(10, 10, 1.0f);
	mGround.meshBuffer.Initialize(ground);
	mGround.diffuseMapId = TextureCache::Get()->LoadTexture("misc/concrete.jpg");

	mAnimationTime = 0.0f;

	mAnimation = AnimationBuilder()
		.AddScaleKey({ 1.0f, 0.5f, 1.0f }, 0.0f)
		.AddPositionKey({ 0.0f, 0.5f, -3.0f }, 0.0f)
		.AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::XAxis, 90.0f * Math::Constants::DegToRad), 0.5f)
		.AddEventKey(std::bind(&GameState::PlayBlastSoundEvent, this), 0.5f)
		.AddPositionKey({ 0.0f, 2.5f, 0.0f }, 1.0f)
		.AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::XAxis, 180.0f * Math::Constants::DegToRad), 1.5f)
		.AddEventKey(std::bind(&GameState::PlayExplosionSoundEvent, this), 1.5f)
		.AddPositionKey({ 0.0f, 0.5f, 3.0f }, 2.0f)
		.AddScaleKey({ 1.0f, 1.0f, 0.5f }, 2.0f)
		.AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::YAxis, 90.0f * Math::Constants::DegToRad), 2.5f)
		.AddEventKey(std::bind(&GameState::PlayBlastSoundEvent, this), 2.5f)
		.AddPositionKey({ 1.5f, 2.5f, 1.5f }, 3.0f)
		.AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::YAxis, 180.0f * Math::Constants::DegToRad), 3.5f)
		.AddEventKey(std::bind(&GameState::PlayExplosionSoundEvent, this), 3.5f)
		.AddPositionKey({ 3.0f, 0.5f, 0.0f }, 4.0f)
		.AddScaleKey({ 0.5f, 1.0f, 1.0f }, 4.0f)
		.AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::XAxis, 90.0f * Math::Constants::DegToRad), 4.5f)
		.AddEventKey(std::bind(&GameState::PlayBlastSoundEvent, this), 4.5f)
		.AddPositionKey({ 0.0f, 2.5f, 0.0f }, 5.0f)
		.AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::XAxis, 180.0f * Math::Constants::DegToRad), 5.5f)
		.AddEventKey(std::bind(&GameState::PlayExplosionSoundEvent, this), 5.5f)
		.AddPositionKey({ -3.0f, 0.5f, 0.0f }, 6.0f)
		.AddScaleKey({ 1.0f, 1.0f, 0.5f }, 6.0f)
		.AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::YAxis, 90.0f * Math::Constants::DegToRad), 6.5f)
		.AddEventKey(std::bind(&GameState::PlayBlastSoundEvent, this), 6.5f)
		.AddPositionKey({ -1.5f, 2.5f, -1.5f }, 7.0f)
		.AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::YAxis, 180.0f * Math::Constants::DegToRad), 7.5f)
		.AddEventKey(std::bind(&GameState::PlayExplosionSoundEvent, this), 7.5f)
		.AddPositionKey({ 0.0f, 0.5f, -3.0f }, 8.0f)
		.AddScaleKey({ 1.0f, 0.5f, 1.0f }, 8.0f)
		.Build();

	EventManager* em = EventManager::Get();
	mSpacePressedEventId = em->AddListener(EventType::SpacePressed, std::bind(&GameState::OnSpacePressedEvent, this, std::placeholders::_1));
	mLShiftPressedEventId = em->AddListener(EventType::LShiftPressed, std::bind(&GameState::OnLShiftPressedEvent, this, std::placeholders::_1));

	mShotEventId = SoundEffectManager::Get()->Load("megamanx_shot.wav");
	mBlastEventId = SoundEffectManager::Get()->Load("megamanx_blast.wav");
	mExplosionEventId = SoundEffectManager::Get()->Load("explosion.wav");
	mGoatEventId = SoundEffectManager::Get()->Load("goat.wav");
}

void GameState::Terminate()
{
	EventManager::Get()->RemoveListener(EventType::SpacePressed, mSpacePressedEventId);
	mGround.Terminate();
	mBall.Terminate();
	mStandardEffect.Terminate();
}

void GameState::Update(float deltaTime)
{
	UpdateCamera(deltaTime);

	if (mAnimation.GetDuration() > 0.0f)
	{
		float prevTime = mAnimationTime;
		mAnimationTime += deltaTime;
		mAnimation.PlayEvent(prevTime, mAnimationTime);
		while (mAnimationTime > mAnimation.GetDuration())
		{
			mAnimationTime -= mAnimation.GetDuration();	// Simple loop
		}
	}

	if (InputSystem::Get()->IsKeyPressed(KeyCode::SPACE))
	{
		SpacePressedEvent spe;
		EventManager::Broadcast(spe);
	}
	if (InputSystem::Get()->IsKeyPressed(KeyCode::LSHIFT))
	{
		LShiftPressedEvent spe2;
		EventManager::Broadcast(spe2);
	}
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

void GameState::OnMoveEvent()
{
	mOffset.x += 0.5f;
	SoundEffectManager::Get()->Play(mExplosionEventId);
}

void GameState::OnSpacePressedEvent(const ENgines::Event& e) const
{
	SoundEffectManager::Get()->Play(mShotEventId);
}

void GameState::OnLShiftPressedEvent(const ENgines::Event& e) const
{
	SoundEffectManager::Get()->Play(mGoatEventId);
}

void GameState::PlayBlastSoundEvent()
{
	SoundEffectManager::Get()->Play(mBlastEventId);
}
void GameState::PlayExplosionSoundEvent()
{
	SoundEffectManager::Get()->Play(mExplosionEventId);
}

bool checkBox = true;

void GameState::Render()
{
	mBall.transform = mAnimation.GetTransform(mAnimationTime);
	mBall.transform.position += mOffset;
	mStandardEffect.Begin();
	mStandardEffect.Render(mGround);
	mStandardEffect.Render(mBall);
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
	ImGui::End();
}