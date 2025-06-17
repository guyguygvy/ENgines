#pragma once
#include "CustomTypeIds.h"

class PlayerComponent : public ENgines::Component
{
public:
	SET_TYPE_ID(CustomComponentId::PlayerComponent);

	void Initialize();
	void Terminate();
	void Deserialize(const rapidjson::Value& value) override;
	void Update(float deltaTime);
	void TryParry();
	bool IsParrying() const { return isParrying; }

private:

	bool isParrying = false;
	float mParryTimer = 0.0f;
	float mMaxParryTime = 0.3f; 
};