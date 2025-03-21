#include "stdafx.h"
#include "PhysicsSimulation.h"

#include "cameraManager.h"
#include "Collision.h"
#include "Game.h"
#include "RigidBody.h"
namespace physics
{
	

	size_t PhysicsSimulation::AddBody(Shape rigidBodyShape, bool is_static, float radius, float density, Material material, Ctransform* transform, bool
	                                  is_trigger)
	{
		PoolableObject<RigidBody>* rb = m_rigidbody_pool_.Get();
		 rb->obj.SetCircleRigidBody(is_static, radius, density, material, false);
		 rb->obj.SetTransform(transform);
		 rb->obj.m_isTrigger = is_trigger;
		 return rb->m_index;
	}

	size_t PhysicsSimulation::AddBody(Shape rigidBodyShape, bool is_static, float width, float height, float density, Material material, Ctransform* transform, bool
	                                  is_trigger)
	{
		PoolableObject<RigidBody>* rb = m_rigidbody_pool_.Get();
		rb->obj.SetAABBRigidBody(is_static, width,height, density, material, false);
		rb->obj.SetTransform(transform);
		rb->obj.m_isTrigger = is_trigger;
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
				App::DrawCircle(position.x, position.y,  object->GetCollider()->GetValues().first, 30,1,0,0);
			}
			else
			{
				App::DrawBox(position.x, position.y, object->GetCollider()->GetValues().first, object->GetCollider()->GetValues().second, 1, 0, 0);
			}
		}
	}

	void PhysicsSimulation::ResolveCollision(RigidBody* A, RigidBody* B, Vector2 normal, Collision collision)
	{
	
		Vector2 relativeVelocity = B->GetVelocity() - A->GetVelocity();

		float velAlongNormal = Vector2::Dot(relativeVelocity, normal);

		if (velAlongNormal > 0.0f)
		{
			return;
		}

		float e = (std::min)(A->GetMaterial().m_bounciness, B->GetMaterial().m_bounciness);

		
		float j = -(1.0f + e) * velAlongNormal;
		j /= A->GetMass().GetInverseMass() +  B->GetMass().GetInverseMass();

		
		Vector2 impulse =  normal * j;

		
		A->OffSetVelocity(impulse * -A->GetMass().GetInverseMass());
		B->OffSetVelocity(impulse * B->GetMass().GetInverseMass());
		
	}
	void PhysicsSimulation::CheckCollisions() //TODO: if time fix this awful code
	{ 
		for (int i = 0; i< m_rigidbody_pool_.activeIndices.size() -1; i++)
		{
			RigidBody* rbA = &m_rigidbody_pool_.m_pool[m_rigidbody_pool_.activeIndices[i]].obj;
			for (int j = i +1 ; j < m_rigidbody_pool_.activeIndices.size(); j++)
			{
				RigidBody* rbB = &m_rigidbody_pool_.m_pool[m_rigidbody_pool_.activeIndices[j]].obj;

				if (rbA->m_isStatic && rbB->m_isStatic)
				{
					continue;
				}
				Collision collision(rbA, rbB);

				auto valuesA  = rbA->GetCollider()->GetValues();
				auto valuesB = rbB->GetCollider()->GetValues();

				size_t rbAID = m_rigidbody_pool_.m_pool[m_rigidbody_pool_.activeIndices[i]].m_index;
				size_t rbBID = m_rigidbody_pool_.m_pool[m_rigidbody_pool_.activeIndices[j]].m_index;

				std::pair<int, int> pair = std::make_pair(i, j);

				if (valuesA.second < 0 && valuesB.second < 0)
				{
					if (CircleVsCircle(&collision))
					{
						
							if (rbA->m_isTrigger || rbB->m_isTrigger)
							{
								if (m_has_triggered_map.contains(pair) && !m_has_triggered_map[pair])
								{
									NotifyPhysicsObservers(true, rbAID, rbBID);
									m_has_triggered_map[pair] = true;
								}
							}
							else
							{
								if (rbA->m_isStatic)
								{
									rbB->OffsetPosition(collision.normal * collision.penetration);
								}
								else if (rbB->m_isStatic)
								{
									rbA->OffsetPosition(collision.normal * -collision.penetration);
								}
								else
								{
									rbA->OffsetPosition(collision.normal * -1 * collision.penetration / 2);
									rbB->OffsetPosition(collision.normal * collision.penetration / 2);
								}
								ResolveCollision(rbA, rbB, collision.normal, collision);
								if (m_has_triggered_map.contains(pair) && !m_has_triggered_map[pair])
								{
									NotifyPhysicsObservers(false, rbAID, rbBID);
									m_has_triggered_map[pair] = true;
								}
							}
					}
					else
					{
						m_has_triggered_map[pair] = false;
					}
					
					
				}
				else if (valuesA.second > -0.05 && valuesB.second > -0.05)
				{
					if (AABBVsAABB(&collision))
					{
						if (rbA->m_isTrigger || rbB->m_isTrigger)
						{
							if (m_has_triggered_map.contains(pair) && !m_has_triggered_map[pair])
							{
								NotifyPhysicsObservers(true, rbAID, rbBID);
								m_has_triggered_map[pair] = true;
							}
						}
						else
						{
							if (rbA->m_isStatic)
							{
								rbB->OffsetPosition(collision.normal * collision.penetration);
							}
							else if (rbB->m_isStatic)
							{
								rbA->OffsetPosition(collision.normal * -collision.penetration);
							}
							else
							{
								rbA->OffsetPosition(collision.normal * -collision.penetration / 2);
								rbB->OffsetPosition(collision.normal * collision.penetration / 2);
							}
							ResolveCollision(rbA, rbB, collision.normal, collision);
							if (m_has_triggered_map.contains(pair) && !m_has_triggered_map[pair])
							{
								NotifyPhysicsObservers(false, rbAID, rbBID);
								m_has_triggered_map[pair] = true;
							}
						}
					}
					else
					{
						m_has_triggered_map[pair] = false;
					}
				}
				else  if (rbA->GetCollider()->GetValues().second == -1)
					{
						if (IntersectionUsingSAT(&collision))
						{
							if (rbA->m_isTrigger || rbB->m_isTrigger)
							{
								if (m_has_triggered_map.contains(pair) && !m_has_triggered_map[pair])
								{
									NotifyPhysicsObservers(true, rbAID, rbBID);
									m_has_triggered_map[pair] = true;
								}
							}
							else
							{
								if (rbA->m_isStatic)
								{
									rbB->OffsetPosition(collision.normal * collision.penetration);
								}
								else if (rbB->m_isStatic)
								{
									rbA->OffsetPosition(collision.normal * -collision.penetration);
								}
								else
								{
									rbA->OffsetPosition(collision.normal * -collision.penetration / 2);
									rbB->OffsetPosition(collision.normal * collision.penetration / 2);


								}
								ResolveCollision(rbA, rbB, collision.normal, collision);
								if (m_has_triggered_map.contains(pair) && !m_has_triggered_map[pair])
								{
									NotifyPhysicsObservers(false, rbAID, rbBID);
									m_has_triggered_map[pair] = false;
								}
							}
						}
						else
						{
							m_has_triggered_map[pair] = false;
						}
					}
				else   
				{
						collision = Collision(rbB,rbA);

						if (IntersectionUsingSAT(&collision))
						{

							if (rbA->m_isTrigger || rbB->m_isTrigger)
							{
								if (m_has_triggered_map.contains(pair) && !m_has_triggered_map[pair])
								{
									NotifyPhysicsObservers(true, rbAID, rbBID);
									m_has_triggered_map[pair] = true;
								}
							}
							else
							{
								if (rbA->m_isStatic)
								{
									rbB->OffsetPosition(collision.normal * -collision.penetration);
								}
								else if (rbB->m_isStatic)
								{
									rbA->OffsetPosition(collision.normal * collision.penetration);
								}
								else
								{
									rbA->OffsetPosition(collision.normal * collision.penetration / 2);
									rbB->OffsetPosition(collision.normal * -collision.penetration / 2);


								}
								ResolveCollision(rbA, rbB, collision.normal * -1, collision);
								if (m_has_triggered_map.contains(pair) && !m_has_triggered_map[pair])
								{
									NotifyPhysicsObservers(false, rbAID, rbBID);
									m_has_triggered_map[pair] = true;
								}
							}
						}
						else
						{
							m_has_triggered_map[pair] = false;
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
