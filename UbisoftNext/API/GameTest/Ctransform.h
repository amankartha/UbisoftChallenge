#pragma once
#include "Component.h"
#include "CustomMath.h"
#include <iostream>


class GameObject;

class Ctransform :
    public Component
{

public:
    static int Count;
    int id;
    Vector2 position;
    
    float rotation = 0.0f;

    Ctransform() : Component() 
    {
        id = Count++;
    }

    Ctransform(float x,float y) : Component()
    {
        id = Count++;
        position = Vector2(x, y);
    }
    ~Ctransform() override
    {
        --Count;
    }

    void SetPosition(Vector2 vec)
    {
        position = vec;
    }
    void OffsetPosition(Vector2 vec)
    {
        position = position + vec;
    }

    void Update() override;
    void Render() override;
};

