#pragma once
#include <bit>
#include <memory>

#include "CustomMath.h"
#include "ObjectPool.h"
#include "ObserverPattern.h"
#include "RigidBody.h"
class Ctransform;

namespace physics{
	struct Collision;
	enum class Shape;
	
}
namespace std
{
	//to allow using <int,int > as a key 
	template<class A, class B>  
	struct hash<pair<A, B>> {
		size_t operator() (const pair<A, B>& p) const {
			return std::rotl(hash<A>{}(p.first), 1) ^
				hash<B>{}(p.second);
		}
	};
}
namespace physics
{

	class PhysicsSimulation : public Events::IPhysicsSubject
	{
	public:
		PhysicsSimulation(Game* instance,float gravity = 9.8f,int MAX_RIGIDBODIES = 50) : m_game_instance_(instance) ,m_gravity(gravity),m_rigidbody_pool_(instance,MAX_RIGIDBODIES)
		{
			Init(MAX_RIGIDBODIES);
			
		}
		size_t AddBody(Shape rigidBodyShape, bool is_static, float radius, float density, Material material, Ctransform* transform, bool
		               is_trigger);
		size_t AddBody(Shape rigidBodyShape, bool is_static, float width, float height, float density, Material material, Ctransform* transform, bool
		               is_trigger);

		void RemoveBody(size_t id);

		RigidBody* GetBody(size_t id);

		void Update(float deltaTime);

		void Init(int rigidBodyCount);

		void DrawColliders();

	private:
		void ResolveCollision(RigidBody* A,RigidBody* B, Vector2 normal, Collision collision);

		void CheckCollisions();
	private:
		float m_gravity;
		ObjectPool<RigidBody> m_rigidbody_pool_;
		Game* m_game_instance_;
		std::unordered_map<std::pair<int, int>, bool> m_has_triggered_map;
	};

};

