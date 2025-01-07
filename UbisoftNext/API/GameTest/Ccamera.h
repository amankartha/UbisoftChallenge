#pragma once
#include "Component.h"
#include "cameraManager.h"
#include "GameObject.h"

class Ccamera :
    public Component
{
private:
    Camera* m_camera = 0;
public:
    Ccamera(CameraManager& manager,int id)  {
        m_camera = &manager.CreateCamera(id);
    }
    Ccamera(CameraManager& manager) :  m_camera(&manager.GetMainCamera()) {}
    void Init() override;
    void Update() override;
    void SetTransform(Transform* transform) const {m_camera->SetTransform(*transform);}
};

