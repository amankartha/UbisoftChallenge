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

		MassData(float _mass)
		{
			mass = _mass;
			inverse_mass = 1 / _mass;
		}
	};
	struct Material
	{
		float density;
		float bounciness;

		Material() : density(1), bounciness(0){}
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
			m_force += force;
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
			m_material.bounciness = std::clamp(value.bounciness, 0.0f, 1.0f);
			m_material.density = value.density;
		}
		MassData GetMass() const
		{
			return m_massData;
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
			const MassData& m_mass_data = MassData(1),
			const Vector2& m_linear_velocity = 0,
			const Vector2& m_rotational_velocity = 0,
			float m_gravity_scale = 1,
			const Vector2& m_force = Vector2(0, 0))
			: m_linearVelocity(m_linear_velocity),
			m_rotationalVelocity(m_rotational_velocity),
			m_gravityScale(m_gravity_scale),
			m_isStatic(m_is_static),
			m_shape(m_shape),
			m_collider(m_collider),
			m_force(m_force),
			m_material(m_material),
			m_massData(m_mass_data)

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
			m_massData(std::move(other.m_massData))
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

				
				other.m_collider = nullptr;
				other.m_transform = nullptr;
			}
			return *this;
		}
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
		
	};
};

