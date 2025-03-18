#include "GameState.h"

using namespace ENgines;
using namespace ENgines::Math;
using namespace ENgines::Graphics;
using namespace ENgines::Core;
using namespace ENgines::Input;
using namespace ENgines::Audio;
using namespace ENgines::Physics;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 2.0f, -5.0f });
	mCamera.SetLookAt({ 0.0f, 3.0f, 0.0f });

	mDirectionalLight.direction = Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.3f, 0.3f, 0.3f, 1.0f };
	mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
	mDirectionalLight.specular = { 0.9f, 0.9f, 0.9f, 1.0f };

	Mesh mesh = MeshBuilder::CreateSphere(300, 300, 1.0f);

	std::filesystem::path shaderFile = L"../../Assets/Shaders/Standard.fx";
	mStandardEffect.Initialize(shaderFile);
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);

	/*mParticleSystemEffect.Initialize();

	mParticleSystemEffect.SetCamera(mCamera);*/

	/*ParticleSystemInfo info;
	info.textureId = TextureCache::Get()->LoadTexture("misc/tears.png");
	int maxParticles = 100;
	info.particlesPerEmit = { 1, 4 };
	info.delay = 1.0f;
	info.lifeTime = FLT_MAX;
	info.timeBetweenEmit = { 0.2f, 0.4f };
	info.spawnAngle = { -30.0f, 30.0f };
	info.spawnSpeed = { 1.0f, 3.0f };
	info.spawnLifeTime = { 0.5f, 2.0f };
	info.spawnDirection = Math::Vector3::YAxis;
	info.spawnPosition = Math::Vector3::Zero;
	info.startScale = { Math::Vector3::One, Math::Vector3::One };
	info.endScale = { Math::Vector3::One, Math::Vector3::One };
	info.startColor = { Colors::White, Colors::White };
	info.endColor = { Colors::White, Colors::White };
	mParticleSystem.Initialize(info);*/

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

	mCharacter2.Initialize(L"../../Assets/Models/SmallMan/small.model", &mCharacterAnimator2);
	ModelCache::Get()->AddAnimation(mCharacter2.modelId, L"../../Assets/Models/SmallMan/Crying.model");
	mCharacterAnimator2.Initialize(mCharacter2.modelId);

	mCharacter3.Initialize(L"../../Assets/Models/SmallMan2/small.model", &mCharacterAnimator3);
	ModelCache::Get()->AddAnimation(mCharacter3.modelId, L"../../Assets/Models/SmallMan2/Crying.model");
	mCharacterAnimator3.Initialize(mCharacter3.modelId);

	AnimationKeyEvent ake;
	ake.SetIndex(2);

	Mesh wall = MeshBuilder::CreateGroundPlane(15,15,1.0f);
	mWall.meshBuffer.Initialize(wall);
	mWall.diffuseMapId = TextureCache::Get()->LoadTexture("misc/kazooya.png");
	Mesh wall2 = MeshBuilder::CreateGroundPlane(20,20,1.0f);
	mWall2.meshBuffer.Initialize(wall2);
	mWall2.diffuseMapId = TextureCache::Get()->LoadTexture("misc/sad.png");

	Mesh groundMesh = MeshBuilder::CreateGroundPlane(100, 100, 1.0f);
	mGround.meshBuffer.Initialize(groundMesh);
	mGround.diffuseMapId = TextureCache::Get()->LoadTexture(L"misc/concrete.jpg");
	mGround.material.ambient = { 0.3f, 0.3f, 0.3f, 1.0f };
	mGround.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	mGround.material.specular = { 0.9f, 0.9f, 0.9f, 1.0f };
	mGround.material.power = 20.0f;

	mCharacterAnimation1 = AnimationBuilder()
	.AddEventKey(std::bind(&GameState::PlayNextAnimation, this), 0.1f)
		.AddEventKey(std::bind(&GameState::PlayMitaiSoundEvent, this), 0.1f)
		.AddPositionKey({ 0.0f, 0.0f, 0.0f }, 0.4f)
		.AddEventKey(std::bind(&GameState::PlayNextAnimation, this), 10.0f)
		.AddEventKey(std::bind(&GameState::PlayNextAnimation, this), 20.0f)
		.AddEventKey(std::bind(&GameState::PlayNextAnimation, this), 27.0f)
		.AddEventKey(std::bind(&GameState::PlayNextAnimation, this), 35.0f)
		.AddEventKey(std::bind(&GameState::PlayNextAnimation, this), 40.0f)
		.AddEventKey(std::bind(&GameState::PlayNextAnimation, this), 45.0f)
		.AddEventKey(std::bind(&GameState::PlayBreakSoundEvent, this), 45.8f)
		.AddEventKey(std::bind(&GameState::PlayAAASoundEvent, this), 46.1f)
		.AddEventKey(std::bind(&GameState::PlayNextAnimation, this), 46.7f)
		.AddPositionKey({ 0.0f, 0.0f, 0.0f }, 46.8f)
		.AddPositionKey({ 0.0f, 0.0f, 3.0f }, 46.81f)
		.AddEventKey(std::bind(&GameState::PlayNextAnimation, this), 48.0f)
		.AddEventKey(std::bind(&GameState::PlayNextAnimation, this), 53.0f)
		.AddPositionKey({ 0.0f, 0.0f, 3.0f }, 89.0f)
		.Build();

	mCharacterAnimation2 = AnimationBuilder()
	.AddEventKey(std::bind(&GameState::PlayNextAnimation, this), 0.1f)
	.AddPositionKey({ 4.0f, -10.0f, 15.0f }, 0.2f)
	.AddPositionKey({ 4.0f, 0.0f, 15.0f }, 19.0f)
	.AddPositionKey({ 4.0f, 0.0f, 6.0f }, 55.0f)
		.Build();
	mCharacterAnimation3 = AnimationBuilder()
	.AddEventKey(std::bind(&GameState::PlayNextAnimation, this), 0.1f)
	.AddPositionKey({ -4.0f, -10.0f, 15.0f }, 0.2f)
	.AddPositionKey({ -4.0f, 0.0f, 15.0f }, 19.0f)
	.AddPositionKey({ -4.0f, 0.0f, 6.0f }, 55.0f)
		.Build();
	
	mWallAnimation = AnimationBuilder()
		.AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::XAxis, 270.0f * Math::Constants::DegToRad), 0.1f)
		.AddPositionKey({ 0.0f, -15.0f, 10.0f }, 0.12f)
		.AddPositionKey({ .0f, 5.0f, 10.0f }, 18.5f)
		.AddPositionKey({ -2.0f, 5.0f, 10.0f }, 24.0f)
		.AddPositionKey({ 2.0f, 5.0f, 10.0f }, 29.0f)
		.AddPositionKey({ -2.0f, 5.0f, 10.0f }, 34.0f)
		.AddPositionKey({ 2.0f, 5.0f, 10.0f }, 39.0f)
		.AddPositionKey({ -2.0f, 5.0f, 10.0f }, 44.0f)
		.AddPositionKey({ 2.0f, 5.0f, 10.0f }, 49.0f)
		.Build();
	mWallAnimation2 = AnimationBuilder()
		.AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::XAxis, 270.0f * Math::Constants::DegToRad), 0.1f)
		.AddPositionKey({ 0.0f, -15.0f, 9.9f }, 0.12f)
		.AddPositionKey({ 0.0f, 7.0f, 9.9f }, 67.0f)
		.Build();

	mAnimationTime = 0.0f;

	EventManager* em = EventManager::Get();
	mScreamEventId = SoundEffectManager::Get()->Load("goat.wav");
	mBoneBreakEventId = SoundEffectManager::Get()->Load("bone-crack.wav");
	mSadEventId = SoundEffectManager::Get()->Load("KazoMitai.wav");
}

