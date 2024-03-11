#include "LargeCandle3D/Graphics/Mesh.h"

std::vector<Vertex3D> g_CubeVertices =
{
  {{-0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}},
  {{ 0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}},
  {{ 0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}},
  {{ 0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}},
  {{-0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}},
  {{-0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}},

  {{-0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}},
  {{ 0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}},
  {{ 0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}},
  {{ 0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}},
  {{-0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}},
  {{-0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}},

  {{-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}},
  {{-0.5f,  0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}},
  {{-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}},
  {{-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}},
  {{-0.5f, -0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}},
  {{-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}},

  {{ 0.5f,  0.5f,  0.5f}, { 1.0f,  0.0f,  0.0f}},
  {{ 0.5f,  0.5f, -0.5f}, { 1.0f,  0.0f,  0.0f}},
  {{ 0.5f, -0.5f, -0.5f}, { 1.0f,  0.0f,  0.0f}},
  {{ 0.5f, -0.5f, -0.5f}, { 1.0f,  0.0f,  0.0f}},
  {{ 0.5f, -0.5f,  0.5f}, { 1.0f,  0.0f,  0.0f}},
  {{ 0.5f,  0.5f,  0.5f}, { 1.0f,  0.0f,  0.0f}},

  {{-0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}},
  {{ 0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}},
  {{ 0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}},
  {{ 0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}},
  {{-0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}},
  {{-0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}},

  {{-0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f}},
  {{ 0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f}},
  {{ 0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f}},
  {{ 0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f}},
  {{-0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f}},
  {{-0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f}}
};

//-----------------------------------------------
//    Impl. of Mesh class
//-----------------------------------------------

Mesh::Mesh(const std::vector<Vertex3D>& vertices)
  : m_Vertices(vertices)
{
  m_bIsBufferTypeIndex = false;

  glCreateBuffers(1, &m_VBO);	
  glNamedBufferData(m_VBO, sizeof(Vertex3D) * m_Vertices.size(), m_Vertices.data(), GL_STATIC_DRAW);

  glCreateVertexArrays(1, &m_VAO);

  glVertexArrayVertexBuffer(m_VAO, 0, m_VBO, 0, sizeof(Vertex3D));

  glEnableVertexArrayAttrib(m_VAO, 0);
  glEnableVertexArrayAttrib(m_VAO, 1);

  glVertexArrayAttribFormat(m_VAO, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex3D, Vertex3D::Position));
  glVertexArrayAttribFormat(m_VAO, 1, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex3D, Vertex3D::Normal));

  glVertexArrayAttribBinding(m_VAO, 0, 0);
  glVertexArrayAttribBinding(m_VAO, 1, 0);
}

Mesh::Mesh(const std::vector<Vertex3D>& vertices, 
  const std::vector<u32>& indices)
    : m_Vertices(vertices), m_Indices(indices)
{
  m_bIsBufferTypeIndex = true;

  glCreateBuffers(1, &m_VBO);	
  glNamedBufferData(m_VBO, sizeof(Vertex3D) * m_Vertices.size(), m_Vertices.data(), GL_STATIC_DRAW);

  glCreateBuffers(1, &m_IBO);
  glNamedBufferData(m_IBO, sizeof(u32) * m_Indices.size(), m_Indices.data(), GL_STATIC_DRAW);

  glCreateVertexArrays(1, &m_VAO);

  glVertexArrayVertexBuffer(m_VAO, 0, m_VBO, 0, sizeof(Vertex3D));
  glVertexArrayElementBuffer(m_VAO, m_IBO);

  glEnableVertexArrayAttrib(m_VAO, 0);
  glEnableVertexArrayAttrib(m_VAO, 1);

  glVertexArrayAttribFormat(m_VAO, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex3D, Vertex3D::Position));
  glVertexArrayAttribFormat(m_VAO, 1, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex3D, Vertex3D::Normal));

  glVertexArrayAttribBinding(m_VAO, 0, 0);
  glVertexArrayAttribBinding(m_VAO, 1, 0);
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
    glDrawArrays(GL_TRIANGLES, 0, m_Vertices.size());
  else
  {
    glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, nullptr);
  }
}