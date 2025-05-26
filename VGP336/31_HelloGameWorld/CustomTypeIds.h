#pragma once

#include <ENgines/Inc/ENgines.h>

enum class CustomComponentId
{
	CustomDebugDraw = static_cast<uint32_t>(ENgines::ComponentId::Count),
	NewComponent,
	NewComponent2
};

enum class CustomServiceId
{
	CustomDebugDrawDisplay = static_cast<uint32_t>(ENgines::ServiceId::Count),
};