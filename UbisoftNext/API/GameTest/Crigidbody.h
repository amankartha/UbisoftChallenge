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
    Crigidbody(GameObject* gameobject, physics::PhysicsSimulation* simulation,float radius,float density,bool isStatic ) : Component(gameobject),
	m_simulation_(simulation),
	m_rigidbody_id(simulation->AddBody(physics::Shape::CIRCLE,isStatic,radius,1, physics::Material(),&GetAttachedGameObject()->GetTransformComponent()))
    {
        
    }

    Crigidbody(GameObject* gameobject, physics::PhysicsSimulation* simulation, float width,float height, float density, bool isStatic ) : Component(gameobject),
        m_simulation_(simulation),
        m_rigidbody_id(simulation->AddBody(physics::Shape::BOX, isStatic, width,height, 1, physics::Material(), &GetAttachedGameObject()->GetTransformComponent()))
    {

    }

    ~Crigidbody();

    void AddForce(Vector2 force);
private:
    size_t m_rigidbody_id;
    physics::PhysicsSimulation* m_simulation_;
};

