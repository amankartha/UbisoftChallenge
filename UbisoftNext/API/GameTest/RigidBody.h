#pragma once
#include "appUtility.h"
#include "Collider.h"
#include "Ctransform.h"

namespace physics
{
	struct MassData
	{
		float mass;
		float inverse_mass;
		float inertia;
		float inverse_inertia;
		bool is_static;
		MassData(float _mass, bool isStatic)
		{
			is_static = isStatic;
			if (_mass <= 0.0001)
			{
				mass = 0;
				inverse_mass = 100000000.0f;
			}
			else
			{
				mass = _mass;
				inverse_mass = 1 / _mass;
			}
		}

		float GetInverseMass()
		{
			if (is_static)
			{
				return 0;
			}
			else
			{
				return inverse_mass;
			}
		}
	};
	struct Material
	{
		float m_density;
		float m_bounciness;

		Material() : m_density(1), m_bounciness(0.8f){}

		Material(float density, float bounciness) : m_density(density), m_bounciness(bounciness){}
	};
	class RigidBody
	{
	public:

		Vector2 GetPosition() const
		{
			return m_transform->GetWorldPosition();
		}
		void SetPosition(Vector2 pos)
		{
			m_transform->SetPosition(pos);
		}
		void OffsetPosition(Vector2 direction)
		{
			m_transform->OffsetPosition(direction);
		}

		Vector2 GetVelocity()
		{
			return m_linearVelocity;
		}
		void SetVelocity(Vector2 newVelocity)
		{
			m_linearVelocity = newVelocity;
		}

		void OffSetVelocity(Vector2 OffsetVelocity)
		{
			m_linearVelocity += OffsetVelocity;
		}
		void SetForce(Vector2 force)
		{
			m_force = force;
		}
		void AddForce(Vector2 force)
		{
			m_force = force;
		}
		Material GetMaterial()
		{
			return m_material;
		}
		void SetTransform(Ctransform* transfom)
		{
			m_transform = transfom;
		}
		void SetMaterial(Material value)
		{
			m_material.m_bounciness = std::clamp(value.m_bounciness, 0.0f, 1.0f);
			m_material.m_density = value.m_density;
		}
		MassData GetMass() const
		{
			return m_massData;
		}
		float GetStaticFriction()
		{
			return m_static_friction;
		}
		void SetStaticFriction(float val)
		{
			m_static_friction = std::clamp(val, 0.0f, 1.0f);
		}
		float GetDynamicFriction()
		{
			return m_dynamic_friction;
		}
		void SetDynamicFriction(float val)
		{
			m_dynamic_friction = std::clamp(val, 0.0f, 1.0f);
		}


		void Clear();
		void Start();
		void Update(float deltaTime);

		Collider* GetCollider();

		void SetCircleRigidBody(bool is_static, float radius, float density, Material material);
		void SetAABBRigidBody(bool is_static, float width, float height, float density, Material material);



		RigidBody(bool m_is_static = false,
			Shape m_shape = Shape::BOX,
			 Collider* m_collider  = nullptr,
			const Material& m_material = Material(),
			const MassData& m_mass_data = MassData(1,false),
			const Vector2& m_linear_velocity = Vector2(0,0),
			const Vector2& m_rotational_velocity = Vector2(0,0),
			float m_gravity_scale = 1,
			const Vector2& m_force = Vector2(0, 0),
			float staticFriction = 0.3f,
			float dynamicFriction = 0.1f)
			: m_linearVelocity(m_linear_velocity),
			m_rotationalVelocity(m_rotational_velocity),
			m_gravityScale(m_gravity_scale),
			m_isStatic(m_is_static),
			m_shape(m_shape),
			m_collider(m_collider),
			m_force(m_force),
			m_material(m_material),
			m_massData(m_mass_data),
			m_static_friction(staticFriction),
			m_dynamic_friction(dynamicFriction)
		{
		}

		~RigidBody()
		{
			delete m_collider;
		}

		// Move Constructor
		RigidBody(RigidBody&& other) noexcept
			: m_linearVelocity(std::move(other.m_linearVelocity)),
			m_rotationalVelocity(std::move(other.m_rotationalVelocity)),
			m_gravityScale(other.m_gravityScale),
			m_isStatic(other.m_isStatic),
			m_shape(other.m_shape),
			m_collider(other.m_collider),
			m_transform(other.m_transform),
			m_force(std::move(other.m_force)),
			m_material(std::move(other.m_material)),
			m_massData(std::move(other.m_massData)),
			m_static_friction(other.m_static_friction),
			m_dynamic_friction(other.m_dynamic_friction)
		{
			other.m_collider = nullptr; 
			other.m_transform = nullptr;
		}

		// Move Assignment Operator
		RigidBody& operator=(RigidBody&& other) noexcept
		{
			if (this != &other)
			{
				
				delete m_collider;

				
				m_linearVelocity = std::move(other.m_linearVelocity);
				m_rotationalVelocity = std::move(other.m_rotationalVelocity);
				m_gravityScale = other.m_gravityScale;
				m_isStatic = other.m_isStatic;
				m_shape = other.m_shape;
				m_collider = other.m_collider;
				m_transform = other.m_transform;
				m_force = std::move(other.m_force);
				m_material = std::move(other.m_material);
				m_massData = std::move(other.m_massData);
				m_static_friction = (other.m_static_friction);
				m_dynamic_friction =  (other.m_dynamic_friction);
				
				other.m_collider = nullptr;
				other.m_transform = nullptr;
			}
			return *this;
		}
	private:
		void AddFriction();
	public:
		Vector2 m_linearVelocity;
		Vector2 m_rotationalVelocity;
		float m_gravityScale;
		bool m_isStatic;
		
	private:
		Shape m_shape;
		Collider* m_collider;
		Ctransform* m_transform;
		Vector2 m_force;
		Material m_material;
		MassData m_massData;
		float m_static_friction;
		float m_dynamic_friction;
	};
};

