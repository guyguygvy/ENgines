#pragma once

namespace ENgines::Physics
{
	class CollisionShape final
	{
	public:
		CollisionShape() = default;
		~CollisionShape();

		void InitializeEmpty();
		void InitializeSphere(float radius);
		void InitializeCapsule(float radius, float height);
		void InitializeBox(const ENgines::Math::Vector3& halfExtents);
		void InitializeHull(const ENgines::Math::Vector3& halfExtents, const ENgines::Math::Vector3& origin);
		void Terminate();

	private:
		friend class RigidBody;
		btCollisionShape* mCollisionShape = nullptr;
	};
}