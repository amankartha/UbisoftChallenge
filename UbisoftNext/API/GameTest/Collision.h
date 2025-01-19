#pragma once
#include "stdafx.h"
#include "RigidBody.h"
#include "Collider.h"
///

namespace physics
{
	struct Collision
	{
		RigidBody* A;
		RigidBody* B;
		float penetration;
		Vector2 normal;
        bool isFlipped = false;
	};

	struct Pair
	{
		RigidBody* A;
		RigidBody* B;

	};

    bool CircleVsCircle(Collision* collision)
    {
        RigidBody* A = collision->A;
        RigidBody* B = collision->B;

        
        Vector2 APosition = A->GetPosition();
        Vector2 BPosition = B->GetPosition();

        float radiusA = A->GetCollider()->GetValues().first;
        float radiusB = B->GetCollider()->GetValues().first;

        
        float distanceSquared = Vector2::DistanceSquared(APosition, BPosition);
        float radiiSum = radiusA + radiusB;

        
        if (distanceSquared > radiiSum * radiiSum) {
            return false; 
        }

        
        if (distanceSquared == 0.0f) {
            collision->normal = Vector2(1.0f, 0.0f); 
            collision->penetration = radiiSum;
            return true;
        }

        
        float distance = std::sqrt(distanceSquared);
        collision->normal = Vector2::Normalize(BPosition - APosition);
        collision->penetration = radiiSum - distance;

        return true;
    }

    bool AABBVsAABB(Collision* collision)
    {
        RigidBody* A = collision->A;
        RigidBody* B = collision->B;

        Vector2 APosition = A->GetPosition();
        Vector2 BPosition = B->GetPosition();

        auto dimensionsA = A->GetCollider()->GetValues(); 
        auto dimensionsB = B->GetCollider()->GetValues();

        float halfWidthA = dimensionsA.first / 2.0f;
        float halfHeightA = dimensionsA.second / 2.0f;

        float halfWidthB = dimensionsB.first / 2.0f;
        float halfHeightB = dimensionsB.second / 2.0f;

       
        Vector2 diff = BPosition - APosition;
        float totalHalfWidth = halfWidthA + halfWidthB;
        float totalHalfHeight = halfHeightA + halfHeightB;

       
        if (std::abs(diff.x) > totalHalfWidth || std::abs(diff.y) > totalHalfHeight) {
            return false; 
        }

     
        float overlapX = totalHalfWidth - std::abs(diff.x);
        float overlapY = totalHalfHeight - std::abs(diff.y);

        if (overlapX < overlapY) {
            collision->normal = Vector2(diff.x > 0 ? 1.0f : -1.0f, 0.0f); 
            collision->penetration = overlapX;
        }
        else {
            collision->normal = Vector2(0.0f, diff.y > 0 ? 1.0f : -1.0f); 
            collision->penetration = overlapY;
        }

        return true;
    }
    ////NOTE THE A MEMBER MUST BE THE AABB FOR THIS TO WORK ;) // ALSO REALLY BUGGY 
    //bool AABBVsCircle(Collision* collision)
    //{
    //    RigidBody* A = collision->A;
    //    RigidBody* B = collision->B;

    //    Vector2 APosition = A->GetPosition();
    //    Vector2 CirclePosition = B->GetPosition();

    //    auto AABBvalues = A->GetCollider()->GetValues();
    //    float halfWidthA = AABBvalues.first / 2.0f;
    //    float halfHeightA = AABBvalues.second / 2.0f;

    //    auto colliderB = B->GetCollider();
    //    if (colliderB == nullptr) {
    //        return false; 
    //    }
    //    float radiusB = colliderB->GetValues().first;

    //    Vector2 n = CirclePosition - APosition;

    //    float closestX = std::clamp(n.x, -halfWidthA, halfWidthA);
    //    float closestY = std::clamp(n.y, -halfHeightA, halfHeightA);

