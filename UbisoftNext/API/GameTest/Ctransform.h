#pragma once
#include "Component.h"
#include "CustomMath.h"
#include <iostream>


class GameObject;

class Ctransform :
    public Component
{

private:
    Transform m_transform;
    Transform m_transform_local;
public:
    static int Count;
    int id;
  
    

    Ctransform() : Component() 
    {
        id = Count++;
    }

    Ctransform(float x,float y) : Component()
    {
        id = Count++;
        m_transform.position = Vector2(x, y);
        m_transform.angle = 0.0f;
    }
    ~Ctransform() override
    {
        --Count;
    }

    void SetPosition(Vector2 vec)
    {
        m_transform.position = vec;
    }
    Vector2 GetPosition()
    {
        return m_transform.position;
    }
    float GetAngle()
    {
        return m_transform.angle;
    }
    void SetAngle(float angle)
    {
        m_transform.angle = angle;
    }
    void SetScale(float scale)
    {
        m_transform.scale = scale;
    }
    float GetScale()
    {
        return m_transform.scale;
    }
    void OffsetPosition(Vector2 vec)
    {
        m_transform.position = m_transform.position + vec;
    }
    void OffsetRotation(float a)
    {
        m_transform.angle += a;
    }

    Transform GetTransformCopy()
    {
        return m_transform;
    }
    
    void Update() override;
   
};

