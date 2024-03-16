#pragma once

#include <vector>

#include "LargeCandle3D/Vendor/glad/glad.h"

#include "LargeCandle3D/Core/PrimTypes.h"

#include "LargeCandle3D/Graphics/Geometry.h"

//-----------------------------------------------
//    Forward declarations
//-----------------------------------------------

class Vertex3D;

//-----------------------------------------------
//
//-----------------------------------------------

extern std::vector<Vertex3D> g_PlaneVertices;
extern std::vector<Vertex3D> g_CubeVertices;

//
// struct Vertex3D
//

struct Vertex3D
{
  glm::vec3   Position;
  glm::vec3   Normal;
  glm::vec2   TexCoords;
  
  Vertex3D(const glm::vec3& position, const glm::vec3& normal, const glm::vec2& texCoords) 
    : Position(position), Normal(normal), TexCoords(texCoords) {}
};

//
// class Mesh
//

class Mesh
{
  public:
    Mesh(const std::vector<Vertex3D>& vertices);
    Mesh(const std::vector<Vertex3D>& vertices, 
      const std::vector<u32>& indices);

    ~Mesh();

    void OnRender() const;

  private:
    bool m_bIsBufferTypeIndex;

    std::vector<Vertex3D> m_Vertices;
    std::vector<u32> m_Indices;

    u32 m_VAO;
    u32 m_VBO;
    u32 m_IBO;
};