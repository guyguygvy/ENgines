#pragma once

#include "Component.h"

namespace ENgines
{
    class UIComponent : public Component
    {
    public:
        virtual void Render() = 0;
    };
}