#include "Maths/Matrix.hpp"

#include <string.h>

#include "Maths/Vector.hpp"

/*-------------------------------------------------------------------------
 *  Matrix.cpp
 *-----------------------------------------------------------------------*/

/*
 *  Impl. of Matrix4x4
 */

Matrix4x4::Matrix4x4()
{
}

Matrix4x4::Matrix4x4(float s)
{
#if USE_GLM
  Data = glm::mat4(s);
#else

#endif
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& m)
{
  Matrix4x4 result;

#if USE_GLM
  result.Data = Data * m.Data;
#else

#endif

  return result;
}

/*
 *  Perspective
 */
Matrix4x4 Perspective(float fovY, float width, float height, float zNear, float zFar)
{
  const float ASPECT_RATIO = width / height;

  Matrix4x4 result;

#if USE_GLM
  result.Data = glm::perspective(fovY, ASPECT_RATIO, zNear, zFar);
#else

#endif

  return result;
}

/*
 *  LookAt
 */
Matrix4x4 LookAt(const Vector3& eye, const Vector3& center, const Vector3& up)
{
  Matrix4x4 result;

#if USE_GLM
  result.Data = glm::lookAt(Vector3ToGlmvec3(eye), Vector3ToGlmvec3(center), Vector3ToGlmvec3(up));
#else

#endif

  return result;
}

/*
 *  Translate
 */
Matrix4x4 Translate(const Vector3& v)
{
  Matrix4x4 result;

#if USE_GLM
  result.Data = glm::translate(glm::mat4(1.0f), Vector3ToGlmvec3(v));
#else

#endif

  return result;
}

/*
 *  Rotate
 */
Matrix4x4 Rotate(float angle, const Vector3& v)
{
  Matrix4x4 result;

#if USE_GLM
  result.Data = glm::rotate(glm::mat4(1.0f), angle, Vector3ToGlmvec3(v));
#else

#endif

  return result;
}

/*
 *  Scale
 */
Matrix4x4 Scale(const Vector3& v)
{
  Matrix4x4 result;

#if USE_GLM
  result.Data = glm::scale(glm::mat4(1.0f), Vector3ToGlmvec3(v));
#else

#endif

  return result;
}