#pragma once

#include <stdint.h>

//  The following includes are used for debugging custom math operations.
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#define   USE_GLM     1

#include "Maths/Vector.hpp"

/*-------------------------------------------------------------------------
 *  Matrix.hpp
 *-----------------------------------------------------------------------*/

/*
 *  Matrix4x4
 */
class Matrix4x4
{
  public:
#if USE_GLM
    glm::mat4   Data;
#else
    float       Data[4][4];
#endif

    Matrix4x4();
    Matrix4x4(float s);

    Matrix4x4 operator*(const Matrix4x4& m);
};

/*
 *  Perspective
 */
extern Matrix4x4 Perspective(float fovY, float width, float height, float zNear, float zFar);

/*
 *  LookAt
 */
extern Matrix4x4 LookAt(const Vector3& eye, const Vector3& center, const Vector3& up);

/*
 *  Translate
 */
extern Matrix4x4 Translate(const Vector3& v);

/*
 *  Rotate
 */
extern Matrix4x4 Rotate(float angle, const Vector3& v);

/*
 *  Scale
 */
extern Matrix4x4 Scale(const Vector3& v);