#pragma once
#include "appUtility.h"
#include "Collider.h"
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
	};
	class RigidBody
	{
	public:

		Vector2 GetPosition() const
		{
			return m_transform->position;
		}
		void SetPosition(Vector2 pos)
		{
			m_transform->position = pos;
		}
		Material GetMaterial()
		{
			return m_material;
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

		void SetCircleRigidBody(bool is_static, float radius, float density, Material material);
		void SetAABBRigidBody(bool is_static, float length, float width, float density, Material material);



		RigidBody(bool m_is_static = false,
			Shape m_shape = Shape::BOX,
			const Collider& m_collider  = Collider(),
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
	public:
		Vector2 m_linearVelocity;
		Vector2 m_rotationalVelocity;
		float m_gravityScale;
		bool m_isStatic;
	private:
		Shape m_shape;
		Collider m_collider;
		Transform* m_transform;
		Vector2 m_force;

		Material m_material;
		MassData m_massData;

	};
};

