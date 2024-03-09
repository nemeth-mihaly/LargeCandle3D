#pragma once

#include "LargeCandle3D/Vendor/glad/glad.h"

#include "LargeCandle3D/Core/PrimTypes.h"
#include "LargeCandle3D/Rendering/Geometry.h"

class Shader
{
  public:
    Shader(const char* vertSource, const char* fragSource);
    ~Shader();

    void Use() const;

    void SetUniformMat4x4(const char* name, const glm::mat4& mat4x4) const;

  private:
    u32 Compile(const char* source, u32 type) const;

  private:
    u32     m_ProgramID;
};