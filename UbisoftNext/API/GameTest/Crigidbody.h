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
	m_rigidbody_id(simulation->AddBody(physics::Shape::CIRCLE,isStatic,radius,density, physics::Material(density,bounciness),&GetAttachedGameObject()->GetTransformComponent(), isTrigger)),
        is_trigger_(isTrigger), width_(-1), height_(-1), radius_(radius), density_(density)

        , bounciness_(bounciness), is_static_(isStatic)
    {
        
    }

    Crigidbody(GameObject* gameobject, physics::PhysicsSimulation* simulation, float width,float height, const float density, float bounciness, bool isStatic,bool isTrigger ) : Component(gameobject),
        m_simulation_(simulation),
        m_rigidbody_id(simulation->AddBody(physics::Shape::BOX, isStatic, width,height, density, physics::Material(density,bounciness), &GetAttachedGameObject()->GetTransformComponent(),isTrigger)),
        is_trigger_(isTrigger), width_(width), height_(height), bounciness_(bounciness), is_static_(isStatic), radius_(-1),
        density_(density)
    {

    }

    ~Crigidbody() override;

    void AddForce(Vector2 force) const;

    Vector2 GetVelocity();

    size_t GetRigidBodyId();

    void ClearBody();

    void AddBody();

private:
    size_t m_rigidbody_id;
    physics::PhysicsSimulation* m_simulation_;
    bool is_trigger_;
    float width_;
    float height_;
    float bounciness_;
    bool is_static_;
    float radius_;
    const float density_;
};

