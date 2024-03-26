#pragma once

#include <stdint.h>
#include <memory>
#include "LargeCandle3D/Graphics/CameraController.hpp"
#include "LargeCandle3D/Graphics/Scene.hpp"
#include "Maths/Math.hpp"

/*-------------------------------------------------------------------------
 *  View.hpp
 *-----------------------------------------------------------------------*/

/*
 *  View
 */
class View
{
  friend class Application;

  public:
    IKeyboardHandler*   m_pKeyboardHandler; 
    IMouseHandler*      m_pMouseHandler;

    View();
    ~View();

    void OnUpdate(float deltaTime);
    
    void OnRender();
    void OnImGuiRender();

    bool OnKeyDown(int key);
    bool OnKeyUp(int key);

    bool OnMouseMove(float x, float y);
    bool OnMouseButtonDown(int button);
    bool OnMouseButtonUp(int button);

  private:
    std::shared_ptr<Scene>        m_pScene;

    std::shared_ptr<CameraNode>   m_pCamera;
    CameraController*             m_pCameraController;
};