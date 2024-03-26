#pragma once

#include <stdint.h>
#include <vector>
#include "Vendor/glad/glad.h"
#include "Maths/Vector.hpp"

/*-------------------------------------------------------------------------
 *  Mesh.hpp
 *-----------------------------------------------------------------------*/

/*
 *  Vertex3D
 */
struct Vertex3D
{
  Vector3   Position;
  Vector3   Normal;
  Vector2   TexCoords;
  
  Vertex3D(const Vector3& position, const Vector3& normal, const Vector2& texCoords) 
    : Position(position), Normal(normal), TexCoords(texCoords) {}
};

/*
 *  g_PlaneVertices
 */
extern std::vector<Vertex3D> g_PlaneVertices;

/*
 *  g_CubeVertices
 */
extern std::vector<Vertex3D> g_CubeVertices;

/*
 *  Mesh
 */
class Mesh
{
  public:
    Mesh(const std::vector<Vertex3D>& vertices);
    Mesh(const std::vector<Vertex3D>& vertices, 
      const std::vector<uint32_t>& indices);

    ~Mesh();

    void OnRender() const;

  private:
    bool m_bIsBufferTypeIndex;

    std::vector<Vertex3D> m_Vertices;
    std::vector<uint32_t> m_Indices;

    uint32_t m_VAO;
    uint32_t m_VBO;
    uint32_t m_IBO;
};