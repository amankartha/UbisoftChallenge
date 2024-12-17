#pragma once
#include "Component.h"
#include "App/SimpleSprite.h"

class CRenderer :
    public Component
{


private:

    CSimpleSprite* sprite;


public:

    CRenderer(GameObject* go) : Component(go)
    {
        sprite = nullptr;
    }
    ~CRenderer() override
    {
       
    }

    void CreateSprite(const char* fileName,int columns, int rows)
    {
        sprite = App::CreateSprite(fileName, columns, rows);
    }

    void Update() override;

    void Render() override;

};

