#include "LargeCandle3D/Graphics/Shader.h"

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
  i32 uniformLocation = glGetUniformLocation(m_ProgramID, name);
  glUniform1i(uniformLocation, static_cast<i32>(value));
}

void Shader::SetUniform3f(const char* name, const glm::vec3& values) const
{
  i32 uniformLocation = glGetUniformLocation(m_ProgramID, name);
  glUniform3f(uniformLocation, values.x, values.y, values.z);
}

void Shader::SetUniformMat4x4(const char* name, const glm::mat4& mat4x4) const
{
  i32 uniformLocation = glGetUniformLocation(m_ProgramID, name);
  glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(mat4x4));
}

u32 Shader::Compile(const char* source, u32 type) const
{
  u32 shaderID = glCreateShader(type);
  glShaderSource(shaderID, 1, &source, nullptr);
  glCompileShader(shaderID);

  return shaderID;
}