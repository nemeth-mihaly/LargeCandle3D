#include "LargeCandle3D/Graphics/Shader.hpp"

#include <stdio.h>
#include "Vendor/glad/glad.h"

/*-------------------------------------------------------------------------
 *  Shader.hpp
 *-----------------------------------------------------------------------*/

/*
 *  Impl. of Shader
 */

Shader::Shader(const char* vertSource, const char* fragSource)
{
  uint32_t vertShaderID = Compile(vertSource, GL_VERTEX_SHADER);
  uint32_t fragShaderID = Compile(fragSource, GL_FRAGMENT_SHADER);

  m_ProgramID = glCreateProgram();

  glAttachShader(m_ProgramID, vertShaderID);
  glAttachShader(m_ProgramID, fragShaderID);

  glLinkProgram(m_ProgramID);
  CheckError(m_ProgramID, true);

  glDeleteShader(vertShaderID);
  glDeleteShader(fragShaderID);
}

Shader::~Shader()
{
  glDeleteProgram(m_ProgramID);
}

void Shader::Use() const
{
  glUseProgram(m_ProgramID);
}

#if USE_GLM

void Shader::SetUniformBool(const char* name, bool value) const
{
  SetUniform1i(name, static_cast<int>(value));
}

void Shader::SetUniform1i(const char* name, int value) const
{
  int uniformLocation = glGetUniformLocation(m_ProgramID, name);
  glUniform1i(uniformLocation, value);
}

void Shader::SetUniform1f(const char* name, float value) const
{
  int uniformLocation = glGetUniformLocation(m_ProgramID, name);
  glUniform1f(uniformLocation, value);
}

void Shader::SetUniform2f(const char* name, const Vector2& values) const
{
  int uniformLocation = glGetUniformLocation(m_ProgramID, name);
  glUniform2f(uniformLocation, values.X, values.Y);
}

void Shader::SetUniform3f(const char* name, const Vector3& vector3) const
{
  int uniformLocation = glGetUniformLocation(m_ProgramID, name);
  glUniform3f(uniformLocation, vector3.X, vector3.Y, vector3.Z);
}

void Shader::SetUniform4f(const char* name, const glm::vec4& values) const
{
  int uniformLocation = glGetUniformLocation(m_ProgramID, name);
  glUniform4f(uniformLocation, values.x, values.y, values.z, values.w);
}

void Shader::SetUniformMat4x4(const char* name, const glm::mat4& mat4x4) const
{
  int uniformLocation = glGetUniformLocation(m_ProgramID, name);
  glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(mat4x4));
}

#else

void Shader::SetUniformBool(const char* name, bool value) const
{
  SetUniform1i(name, static_cast<int>(value));
}

void Shader::SetUniform1i(const char* name, int value) const
{
  int uniformLocation = glGetUniformLocation(m_ProgramID, name);
  glUniform1i(uniformLocation, value);
}

void Shader::SetUniform1f(const char* name, float value) const
{
  int uniformLocation = glGetUniformLocation(m_ProgramID, name);
  glUniform1f(uniformLocation, value);
}

void Shader::SetUniform2f(const char* name, const Vector2& values) const
{
  int uniformLocation = glGetUniformLocation(m_ProgramID, name);
  glUniform2f(uniformLocation, values.X, values.Y);
}

void Shader::SetUniform3f(const char* name, const Vector3& values) const
{
  int uniformLocation = glGetUniformLocation(m_ProgramID, name);
  glUniform3f(uniformLocation, values.X, values.Y, values.Z);
}

void Shader::SetUniform4f(const char* name, const Vector4& values) const
{
  int uniformLocation = glGetUniformLocation(m_ProgramID, name);
  glUniform4f(uniformLocation, values.X, values.Y, values.Z, values.W);
}

void Shader::SetUniformMat4x4(const char* name, const Matrix4x4& mat4x4) const
{
  int uniformLocation = glGetUniformLocation(m_ProgramID, name);
  glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, mat4x4.AsValuePtr());
}

#endif

uint32_t Shader::Compile(const char* source, uint32_t type) const
{
  uint32_t shaderID = glCreateShader(type);
  glShaderSource(shaderID, 1, &source, NULL);

  glCompileShader(shaderID);
  CheckError(shaderID);

  return shaderID;
}

void Shader::CheckError(uint32_t renderID, bool bIsProgram) const
{
  int result;
  char logBuffer[BUFSIZ];

  if (bIsProgram)
  {
    glGetProgramiv(renderID, GL_LINK_STATUS, &result);

    if (result == false)
      glGetProgramInfoLog(renderID, BUFSIZ, NULL, logBuffer);
    {
      return;
    }
  }
  else
  {
    glGetShaderiv(renderID, GL_COMPILE_STATUS, &result);

    if (result == false)
      glGetShaderInfoLog(renderID, BUFSIZ, NULL, logBuffer);
    else
    {
      return;
    }
  }

  fprintf(stderr, "%s \n", logBuffer);
}