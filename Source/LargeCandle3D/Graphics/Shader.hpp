#pragma once

#include <stdint.h>
#include "Maths/Vector.hpp"

/*-------------------------------------------------------------------------
 *  Shader.hpp
 *-----------------------------------------------------------------------*/

/*
 *  Shader
 */
class Shader
{
  public:
    Shader(const char* vertSource, const char* fragSource);
    ~Shader();

    void Use() const;

#if USE_GLM
    void SetUniformBool(const char* name, bool value) const;
    void SetUniform1i(const char* name, int value) const;
    void SetUniform1f(const char* name, float value) const;
    void SetUniform2f(const char* name, const Vector2& values) const;
    void SetUniform3f(const char* name, const Vector3& vector3) const;
    void SetUniform4f(const char* name, const glm::vec4& values) const;
    void SetUniformMat4x4(const char* name, const glm::mat4& mat4x4) const;
#else
    void SetUniformBool(const char* name, bool value) const;
    void SetUniform1i(const char* name, int value) const;
    void SetUniform1f(const char* name, float value) const;
    void SetUniform2f(const char* name, const Vector2& values) const;
    void SetUniform3f(const char* name, const Vector3& values) const;
    void SetUniform4f(const char* name, const Vector4& values) const;
    void SetUniformMat4x4(const char* name, const Matrix4x4& mat4x4) const;
#endif

  private:
    uint32_t Compile(const char* source, uint32_t type) const;
    void CheckError(uint32_t renderID, bool bIsProgram = false) const;

  private:
    uint32_t    m_ProgramID;
};