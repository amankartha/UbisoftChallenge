#pragma once
#include "stdafx.h"
#include <utility>

namespace physics
{

	enum class Shape
	{
		BOX = 0,
		CIRCLE = 1
	};

	struct Collider
	{
		virtual std::pair<float,float> GetValues() = 0;
	};

	struct AABB : Collider
	{
	public:
		AABB(const float length, const float width) : m_width(length), m_height(width) {}

		std::pair<float,float> GetValues() override
		{
			return std::make_pair(m_width, m_height);
		}
	private:
		float m_width;
		float m_height;
	};

	struct Circle : Collider
	{
	public:
		Circle(float radius) : m_radius(radius) {}
		std::pair<float, float> GetValues() override
		{
			return std::make_pair(m_radius, -1.0f);
		}
	public:
		float m_radius;
	};

};