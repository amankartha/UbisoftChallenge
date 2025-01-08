#include "stdafx.h"
#include "Ctransform.h"
#include "GameObject.h"
#include "App/app.h"

void Ctransform::SetPosition(Vector2 vec)
{
    m_transform_local.position = vec;
    MarkAllChildrenDirty();
}

void Ctransform::OffsetPosition(Vector2 vec)
{
    m_transform_local.position += vec;
    MarkAllChildrenDirty();
}

Vector2 Ctransform::GetWorldPosition()
{
    if (m_dirty)
    {
        CombineTransform(); // Recalculate the world transform
        m_dirty = false;
    }
    return m_transform_world.position;
}

float Ctransform::GetAngle()
{
    if (m_dirty)
    {
        CombineTransform();
        m_dirty = false;
    }
    return m_transform_world.angle;
}

void Ctransform::SetAngle(float angle)
{
    m_transform_local.angle = angle;
    MarkAllChildrenDirty();
}

void Ctransform::SetScale(float scale)
{
    m_transform_local.scale = scale;
    MarkAllChildrenDirty();
}

float Ctransform::GetScale() 
{
    if (m_dirty)
    {
        CombineTransform();
        m_dirty = false;
    }
    return m_transform_world.scale;
}

void Ctransform::OffsetRotation(float a)
{
    m_transform_local.angle += a;
    MarkAllChildrenDirty();
}

void Ctransform::Update()
{
	Component::Update();
   
}

Transform Ctransform::CombineTransform()
{
    GameObject* parentObject = getAttachedGameObject()->m_parent;

    if (parentObject)
    {
        const Transform& parentTransform = *parentObject->GetTransformComponent().GetTransform();

        // Combine parent's transform with local transform
        m_transform_world.position = parentTransform.position + m_transform_local.position;
        m_transform_world.angle = parentTransform.angle + m_transform_local.angle;
        m_transform_world.scale = parentTransform.scale * m_transform_local.scale;
    }
    else
    {
        // No parent: world transform equals local transform
        m_transform_world = m_transform_local;
    }

    return m_transform_world;
}

void Ctransform::MarkAllChildrenDirty()
{
    if (m_dirty)
    {
        return;
    }

    m_dirty = true;

    for (GameObject* child : getAttachedGameObject()->m_children)
    {
        child->GetTransformComponent().MarkAllChildrenDirty();
    }
}


