#pragma once
#include "Component.h"
#include "appUtility.h"
#include "Collider.h"
#include "GameObject.h"
#include "PhysicsSimulation.h"
#include "RigidBody.h"
namespace physics
{
	class PhysicsSimulation;
}

class Crigidbody :
    public Component 
{
public:
    Crigidbody(GameObject* gameobject, physics::PhysicsSimulation* simulation, float radius, float density, float bounciness ,bool isStatic,bool isTrigger = false) : Component(gameobject),
	m_simulation_(simulation),
	m_rigidbody_id(simulation->AddBody(physics::Shape::CIRCLE,isStatic,radius,density, physics::Material(density,bounciness),&GetAttachedGameObject()->GetTransformComponent(), isTrigger))
    {
        
    }

    Crigidbody(GameObject* gameobject, physics::PhysicsSimulation* simulation, float width,float height, float density, float bounciness, bool isStatic,bool isTrigger ) : Component(gameobject),
        m_simulation_(simulation),
        m_rigidbody_id(simulation->AddBody(physics::Shape::BOX, isStatic, width,height, density, physics::Material(density,bounciness), &GetAttachedGameObject()->GetTransformComponent(),isTrigger))
    {

    }

    ~Crigidbody() override;

    void AddForce(Vector2 force) const;

    Vector2 GetVelocity();

    size_t GetRigidBodyId();

private:
    size_t m_rigidbody_id;
    physics::PhysicsSimulation* m_simulation_;
};

