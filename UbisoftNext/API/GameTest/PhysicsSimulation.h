#pragma once
#include <memory>

#include "ObjectPool.h"
#include "RigidBody.h"
namespace physics
{
	enum class Shape;
}

namespace physics
{
	

	class PhysicsSimulation
	{
	public:
		PhysicsSimulation(Game* instance,float gravity = 9.8f,int MAX_RIGIDBODIES = 50) : m_game_instance_(instance) ,m_gravity(gravity),m_rigidbody_pool_(instance,MAX_RIGIDBODIES)
		{
			Init(MAX_RIGIDBODIES);
			
		}
		size_t AddBody(Shape rigidBodyShape, bool is_static, float radius, float density, Material material,Ctransform* transform);
		size_t AddBody(Shape rigidBodyShape, bool is_static, float width, float height, float density, Material material, Ctransform* transform);

		void RemoveBody(size_t id);

		RigidBody* GetBody(size_t id);

		void Update(float deltaTime);

		void Init(int rigidBodyCount);

		void DrawColliders();

	private:
		void ResolveCollision(RigidBody* A,RigidBody* B, Vector2 normal, float penetration);

		void CheckCollisions();
	private:
		float m_gravity;
		ObjectPool<RigidBody> m_rigidbody_pool_;
		Game* m_game_instance_;
	};

};

