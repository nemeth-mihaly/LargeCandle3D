#pragma once

#include <memory>

#define GLFW_INCLUDE_NONE
#include "LargeCandle3D/Vendor/GLFW/glfw3.h"

#include "LargeCandle3D/Core/PrimTypes.h"

#include "LargeCandle3D/Applv/Input.h"

#include "LargeCandle3D/Graphics/Geometry.h"
#include "LargeCandle3D/Graphics/Camera.h"

//-----------------------------------------------
//
//-----------------------------------------------

//
// class CameraController
//

class CameraController : public IKeyboardHandler, public IMouseHandler 
{
  public:
    CameraController(const std::shared_ptr<Camera>& pCamera);

    void OnUpdate(f32 deltaTime);

    bool VOnKeyDown(i32 key);
    bool VOnKeyUp(i32 key);

    bool VOnMouseMove(f32 x, f32 y);
    bool VOnMouseButtonDown(i32 button);
    bool VOnMouseButtonUp(i32 button);

  private:
    std::shared_ptr<Camera> m_pCamera;

    bool m_bKeysDown[GLFW_KEY_LAST];

    glm::vec2 m_MousePos;
    glm::vec2 m_PrevMousePos;
};