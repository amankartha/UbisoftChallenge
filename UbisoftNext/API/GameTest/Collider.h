#pragma once
#include "stdafx.h"

namespace physics
{

	enum class Shape
	{
		BOX = 0,
		CIRCLE = 1
	};

	struct Collider{};

	struct AABB : Collider
	{
	public:
		AABB(const float length, const float width) : m_length(length), m_width(width) {}
	private:
		float m_length;
		float m_width;
	};

	struct Circle : Collider
	{
	public:
		Circle(float radius) : m_radius(radius) {}
	public:
		float m_radius;
	};

};