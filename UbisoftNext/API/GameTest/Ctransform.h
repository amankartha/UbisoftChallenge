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


  
    

    Ctransform() : Component() 
    {
       
    }

    Ctransform(float x,float y) : Component()
    {
     
        m_transform.position = Vector2(x, y);
        m_transform.angle = 0.0f;
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

    Transform& GetTransform() 
    {
        return m_transform;
    }
    
    void Update() override;
   
};