void GameState::Terminate()
{
	mGround.Terminate();
	mCharacter.Terminate();
	mCharacter2.Terminate();
	mCharacter3.Terminate();
	mWall.Terminate();
	mWall2.Terminate();
	/*mParticleSystem.Terminate();
	mParticleSystemEffect.Terminate();*/
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
		while (mAnimationTime > mCharacterAnimation1.GetDuration())
		{
			mAnimationTime -= mCharacterAnimation1.GetDuration();
		}
	}
	if (mCharacterAnimation2.GetDuration() > 0.0f)
	{
		float prevTime = mAnimationTime;
		mCharacterAnimation2.PlayEvent(prevTime, mAnimationTime);
		Event event;
		mCharacterAnimation2.PlayParameterEvent(prevTime, mAnimationTime, event);
	}
	if (mCharacterAnimation3.GetDuration() > 0.0f)
	{
		float prevTime = mAnimationTime;
		mCharacterAnimation3.PlayEvent(prevTime, mAnimationTime);
		Event event;
		mCharacterAnimation3.PlayParameterEvent(prevTime, mAnimationTime, event);
	}
	//mParticleSystem.Update(deltaTime);
	mCharacterAnimator.Update(deltaTime);
	mCharacterAnimator2.Update(deltaTime);
	mCharacterAnimator3.Update(deltaTime);
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

void GameState::PlayMitaiSoundEvent()
{
	SoundEffectManager::Get()->Play(mSadEventId);
}

void GameState::PlayNextAnimation()
{
	mAnimationIndex++;
	mAnimationIndex2++;
	if (mAnimationIndex >= mCharacterAnimator.GetAnimationCount())
	{
		mAnimationIndex = 0;
	}
	if (mAnimationIndex2 >= mCharacterAnimator2.GetAnimationCount())
	{
		mAnimationIndex2 = 1;
	}
	if (mAnimationIndex3 >= mCharacterAnimator3.GetAnimationCount())
	{
		mAnimationIndex3 = 1;
	}
	mCharacterAnimator.PlayAnimation(mAnimationIndex, true);
	mCharacterAnimator2.PlayAnimation(mAnimationIndex2, true);
	mCharacterAnimator3.PlayAnimation(mAnimationIndex3, true);
}

void GameState::Render()
{
	mStandardEffect.Begin();
	//mParticleSystemEffect.Begin();
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
	mCharacter.transform = mCharacterAnimation1.GetTransform(mAnimationTime);
	mCharacter2.transform = mCharacterAnimation2.GetTransform(mAnimationTime);
	mCharacter3.transform = mCharacterAnimation3.GetTransform(mAnimationTime);
	mStandardEffect.Render(mCharacter2);
	mStandardEffect.Render(mCharacter3);
	mWall.transform = mWallAnimation.GetTransform(mAnimationTime);
	mWall2.transform = mWallAnimation2.GetTransform(mAnimationTime);
	//mParticleSystem.Render(mParticleSystemEffect);
	mStandardEffect.Render(mGround);
	mStandardEffect.Render(mWall);
	mStandardEffect.Render(mWall2);
	//mParticleSystemEffect.End();
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