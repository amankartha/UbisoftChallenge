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
		virtual void ChangeSize(float mult) = 0;
		virtual void ChangeSize(std::pair<float,float> pair) = 0;
	};

	struct AABB : Collider
	{
	public:
		AABB(const float length, const float width) : m_width(length), m_height(width) {}

		std::pair<float,float> GetValues() override
		{
			return std::make_pair(m_width, m_height);
		}

		void ChangeSize(float mult) override
		{
			m_width *= mult;
			m_height *= mult;
		}
		void ChangeSize(std::pair<float, float> pair) override
		{
			m_width = pair.first;
			m_height = pair.second;
		}
	
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
		void ChangeSize(float mult) override
		{
			m_radius *= mult;
		}
		void ChangeSize(std::pair<float, float> pair) override
		{
			m_radius = pair.first;
		}
		float m_radius;
	};

};