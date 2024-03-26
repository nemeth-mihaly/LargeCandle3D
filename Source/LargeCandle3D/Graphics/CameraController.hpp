#pragma once

#include <stdint.h>
#include <memory>
#define GLFW_INCLUDE_NONE
#include "Vendor/GLFW/glfw3.h"
#include "LargeCandle3D/Applv/Input.hpp"
#include "LargeCandle3D/Graphics/SceneNodes.hpp"
#include "Maths/Math.hpp"

/*-------------------------------------------------------------------------
 *  Light.hpp
 *-----------------------------------------------------------------------*/

/*
 *  CameraController
 */
class CameraController : public IKeyboardHandler, public IMouseHandler 
{
  public:
    CameraController(const std::shared_ptr<CameraNode>& pCamera);

    void OnUpdate(float deltaTime);

    bool VOnKeyDown(int key);
    bool VOnKeyUp(int key);

    bool VOnMouseMove(float x, float y);
    bool VOnMouseButtonDown(int button);
    bool VOnMouseButtonUp(int button);

  private:
    std::shared_ptr<CameraNode> m_pCamera;

    float   m_Yaw;
    float   m_Pitch;

    bool m_bKeysDown[GLFW_KEY_LAST];
    bool m_bMouseButtonsDown[GLFW_MOUSE_BUTTON_LAST];

    Vector2   m_MousePos;
    Vector2   m_PrevMousePos;
};