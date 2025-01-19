#pragma once
#include "Component.h"
#include "appUtility.h"
#include "GameObject.h"
#include "PhysicsSimulation.h"

namespace physics
{
	class PhysicsSimulation;
}

class Crigidbody :
    public Component
{
public:
    Crigidbody(GameObject* gameobject, physics::PhysicsSimulation* simulation,float radius,float density) : Component(gameobject),
	m_simulation_(simulation),
	m_rigidbody_id(simulation->AddBody(physics::Shape::CIRCLE,false,radius,1, physics::Material(),&GetAttachedGameObject()->GetTransformComponent()))
    {
        
    }

    Crigidbody(GameObject* gameobject, physics::PhysicsSimulation* simulation, float width,float height, float density) : Component(gameobject),
        m_simulation_(simulation),
        m_rigidbody_id(simulation->AddBody(physics::Shape::BOX, false, width,height, 1, physics::Material(), &GetAttachedGameObject()->GetTransformComponent()))
    {

    }

    ~Crigidbody();
private:
    size_t m_rigidbody_id;
    physics::PhysicsSimulation* m_simulation_;
};

