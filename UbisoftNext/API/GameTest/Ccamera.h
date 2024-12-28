#pragma once
#include "Component.h"
#include "cameraManager.h"

class Ccamera :
    public Component
{
private:
    Camera* m_camera;

public:

    Ccamera(CameraManager& manager,int id) : Component() ,m_camera(&manager.CreateCamera(id)) {
        
    }
    Ccamera(CameraManager& manager) : Component(), m_camera(&manager.GetMainCamera()) {
    }
    

    void Init() override;
    void Update() override;

};

