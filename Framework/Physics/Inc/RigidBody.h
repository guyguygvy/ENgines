#pragma once

#include "PhysicsObject.h"

namespace ENgines::Physics
{
	class CollisionShape;

	class RigidBody final : public PhysicsObject
	{
	public:
		RigidBody() = default;
		~RigidBody() override;

		void Initialize(ENgines::Graphics::Transform& graphicsTransform, const CollisionShape& shape, float mass = 0.0f);
		void Terminate();

		void SetPosition(const ENgines::Math::Vector3& position);
		void SetVelocity(const ENgines::Math::Vector3& velocity);

		bool IsDynamic() const;

	private:
		void SyncWithGraphics() override;
		btRigidBody* GetRigidBody() override;

		btRigidBody* mRigidBody = nullptr;
		btDefaultMotionState* mMotionState = nullptr;
		float mMass = 0.0f;

		ENgines::Graphics::Transform* mGraphicsTransform = nullptr;
	};
}