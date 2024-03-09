#pragma once

#include <vector>

#include "LargeCandle3D/Vendor/glad/glad.h"

#include "LargeCandle3D/Core/PrimTypes.h"
#include "LargeCandle3D/Rendering/Geometry.h"

struct Vertex
{
  glm::vec3   Position;
  
  Vertex(const glm::vec3& position) 
    : Position(position) {}
};

class Mesh
{
  public:
    Mesh(const std::vector<Vertex>& vertices);
    Mesh(const std::vector<Vertex>& vertices, 
      const std::vector<u32>& indices);

    ~Mesh();

    void OnRender() const;

  private:
    bool m_bIsBufferTypeIndex;

    std::vector<Vertex>    m_VData;
    std::vector<u32>    m_IData;

    u32   m_VAO;
    u32   m_VBO;
    u32   m_IBO;
};

extern std::vector<Vertex>    g_CubeVData; // Not indexed.