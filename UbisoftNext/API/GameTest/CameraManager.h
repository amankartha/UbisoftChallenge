#pragma once
#include <vector>
#include <memory>
#include <Camera.h>
#include <cassert>
#include <unordered_map>

class CameraManager
{
	 std::unordered_map<int, std::unique_ptr<Camera>> m_cameras;
	 Camera* m_mainCamera;
public:
	 Camera& CreateCamera(const int id)
	{
		if (m_cameras.find(id) != m_cameras.end())
		{
			throw std::runtime_error("Camera with this ID already exists");
		}

		auto camera = std::make_unique<Camera>();
		Camera& ref = *camera;
		m_cameras[id] = std::move(camera);
		if (!m_mainCamera)
		{
			m_mainCamera = &ref;
		}
       
		return *m_cameras[id];
	}
    
     Camera& GetCamera(int id) {
        auto it = m_cameras.find(id);
        if (it == m_cameras.end()) {
            assert("Camera not found!");
        }
        return *(it->second);
    }

    
     void SetMainCamera(int id) {
        m_mainCamera = &GetCamera(id);
    }

   
     Camera& GetMainCamera() {
	 	assert(m_mainCamera && "Main camera not set!");
        return *m_mainCamera;
    }



  
     void RemoveCamera(int id) {
        if (m_mainCamera == m_cameras[id].get()) {
            throw std::runtime_error("Cannot remove the main camera!");
        }
        m_cameras.erase(id);
    }

};

