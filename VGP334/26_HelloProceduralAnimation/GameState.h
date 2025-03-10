#pragma once

#include <ENgines/Inc/ENgines.h>


class GameState : public ENgines::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Render() override;
	void DebugUI() override;
	void Update(float deltaTime);

protected:
	void UpdateCamera(float deltaTime);

	ENgines::Graphics::Camera mCamera;
	ENgines::Graphics::DirectionalLight mDirectionalLight;
	ENgines::Graphics::StandardEffect mStandardEffect;

	ENgines::Graphics::RenderObject mGround;
	ENgines::Physics::CollisionShape mGroundShape;
	ENgines::Physics::RigidBody mGroundRB;

	struct BodyPart
	{
		ENgines::Graphics::RenderObject segment;
		float range = 0.0f;
	};
	std::vector<BodyPart> mBodyParts;
	ENgines::Physics::RigidBody mBodyAnchorRB;
	ENgines::Physics::CollisionShape mBodyShape;
};