#include "stdafx.h"
#include "PhysicsSimulation.h"

#include "cameraManager.h"
#include "Collision.h"
#include "Game.h"
#include "RigidBody.h"
namespace physics
{
	

	size_t PhysicsSimulation::AddBody(Shape rigidBodyShape, bool is_static, float radius, float density, Material material,Ctransform* transform)
	{
		PoolableObject<RigidBody>* rb = m_rigidbody_pool_.Get();
		 rb->obj.SetCircleRigidBody(is_static, radius, density, material);
		 rb->obj.SetTransform(transform);
		 return rb->m_index;
	}

	size_t PhysicsSimulation::AddBody(Shape rigidBodyShape, bool is_static,float width,float height, float density, Material material, Ctransform* transform)
	{
		PoolableObject<RigidBody>* rb = m_rigidbody_pool_.Get();
		rb->obj.SetAABBRigidBody(is_static, width,height, density, material);
		rb->obj.SetTransform(transform);
		return rb->m_index;
	}

	void PhysicsSimulation::RemoveBody(size_t id)
	{
		/*auto it = std::find(m_bodies.begin(), m_bodies.end(), rigid_body);
		if (it != m_bodies.end()) {
			m_bodies.erase(it); 
		}*/
		m_rigidbody_pool_.Release(id);
	}

	RigidBody* PhysicsSimulation::GetBody(size_t id)
	{
		return m_rigidbody_pool_.GetDirect(id);
	}

	void PhysicsSimulation::Init(int rigidBodyCount)
	{
		m_rigidbody_pool_.InitializePool(rigidBodyCount);
	}

	void PhysicsSimulation::DrawColliders()
	{
		


		for (auto index : m_rigidbody_pool_.activeIndices)
		{
			RigidBody* object = &m_rigidbody_pool_.m_pool[index].obj;
			Vector2 position = App::WorldToScreen(m_game_instance_->GetCameraManager()->GetMainCamera(), object->GetPosition());


			if (object->GetCollider()->GetValues().second == -1)
			{
				App::DrawCircle(position.x, position.y,  object->GetCollider()->GetValues().first, 30,0,1,0);
			}
			else
			{
				App::DrawBox(position.x, position.y, object->GetCollider()->GetValues().first, object->GetCollider()->GetValues().second, 0, 1, 0);
			}
		}
	}

	void PhysicsSimulation::ResolveCollision(RigidBody* A, RigidBody* B, Vector2 normal, float penetration)
	{
		// Calculate relative velocity
		Vector2 relativeVelocity = B->GetVelocity() - A->GetVelocity();

		// Calculate the coefficient of restitution (bounciness)
		float e = (std::min)(A->GetMaterial().bounciness, B->GetMaterial().bounciness);

		// Calculate the impulse scalar
		float j = -(1.0f + e) * Vector2::Dot(relativeVelocity, normal);
		j /= (1.0f / A->GetMass().mass) + (1.0f / B->GetMass().mass);

		// Apply the impulse to the velocities
		Vector2 impulse =  normal * j;

		A->OffSetVelocity(impulse * (-1.0f / A->GetMass().mass));
		B->OffSetVelocity(impulse * (1.0f / B->GetMass().mass));
	}
	void PhysicsSimulation::CheckCollisions()
	{
		for (int i = 0; i< m_rigidbody_pool_.activeIndices.size() -1; i++)
		{
			RigidBody* rbA = &m_rigidbody_pool_.m_pool[m_rigidbody_pool_.activeIndices[i]].obj;
			for (int j = i +1 ; j < m_rigidbody_pool_.activeIndices.size(); j++)
			{
				RigidBody* rbB = &m_rigidbody_pool_.m_pool[m_rigidbody_pool_.activeIndices[j]].obj;

				Collision collision(rbA, rbB);

				auto valuesA  = rbA->GetCollider()->GetValues();
				auto valuesB = rbB->GetCollider()->GetValues();
				if (valuesA.second < 0 && valuesB.second < 0)
				{
					if (CircleVsCircle(&collision))
					{
						rbA->OffsetPosition(collision.normal * -1 * collision.penetration / 2);
						rbB->OffsetPosition(collision.normal * collision.penetration / 2);

						ResolveCollision(rbA, rbB, collision.normal, collision.penetration);
					}
				}
				else if (valuesA.second > -0.05 && valuesB.second > -0.05)
				{
					if (AABBVsAABB(&collision))
					{
						rbA->OffsetPosition(collision.normal * -1 * collision.penetration / 2);
						rbB->OffsetPosition(collision.normal * collision.penetration / 2);

						ResolveCollision(rbA, rbB, collision.normal, collision.penetration);
					}
				}
				else
				{
					if (valuesA.second < 0)
					{
						Collision swappedCollision(rbB, rbA);  //TODO: if time fix this awful code

						if (AABBVsCircle(&swappedCollision))
						{
							rbA->OffsetPosition(swappedCollision.normal  * swappedCollision.penetration / 2);
							rbB->OffsetPosition(swappedCollision.normal  * -swappedCollision.penetration / 2);

							ResolveCollision(rbA, rbB, swappedCollision.normal, swappedCollision.penetration);
						}
					}
					else
					{
						if (AABBVsCircle(&collision))
						{
							rbA->OffsetPosition(collision.normal  * -collision.penetration / 2);
							rbB->OffsetPosition(collision.normal * collision.penetration / 2);

							ResolveCollision(rbA, rbB, collision.normal, collision.penetration);
						}
					}
					
				}
			}
		}
	}

	void PhysicsSimulation::Update(float deltaTime)
	{
		CheckCollisions();
		m_rigidbody_pool_.UpdateEachInUse(deltaTime);
	}

};
