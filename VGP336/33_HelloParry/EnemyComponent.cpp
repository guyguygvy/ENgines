#include "EnemyComponent.h"
#include "PlayerComponent.h"

using namespace ENgines;
using namespace ENgines::Input;
using namespace ENgines::Graphics;
using namespace ENgines::Math;
using namespace ENgines::Physics;

void EnemyComponent::Initialize()
{
	mTransformComponent = GetOwner().GetComponent<TransformComponent>();
	mSoundBankComponent = GetOwner().GetComponent<SoundBankComponent>();
	mParryTriggered = false;
}

void EnemyComponent::Terminate()
{
	mSoundBankComponent = nullptr;
}

void EnemyComponent::Deserialize(const rapidjson::Value& value)
{
	if (value.HasMember("mMoveSpeed") && value["mMoveSpeed"].IsNumber())
	{
		mMoveSpeed = value["mMoveSpeed"].GetFloat();
	}

	if (value.HasMember("mAttackRange") && value["mAttackRange"].IsNumber())
	{
		mAttackRange = value["mAttackRange"].GetFloat();
	}

	if (value.HasMember("mResetDistance") && value["mResetDistance"].IsNumber())
	{
		mResetDistance = value["mResetDistance"].GetFloat();
	}

	if (value.HasMember("mStartZ") && value["mStartZ"].IsNumber())
	{
		mStartZ = value["mStartZ"].GetFloat();
	}
}



void EnemyComponent::Update(float deltaTime)
{
	
	Move(deltaTime);
	CheckParryWindow();
}


void EnemyComponent::Move(float deltaTime)
{
	auto* transform = GetOwner().GetComponent<TransformComponent>();
	if (!transform)
		return;

	transform->position.z -= mMoveSpeed * deltaTime;

	if (transform->position.z <= mResetDistance)
	{
		transform->position.z = mStartZ;
		mParryTriggered = false; // Reset for next loop
	}
}

void EnemyComponent::CheckParryWindow()
{
	//if (mParryTriggered)
	//{
	//	return;
	//}

	//auto* hitboxTransform = GetOwner().GetComponent<TransformComponent>();
	//auto* playerTransform = mPlayerGO->GetComponent<TransformComponent>();
	//auto* playerComp = mPlayerGO->GetComponent<PlayerComponent>();

	//if (!hitboxTransform || !playerTransform || !playerComp)
	//{
	//	return;
	//}

	//float parryWindow = std::abs(hitboxTransform->position.z - playerTransform->position.z);

	//if (parryWindow <= mAttackRange)
	//{
	//	mParryTriggered = true;
	//	if (playerComp->IsParrying())
	//	{
	//		//Hit Parry
	//		ParrySoundEffect();
	//	}
	//	else
	//	{
	//		//Missed Parry
	//	}
	//}
}