#pragma once

#include <ENgines/Inc/ENgines.h>

enum class CustomComponentId
{
	PlayerComponent = static_cast<uint32_t>(ENgines::ComponentId::Count),
	EnemyComponent,
	CustomDebugDraw
};

enum class CustomServiceId
{
	CustomDebugDrawDisplay = static_cast<uint32_t>(ENgines::ServiceId::Count),
};