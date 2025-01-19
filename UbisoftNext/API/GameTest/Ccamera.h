#pragma once
#include "Component.h"
#include "cameraManager.h"
#include "GameObject.h"

class Ccamera :
    public Component
{
public:
    Ccamera(GameObject* gameObject, CameraManager* manager,int id) : Component(gameObject) {
        m_camera = &manager->CreateCamera(id);
    }
    Ccamera(GameObject* gameObject,CameraManager* manager) :Component(gameObject),  m_camera(&manager->GetMainCamera()) {}
    void Init() override;
    void Update(float DeltaTime) override;
    void SetTransform(Ctransform* transform) const {m_camera->SetTransform(*transform);}

private:
    Camera* m_camera = 0;
};

