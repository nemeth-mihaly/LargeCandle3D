#pragma once

#include "LC3/Core/PrimTypes.h"

// OpenGL
#include "LC3/Vendor/glad/glad.h"

class Shader
{
  public:
    Shader(const char* vertSource, const char* fragSource);
    ~Shader();

    void Use() const;

  private:
    u32 Compile(const char* source, u32 type) const;

  private:
    u32     m_ProgramID;
};