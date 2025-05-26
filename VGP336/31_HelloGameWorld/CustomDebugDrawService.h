#pragma once

#include "CustomTypeIds.h"

class CustomDebugDrawComponent;

class CustomDebugDrawService : public ENgines::Service
{
public:
    SET_TYPE_ID(CustomServiceId::CustomDebugDrawDisplay);

    void Render() override;

    void Register(const CustomDebugDrawComponent* debugDrawComponent);
    void Unregister(const CustomDebugDrawComponent* debugDrawComponent);

private:
    using CustomDebugDrawComponents = std::vector<const CustomDebugDrawComponent*>;
    CustomDebugDrawComponents mCustomDebugDrawComponents;
};