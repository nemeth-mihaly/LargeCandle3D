#include "Maths/Quaternion.hpp"

/*-------------------------------------------------------------------------
 *  Quaternion.cpp
 *-----------------------------------------------------------------------*/

/*
 *  Impl. of Quaternion
 */

Quaternion::Quaternion()
{
  X = 0.0f;
  Y = 0.0f;
  Z = 0.0f;
  W = 1.0f;
}

Quaternion::Quaternion(float x, float y, float z, float w)
  : X(x), Y(y), Z(z), W(w)
{

}

Quaternion::Quaternion(float angle, const Vector3& axis)
{
  glm::quat q = glm::angleAxis(angle, Vector3ToGlmvec3(axis));
  X = q.x;
  Y = q.y;
  Z = q.z;
  W = q.w;
}

Quaternion Quaternion::operator*(const Quaternion& q) const
{
  return Quaternion(
    ((W * q.X) + (X * q.W) + (Y * q.Z) - (Z *  q.Y)),
    ((W * q.Y) + (Y * q.W) + (Z * q.X) - (X *  q.Z)),
    ((W * q.Z) + (Z * q.W) + (X * q.Y) - (Y *  q.X)),
    ((W * q.W) - (X * q.W) - (Y * q.Y) - (Z *  q.Z)));
}

Vector3 Quaternion::operator*(const Vector3& v) const
{
  float tX = (((W * v.X) + (Y * v.Z)) - (Z * v.Y));
  float tY = (((W * v.Y) + (Z * v.X)) - (X * v.Z));
  float tZ = (((W * v.Z) + (X * v.Y)) - (Y * v.X));
  float tW = (((X * v.X) + (Y * v.Y)) + (Z * v.Z));

  return Vector3(
    ((((tW * X) + (tX * W)) - (tY * Z)) + (tZ * Y)),
    ((((tW * Y) + (tY * W)) - (tZ * X)) + (tX * Z)),
    ((((tW * Z) + (tZ * W)) - (tX * Y)) + (tY * X)));
}

float Quaternion::Length() const
{
  return sqrtf(
    ((X * X) + (Y * Y) + (Z * Z) + (W * W)));
}

Quaternion& Quaternion::Normalize()
{
  float len = Length();

  if (len)
  {
    len = 1.0f / len;

    X *= len;
    Y *= len;
    Z *= len;
    W *= len;
  }

  return *this;
}

/*
 *  GlmquatToQuaternion
 */
Quaternion GlmquatToQuaternion(const glm::quat& q)
{
  Quaternion result;
  result.X = q.x;
  result.Y = q.y;
  result.Z = q.z;
  result.W = q.w;

  return result;
}

/*
 *  QuaternionToGlmquat
 */
glm::quat QuaternionToGlmquat(const Quaternion& q)
{
  glm::quat result;
  result.x = q.X;
  result.y = q.Y;
  result.z = q.Z;
  result.w = q.W;

  return result;
}