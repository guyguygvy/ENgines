#pragma once

#include "CustomTypeIds.h"

class CustomDebugDrawComponent : public ENgines::Component
{
public:
	SET_TYPE_ID(CustomComponentId::CustomDebugDraw);

	void Initialize() override;
	void Terminate() override;
	void Deserialize(const rapidjson::Value& value) override;

	void AddDebugDraw() const;

private:
	const ENgines::TransformComponent* mTransformComponent = nullptr;
	ENgines::Math::Vector3 mPosition = ENgines::Math::Vector3::Zero;
	ENgines::Color mColor = ENgines::Colors::White;

	uint32_t mSlices = 0;
	uint32_t mRings = 0;
	float mRadius = 0.0f;
};