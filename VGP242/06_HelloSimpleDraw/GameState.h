#pragma once
#include <ENgines/Inc/ENgines.h>

enum class DebugDrawType
{
	None,
	Line,
	Transform,
	Sphere,
	GroundPlane,
	GroundCircle,
	AABB,
	AABBFilled,
	ExtraShape
};

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
	DebugDrawType mDebugDrawType = DebugDrawType::None;
};