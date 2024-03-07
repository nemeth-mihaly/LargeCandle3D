#pragma once

#include "LargeCandle3D/Core/PrimTypes.h"

#include "LargeCandle3D/Applv/Interfaces.h"

#include "LargeCandle3D/Vendor/GLFW/glfw3.h"

#include "LargeCandle3D/Vendor/glm/glm.hpp"
#include "LargeCandle3D/Vendor/glm/gtc/matrix_transform.hpp"
#include "LargeCandle3D/Vendor/glm/gtc/type_ptr.hpp"
#include "LargeCandle3D/Vendor/glm/gtc/quaternion.hpp"
#include "LargeCandle3D/Vendor/glm/gtx/quaternion.hpp"

#include "LargeCandle3D/Rendering/Camera.h"

class CameraController : public IKeyboardHandler, public IMouseHandler 
{
  public:
    CameraController();
    CameraController(Camera& camera);

    void OnUpdate(f32 deltaTime);

    bool VOnKeyDown(i32 keyCode);
    bool VOnKeyUp(i32 keyCode);

    bool VOnMouseMove(f32 x, f32 y);
    bool VOnMouseButtonDown(i32 buttonCode);
    bool VOnMouseButtonUp(i32 buttonCode);

  private:
    Camera*     m_pCamera;

    bool        m_bKeysDown[GLFW_KEY_LAST];

    glm::vec2   m_MousePos;
    glm::vec2   m_PrevMousePos;
};