#pragma once

#include "Component.h"

namespace ENgines
{
	class TransformComponent final : public Component, public Graphics::Transform
	{
	public:
		SET_TYPE_ID(ComponentId::Transform);

		void DebugUI() override;
		void Deserialize(const rapidjson::Value& value) override;
	};
}