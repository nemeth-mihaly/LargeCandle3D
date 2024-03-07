#pragma once

#include "LargeCandle3D/Core/PrimTypes.h"

#include "LargeCandle3D/Vendor/glm/glm.hpp"
#include "LargeCandle3D/Vendor/glm/gtc/matrix_transform.hpp"
#include "LargeCandle3D/Vendor/glm/gtc/type_ptr.hpp"

class Camera
{
  public:
    Camera();
    Camera(i32 width, i32 height);

    const glm::mat4& GetProjection() const { return m_Projection; }
    const glm::mat4& GetView() const { return m_View; }

    void SetPosition(const glm::vec3& position) { m_Position = position; }
    void SetForwardDirection(const glm::vec3& forwardDirection) { m_ForwardDirection = forwardDirection; }

    const glm::vec3& GetPosition() const { return m_Position; }
    const glm::vec3& GetForwardDirection() const { return m_ForwardDirection; }

    void RecalcView();

  private:
    glm::mat4     m_Projection;
    glm::mat4     m_View;

    glm::vec3     m_Position;
    glm::vec3     m_ForwardDirection;
};

extern glm::vec3 g_UpDirection;