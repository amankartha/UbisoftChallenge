#pragma once
#include "Component.h"
#include "CustomMath.h"
#include "ObserverPattern.h"


class GameObject;

class Ctransform :
    public Component , public Events::ISubject
{

public:
    Ctransform(GameObject* gameObject) : Component(gameObject)
    {
        MarkAllChildrenDirty();
    }

    Ctransform(GameObject* gameObject, float x, float y) : Component(gameObject)
    {
        m_transform_local.position = Vector2(x, y);
        m_transform_world.angle = 0.0f;
        MarkAllChildrenDirty();
    }

    void SetPosition(Vector2 vec);

    void ResetLocalPosition();

    void RecalculateWithNewParent(GameObject* parent);

    Vector2 GetWorldPosition() ;

    float GetAngle();

    void SetAngle(float angle);

    void SetScale(float scale);

    float GetScale();

    void OffsetPosition(Vector2 vec);

    void OffsetRotation(float a);

    Transform* GetTransform();

    void Update(float DeltaTime) override;
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

