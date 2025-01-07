#pragma once
#include "Component.h"
#include "CustomMath.h"



class GameObject;

class Ctransform :
    public Component
{

public:
    Ctransform() : Component()
    {

    }

    Ctransform(float x, float y) : Component()
    {
        m_transform_local.position = Vector2(x, y);
        m_transform_world.angle = 0.0f;
    }

    void SetPosition(Vector2 vec);

    Vector2 GetWorldPosition() ;

    float GetAngle();

    void SetAngle(float angle);

    void SetScale(float scale);

    float GetScale();

    void OffsetPosition(Vector2 vec);

    void OffsetRotation(float a);

    Transform* GetTransform();

    void Update() override;
private:
    Transform CombineTransform();
    void MarkAllChildrenDirty();
public:
    bool m_dirty = true; //dirtyflag to check if position needs recalculation
private:
    Transform m_transform_world;
    Transform m_transform_local;
};

inline Transform* Ctransform::GetTransform()
{
    return &m_transform_world;
}

