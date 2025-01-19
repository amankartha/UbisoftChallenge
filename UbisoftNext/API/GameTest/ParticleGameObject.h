#pragma once
#include "GameObject.h"
class ParticleGameObject :
    public GameObject
{

public:

    void Free();
    void Update(float DeltaTime) override;
    void Start();
};

