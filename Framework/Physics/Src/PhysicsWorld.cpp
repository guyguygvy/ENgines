#include "Precompiled.h"
#include "PhysicsWorld.h"
#include "PhysicsObject.h"

using namespace ENgines;
using namespace ENgines::Physics;

namespace
{
	std::unique_ptr<PhysicsWorld> sPhysicsWorld;
}

void PhysicsWorld::StaticInitialize(const Settings& settings)
{
	ASSERT(sPhysicsWorld == nullptr, "PhysicsWorld: is already initialized");
	sPhysicsWorld = std::make_unique<PhysicsWorld>();
	sPhysicsWorld->Initialize(settings);
}

void PhysicsWorld::StaticTerminate()
{
	if (sPhysicsWorld != nullptr)
	{
		sPhysicsWorld->Terminate();
		sPhysicsWorld.reset();
	}
}

PhysicsWorld* PhysicsWorld::Get()
{
	ASSERT(sPhysicsWorld != nullptr, "PhysicsWorld: must be initialized");
	return sPhysicsWorld.get();
}

PhysicsWorld::~PhysicsWorld()
{
	ASSERT(mDynamicsWorld == nullptr, "PhysicsWorld: must be terminated");
}

void PhysicsWorld::Initialize(const Settings& settings)
{
	mSettings = settings;

	mInterface = new btDbvtBroadphase();
	mSolver = new btSequentialImpulseConstraintSolver();
#ifdef USE_SOFT_BODY
	mCollisionConfiguration = new btSoftBodyRigidBodyCollisionConfiguration();
	mDispatcher = new btCollisionDispatcher(mCollisionConfiguration);
	mDynamicsWorld = new btSoftRigidDynamicsWorld(mDispatcher, mInterface, mSolver, mCollisionConfiguration);
#else
	mCollisionConfiguration = new btDefaultCollisionConfiguration();
	mDispatcher = new btCollisionDispatcher(mCollisionConfiguration);
	mDynamicsWorld = new btDiscreteDynamicsWorld(mDispatcher, mInterface, mSolver, mCollisionConfiguration);
#endif
	mDynamicsWorld->setGravity(TobtVector3(settings.gravity));
	mDynamicsWorld->setDebugDrawer(&mPhysicsDebugDraw);
}

void PhysicsWorld::Terminate()
{
	SafeDelete(mDynamicsWorld);
	SafeDelete(mSolver);
	SafeDelete(mInterface);
	SafeDelete(mDispatcher);
	SafeDelete(mCollisionConfiguration);
}

void PhysicsWorld::Update(float deltaTime)
{
	mDynamicsWorld->stepSimulation(deltaTime, mSettings.simulationSteps, mSettings.fixedTimeStep);
	for (PhysicsObject* po : mPhysicsObjects)
	{
		po->SyncWithGraphics();
	}
}

void PhysicsWorld::DebugUI()
{
	if (ImGui::CollapsingHeader("Physics", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::DragFloat3("Gravity", &mSettings.gravity.x, 0.1f))
		{
			mDynamicsWorld->setGravity(TobtVector3(mSettings.gravity));
		}
		ImGui::Checkbox("DebugDraw", &mDebugDraw);
		if (mDebugDraw)
		{
			ImGui::Indent();
			int debugMode = mPhysicsDebugDraw.getDebugMode();
			bool isEnabled = (debugMode & btIDebugDraw::DBG_DrawWireframe);
			if (ImGui::Checkbox("WireFrame", &isEnabled))
			{
				debugMode = (isEnabled) ? debugMode | btIDebugDraw::DBG_DrawWireframe : debugMode & ~btIDebugDraw::DBG_DrawWireframe;
			}
			isEnabled = (debugMode & btIDebugDraw::DBG_DrawAabb);
			if (ImGui::Checkbox("DrawAABB", &isEnabled))
			{
				debugMode = (isEnabled) ? debugMode | btIDebugDraw::DBG_DrawAabb : debugMode & ~btIDebugDraw::DBG_DrawAabb;
			}
			isEnabled = (debugMode & btIDebugDraw::DBG_DrawNormals);

			mPhysicsDebugDraw.setDebugMode(debugMode);
			mDynamicsWorld->debugDrawWorld();
			ImGui::Unindent();
		}
	}
}

void PhysicsWorld::Register(PhysicsObject* physicsObject)
{
	auto iter = std::find(mPhysicsObjects.begin(), mPhysicsObjects.end(), physicsObject);
	if (iter == mPhysicsObjects.end())	// if the item has not been added yet
	{
		mPhysicsObjects.push_back(physicsObject);
#ifdef USE_SOFT_BODY
		if (physicsObject->GetSoftBody())
		{
			mDynamicsWorld->addSoftBody(physicsObject->GetSoftBody());
		}
#endif // USE_SOFT_BODY

		if (physicsObject->GetRigidBody())
		{
			mDynamicsWorld->addRigidBody(physicsObject->GetRigidBody());
		}
	}
}

void PhysicsWorld::Unregister(PhysicsObject* physicsObject)
{
	auto iter = std::find(mPhysicsObjects.begin(), mPhysicsObjects.end(), physicsObject);
	if (iter != mPhysicsObjects.end())
	{
#ifdef USE_SOFT_BODY
		if (physicsObject->GetSoftBody())
		{
			mDynamicsWorld->removeSoftBody(physicsObject->GetSoftBody());
		}
#endif // USE_SOFT_BODY

		if (physicsObject->GetRigidBody())
		{
			mDynamicsWorld->removeRigidBody(physicsObject->GetRigidBody());
		}
		mPhysicsObjects.erase(iter);
	}
}

const PhysicsWorld::Settings& PhysicsWorld::GetSettings() const
{
	return mSettings;
}

void PhysicsWorld::UpdateSettings(const Settings& settings)
{
	mSettings = settings;
}

void PhysicsWorld::SetGravity(const ENgines::Math::Vector3& gravity)
{
	mSettings.gravity = gravity;
	mDynamicsWorld->setGravity(TobtVector3(gravity));
}