    //    Vector2 closest = APosition + Vector2(closestX, closestY);

    //    Vector2 diff = CirclePosition - closest;
    //    float distanceSquared = Vector2::DistanceSquared(CirclePosition, closest);

    //    if (distanceSquared > radiusB * radiusB) {
    //        return false;
    //    }

    //    float distance = std::sqrt(distanceSquared);

    //    collision->normal = (distance > 0) ? Vector2::Normalize(diff) : Vector2(1.0f, 0.0f);
    //    collision->penetration = radiusB - distance;

    //    if (distance == 0.0f) {
    //        collision->normal = Vector2(1.0f, 0.0f); 
    //        collision->penetration = radiusB;
    //    }

    //    return true;
    //}
    //

    bool AABBVsCircle(Collision* collision)
    {
        RigidBody* A = collision->A;
        RigidBody* B = collision->B;
      

        Vector2 n = B->GetPosition() - A->GetPosition();
        Vector2 closestPosition = n;

        float x_extent = A->GetCollider()->GetValues().first / 2;
        float y_extent = A->GetCollider()->GetValues().second / 2;

        closestPosition.x = std::clamp(closestPosition.x, -x_extent, x_extent);
        closestPosition.y = std::clamp(closestPosition.y, -y_extent, y_extent);

        bool inside = false;

        if ((n - closestPosition).MagnitudeSquared() < 0.000001f)
        {
            inside = true;

            if (std::abs(n.x) > std::abs(n.y))
            {
                closestPosition.x = (closestPosition.x > 0) ? x_extent : -x_extent;
                B->OffsetPosition(Vector2(closestPosition.x,0));
            }
            else
            {
                closestPosition.y = (closestPosition.y > 0) ? y_extent : -y_extent;
                B->OffsetPosition(Vector2(0,closestPosition.y));
            }
            
        }

        float d = (n - closestPosition).MagnitudeSquared();
        float radius = B->GetCollider()->GetValues().first;

        if (d > (radius * radius) && !inside)
        {
            return false;
        }

        Vector2 normal = (n - closestPosition).Normalize();

        if (inside)
        {
            collision->normal = normal * -1;
            collision->penetration = radius - std::sqrt(d);
        }
        else
        {
            collision->normal = normal;
            collision->penetration = radius - std::sqrt(d);
        }

        return true;
    }

    bool CircleVsAABB(Collision* collision)
    {

        RigidBody* A = collision->A;
        RigidBody* B = collision->B;


        Vector2 n = A->GetPosition() - B->GetPosition();
        Vector2 closestPosition = n;

        float x_extent = B->GetCollider()->GetValues().first / 2;
        float y_extent = B->GetCollider()->GetValues().second / 2;

        closestPosition.x = std::clamp(closestPosition.x, -x_extent, x_extent);
        closestPosition.y = std::clamp(closestPosition.y, -y_extent, y_extent);

        bool inside = false;

        if ((n - closestPosition).MagnitudeSquared() < 0.000001f)
        {
            inside = true;

            if (std::abs(n.x) > std::abs(n.y))
            {
                closestPosition.x = (closestPosition.x > 0) ? x_extent : -x_extent;
                A->OffsetPosition(Vector2(closestPosition.x, 0));
            }
            else
            {
                closestPosition.y = (closestPosition.y > 0) ? y_extent : -y_extent;
                A->OffsetPosition(Vector2(0, closestPosition.y));
            }

        }

        float d = (n - closestPosition).MagnitudeSquared();
        float radius = A->GetCollider()->GetValues().first;

        if (d > (radius * radius) && !inside)
        {
            return false;
        }

        Vector2 normal = (n - closestPosition).Normalize();

        if (inside)
        {
            collision->normal = normal * -1;
            collision->penetration = radius - std::sqrt(d);
        }
        else
        {
            collision->normal = normal;
            collision->penetration = radius - std::sqrt(d);
        }

        return true;
    }
};
