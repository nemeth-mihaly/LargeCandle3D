#include "LargeCandle3D/Rendering/Mesh.h"

std::vector<Vertex> g_CubeVData =
{
  {{ -0.5f, -0.5f, -0.5f }},
  {{  0.5f, -0.5f, -0.5f }},
  {{  0.5f,  0.5f, -0.5f }},
  {{  0.5f,  0.5f, -0.5f }},
  {{ -0.5f,  0.5f, -0.5f }},
  {{ -0.5f, -0.5f, -0.5f }},

  {{ -0.5f, -0.5f,  0.5f }},
  {{  0.5f, -0.5f,  0.5f }},
  {{  0.5f,  0.5f,  0.5f }},
  {{  0.5f,  0.5f,  0.5f }},
  {{ -0.5f,  0.5f,  0.5f }},
  {{ -0.5f, -0.5f,  0.5f }},

  {{ -0.5f,  0.5f,  0.5f }},
  {{ -0.5f,  0.5f, -0.5f }},
  {{ -0.5f, -0.5f, -0.5f }},
  {{ -0.5f, -0.5f, -0.5f }},
  {{ -0.5f, -0.5f,  0.5f }},
  {{ -0.5f,  0.5f,  0.5f }},

  {{  0.5f,  0.5f,  0.5f }},
  {{  0.5f,  0.5f, -0.5f }},
  {{  0.5f, -0.5f, -0.5f }},
  {{  0.5f, -0.5f, -0.5f }},
  {{  0.5f, -0.5f,  0.5f }},
  {{  0.5f,  0.5f,  0.5f }},

  {{ -0.5f, -0.5f, -0.5f }},
  {{  0.5f, -0.5f, -0.5f }},
  {{  0.5f, -0.5f,  0.5f }},
  {{  0.5f, -0.5f,  0.5f }},
  {{ -0.5f, -0.5f,  0.5f }},
  {{ -0.5f, -0.5f, -0.5f }},

  {{ -0.5f,  0.5f, -0.5f }},
  {{  0.5f,  0.5f, -0.5f }},
  {{  0.5f,  0.5f,  0.5f }},
  {{  0.5f,  0.5f,  0.5f }},
  {{ -0.5f,  0.5f,  0.5f }},
  {{ -0.5f,  0.5f, -0.5f }}
};

//-----------------------------------------------
//    Impl. of Mesh class
//-----------------------------------------------

Mesh::Mesh(const std::vector<Vertex>& vertices)
  : m_VData(vertices)
{
  m_bIsBufferTypeIndex = false;

  glCreateBuffers(1, &m_VBO);	
  glNamedBufferData(m_VBO, sizeof(Vertex) * m_VData.size(), m_VData.data(), GL_STATIC_DRAW);

  glCreateVertexArrays(1, &m_VAO);

  glVertexArrayVertexBuffer(m_VAO, 0, m_VBO, 0, sizeof(Vertex));

  glEnableVertexArrayAttrib(m_VAO, 0);
  glVertexArrayAttribFormat(m_VAO, 0, 3, GL_FLOAT, GL_FALSE, sizeof(f32) * 0);
  glVertexArrayAttribBinding(m_VAO, 0, 0);
}

Mesh::Mesh(const std::vector<Vertex>& vertices, 
  const std::vector<u32>& indices)
    : m_VData(vertices), m_IData(indices)
{
  m_bIsBufferTypeIndex = true;

  glCreateBuffers(1, &m_VBO);	
  glNamedBufferData(m_VBO, sizeof(Vertex) * m_VData.size(), m_VData.data(), GL_STATIC_DRAW);

  glCreateBuffers(1, &m_IBO);
  glNamedBufferData(m_IBO, sizeof(u32) * m_IData.size(), m_IData.data(), GL_STATIC_DRAW);

  glCreateVertexArrays(1, &m_VAO);

  glVertexArrayVertexBuffer(m_VAO, 0, m_VBO, 0, sizeof(Vertex));
  glVertexArrayElementBuffer(m_VAO, m_IBO);

  glEnableVertexArrayAttrib(m_VAO, 0);
  glVertexArrayAttribFormat(m_VAO, 0, 3, GL_FLOAT, GL_FALSE, sizeof(f32) * 0);
  glVertexArrayAttribBinding(m_VAO, 0, 0);
}

Mesh::~Mesh()
{
  if (m_bIsBufferTypeIndex)
    glDeleteBuffers(1, &m_IBO);
  
  glDeleteBuffers(1, &m_VBO);
  glDeleteVertexArrays(1, &m_VAO);
}

void Mesh::OnRender() const
{
  glBindVertexArray(m_VAO);
 
  if (!m_bIsBufferTypeIndex)
    glDrawArrays(GL_TRIANGLES, 0, m_VData.size());
  else
  {
    glDrawElements(GL_TRIANGLES, m_IData.size(), GL_UNSIGNED_INT, nullptr);
  }
}