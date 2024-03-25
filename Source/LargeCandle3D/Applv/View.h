#pragma once

#include <memory>

#include "LargeCandle3D/Core/PrimTypes.h"
#include "LargeCandle3D/Graphics/CameraController.h"
#include "LargeCandle3D/Graphics/Scene.h"

class View
{
  friend class Application;

  public:
    IKeyboardHandler* m_pKeyboardHandler; 
    IMouseHandler* m_pMouseHandler;

    View();
    ~View();

    void OnUpdate(f32 deltaTime);
    
    void OnRender();
    void OnImGuiRender();

    bool OnKeyDown(i32 key);
    bool OnKeyUp(i32 key);

    bool OnMouseMove(f32 x, f32 y);
    bool OnMouseButtonDown(i32 button);
    bool OnMouseButtonUp(i32 button);

  private:
    std::shared_ptr<Scene> m_pScene;

    std::shared_ptr<CameraNode> m_pCamera;
    CameraController* m_pCameraController;
};