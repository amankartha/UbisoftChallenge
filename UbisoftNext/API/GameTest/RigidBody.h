#pragma once
#include "appUtility.h"


struct MassData
{
	float mass;
	float inv_mass;
	float inertia;
	float inverse_inertia;
};
struct Material
{
	float density;
	float bounciness;
};
class RigidBody
{
public:

#pragma region Getters and Setters

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
	
	float GetInverseMass()
	{
		return m_invMass;
	}

#pragma endregion
	static bool CreateCircleRigidBody(bool is_static, float radius, float density, Material material);


private:
	RigidBody(const Vector2& m_linear_velocity, const Vector2& m_rotational_velocity, float m_gravity_scale,
		bool m_is_static, Shape m_shape, const Collider& m_collider, Transform* m_transform, const Vector2& m_force,
		const Material& m_material, const MassData& m_mass_data, float m_inv_mass)
		: m_linearVelocity(m_linear_velocity),
		m_rotationalVelocity(m_rotational_velocity),
		m_gravityScale(m_gravity_scale),
		m_isStatic(m_is_static),
		m_shape(m_shape),
		m_collider(m_collider),
		m_transform(m_transform),
		m_force(m_force),
		m_material(m_material),
		m_massData(m_mass_data),
		m_invMass(m_inv_mass)
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
	float m_invMass;
	
};

