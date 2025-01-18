#pragma once
#include <memory>  


namespace GRID
{
	class GridSystem;
}

class GameObjectManager;
class Renderer;
class CameraManager;
class Scheduler;
namespace physics {
    class PhysicsSimulation;
}
class InputHandler;
class SceneManager;


class Game
{
protected:
   
    std::unique_ptr<GameObjectManager> m_gameObjectManager;
    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<CameraManager> m_cameraManager;
    std::unique_ptr<Scheduler> m_scheduler;
    std::unique_ptr<physics::PhysicsSimulation> m_physicsSimulation;
    std::unique_ptr<InputHandler> m_input_handler;
	std::unique_ptr<SceneManager> m_scene_manager;

public:
    
     Game();

    
    virtual ~Game();

    
    virtual void InternalInit();
    virtual void InternalUpdate(const float deltaTime);
    virtual void InternalRender();
    virtual void InternalShutdown() = 0;

   
    Renderer* GetRenderer() const;
    GameObjectManager* GetGameObjectManager() const;
    CameraManager* GetCameraManager() const;
    Scheduler* GetScheduler() const;
    physics::PhysicsSimulation* GetPhysicsSimulation() const;
    InputHandler* GetInputHandler();
	SceneManager* GetSceneManager();
    virtual GRID::GridSystem* GetGridSystem(); 

};