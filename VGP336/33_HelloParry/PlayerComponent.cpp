#include "PlayerComponent.h"
using namespace ENgines;
using namespace ENgines::Input;

void PlayerComponent::Initialize()
{

}

void PlayerComponent::Terminate()
{
}

void PlayerComponent::Deserialize(const rapidjson::Value& value)
{
    if (value.HasMember("mMaxParryTime") && value["mMaxParryTime"].IsNumber())
    {
        const_cast<float&>(mMaxParryTime) = value["mMaxParryTime"].GetFloat();
    }
}

void PlayerComponent::TryParry() {
    if (!isParrying)
    {
        isParrying = true;
        mParryTimer = mMaxParryTime;
    }

}

void PlayerComponent::Update(float deltaTime)
{
    if (isParrying)
    {
        mParryTimer -= deltaTime;
        if (mParryTimer <= 0.0f)
        {
            isParrying = false;
        }
    }

    auto input = InputSystem::Get();
    if (input->IsKeyPressed(KeyCode::SPACE))
    {
        TryParry();
    }
}