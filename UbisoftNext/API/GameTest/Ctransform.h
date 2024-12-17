#pragma once
#include "Component.h"
#include <iostream>

class GameObject;

class Ctransform :
    public Component
{

public:
    static int Count;
    int id;
    float x = 0.0f;
    float y = 0.0f;
    float rotation = 0.0f;

    Ctransform(GameObject* go) : Component(go) 
    {
        id = Count++;
    }
    ~Ctransform() override
    {
        --Count;
    }

    void SetPosition(float _x, float _y)
    {
        x = _x;
        y = _y;
    }
    void OffsetPosition(float _x, float _y)
    {
        x += _x;
        y += _y;
    }

    void Update() override;
    void Render() override;
};

