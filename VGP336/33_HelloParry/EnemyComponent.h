#pragma once

#include "CustomTypeIds.h"

class EnemyComponent : public ENgines::Component
{
public:
	SET_TYPE_ID(CustomComponentId::EnemyComponent);
	void Initialize();
	void Terminate();
	void Deserialize(const rapidjson::Value& value) override;
	void Update(float deltaTime);
	virtual void ParrySoundEffect() { mSoundBankComponent->Play("Parry"); }

private:
	ENgines::TransformComponent* mTransformComponent = nullptr;

	float mMoveSpeed = 2.0f;
	float mAttackRange = 1.5f;
	float mResetDistance = -5.0f;
	float mStartZ = 5.0f;
	bool mParryTriggered = false;


	void Move(float deltaTime);
	void CheckParryWindow();
protected:
	ENgines::SoundBankComponent* mSoundBankComponent = nullptr;
};