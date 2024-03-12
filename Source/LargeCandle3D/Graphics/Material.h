#pragma once

#include "LargeCandle3D/Core/PrimTypes.h"

#include "LargeCandle3D/Graphics/Geometry.h"

//-----------------------------------------------
//
//-----------------------------------------------

extern glm::vec3 g_White;
extern glm::vec3 g_Black;
extern glm::vec3 g_Cyan;
extern glm::vec3 g_Red;
extern glm::vec3 g_Green;
extern glm::vec3 g_Blue;
extern glm::vec3 g_Yellow;
extern glm::vec3 g_Gray40;
extern glm::vec3 g_Gray25;
extern glm::vec3 g_Gray65;

//
// class Material
//

class Material
{
  public:
    glm::vec3 Ambient;
    glm::vec3 Diffuse;
    glm::vec3 Specular;
    f32 Shininess;

    Material();
    ~Material();
};

//-----------------------------------------------
//    Real-world Materials
//      from: http://devernay.free.fr/cours/opengl/materials.html
//-----------------------------------------------
// Name        Ambient               Diffuse                    Specular                     Shininess
//-----------------------------------------------
// Emerald     (5.48, 44.50, 5.48)   (19.30, 156.63, 19.30)     (161.42, 185.59. 161.42)     76.8
// Jade
// Obsidian
// Pearl
// Ruby
// Turquoise
// Brass
// Bronze
// Chrome
// Copper
// Gold
// Silver
// Black Plastic
// Cyan Plastic
// Green Plastic
// Red Plastic
// White Plastic
// Yellow Plastic
// Black Rubber
// Cyan Rubber
// Green Rubber
// Red Rubber
// White Rubber
// Yellow Rubber