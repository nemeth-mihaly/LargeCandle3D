#include "LargeCandle3D/Graphics/Shader.h"

#include <stdio.h>

#include "LargeCandle3D/Vendor/glad/glad.h"

//-----------------------------------------------
//    Impl. of Shader class
//-----------------------------------------------

Shader::Shader(const char* vertSource, const char* fragSource)
{
  u32 vertShaderID = Compile(vertSource, GL_VERTEX_SHADER);
  u32 fragShaderID = Compile(fragSource, GL_FRAGMENT_SHADER);

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

void Shader::SetUniformBool(const char* name, bool value) const
{
  //i32 uniformLocation = glGetUniformLocation(m_ProgramID, name);
  //glUniform1i(uniformLocation, static_cast<i32>(value));
  
  SetUniform1i(name, static_cast<i32>(value));
}

void Shader::SetUniform1i(const char* name, i32 value) const
{
  i32 uniformLocation = glGetUniformLocation(m_ProgramID, name);
  glUniform1i(uniformLocation, value);
}

void Shader::SetUniform1f(const char* name, f32 value) const
{
  i32 uniformLocation = glGetUniformLocation(m_ProgramID, name);
  glUniform1f(uniformLocation, value);
}

void Shader::SetUniform2f(const char* name, const glm::vec2& values) const
{
  i32 uniformLocation = glGetUniformLocation(m_ProgramID, name);
  glUniform2f(uniformLocation, values.x, values.y);
}

void Shader::SetUniform3f(const char* name, const glm::vec3& values) const
{
  i32 uniformLocation = glGetUniformLocation(m_ProgramID, name);
  glUniform3f(uniformLocation, values.x, values.y, values.z);
}

void Shader::SetUniform4f(const char* name, const glm::vec4& values) const
{
  i32 uniformLocation = glGetUniformLocation(m_ProgramID, name);
  glUniform4f(uniformLocation, values.x, values.y, values.z, values.w);
}

void Shader::SetUniformMat4x4(const char* name, const glm::mat4& mat4x4) const
{
  i32 uniformLocation = glGetUniformLocation(m_ProgramID, name);
  glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(mat4x4));
}

u32 Shader::Compile(const char* source, u32 type) const
{
  u32 shaderID = glCreateShader(type);
  glShaderSource(shaderID, 1, &source, NULL);

  glCompileShader(shaderID);
  CheckError(shaderID);

  return shaderID;
}

void Shader::CheckError(u32 renderID, bool bIsProgram) const
{
  i32 result;
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