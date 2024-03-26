#include "Maths/Vector.hpp"

/*-------------------------------------------------------------------------
 *  Vector.cpp
 *-----------------------------------------------------------------------*/

/*
 *  Impl. of Vector2
 */

Vector2::Vector2()
{
  X = 0.0f;
  Y = 0.0f;
}

Vector2::Vector2(float x, float y)
  : X(x), Y(y)
{
}

Vector2::Vector2(float scalar)
  : X(scalar), Y(scalar)
{
}

Vector2 Vector2::operator+(const Vector2& v) const
{
  return Vector2(
    X + v.X,
    Y + v.Y);
}

Vector2 Vector2::operator-(const Vector2& v) const
{
  return Vector2(
    X - v.X,
    Y - v.Y);
}

Vector2 Vector2::operator*(const Vector2& v) const
{
  return Vector2(
    X * v.X,
    Y * v.Y);
}

Vector2 Vector2::operator/(const Vector2& v) const
{
  return Vector2(
    X / v.X,
    Y / v.Y);
}

Vector2& Vector2::operator+=(const Vector2& v)
{
  X += v.X;
  Y += v.Y;

  return *this;
}

Vector2& Vector2::operator-=(const Vector2& v)
{
  X -= v.X;
  Y -= v.Y;

  return *this;
}

Vector2& Vector2::operator*=(const Vector2& v)
{
  X *= v.X;
  Y *= v.Y;

  return *this;
}

Vector2& Vector2::operator/=(const Vector2& v)
{
  X /= v.X;
  Y /= v.Y;

  return *this;
}

/*
 *  Glmvec3ToVector2
 */
Vector2 Glmvec2ToVector2(const glm::vec2& v)
{
  Vector2 result;
  result.X = v.x;
  result.Y = v.y;

  return result;
}

/*
 *  Vector3ToGlmvec2
 */
glm::vec2 Vector2ToGlmvec2(const Vector2& v)
{
  glm::vec2 result;
  result.x = v.X;
  result.y = v.Y;

  return result;
}

/*
 *  Impl. of Vector3
 */

Vector3::Vector3()
{
  X = 0.0f;
  Y = 0.0f;
  Z = 0.0f;
}

Vector3::Vector3(float x, float y, float z)
  : X(x), Y(y), Z(z)
{
}

Vector3::Vector3(float scalar)
  : X(scalar), Y(scalar), Z(scalar)
{
}

Vector3 Vector3::operator+(const Vector3& v) const
{
  return Vector3(
    X + v.X,
    Y + v.Y,
    Z + v.Z);
}

Vector3 Vector3::operator-(const Vector3& v) const
{
  return Vector3(
    X - v.X,
    Y - v.Y,
    Z - v.Z);
}

Vector3 Vector3::operator*(const Vector3& v) const
{
  return Vector3(
    X * v.X,
    Y * v.Y,
    Z * v.Z);
}

Vector3 Vector3::operator/(const Vector3& v) const
{
  return Vector3(
    X / v.X,
    Y / v.Y,
    Z / v.Z);
}

Vector3& Vector3::operator+=(const Vector3& v)
{
  X += v.X;
  Y += v.Y;
  Z += v.Z;

  return *this;
}

Vector3& Vector3::operator-=(const Vector3& v)
{
  X -= v.X;
  Y -= v.Y;
  Z -= v.Z;

  return *this;
}

Vector3& Vector3::operator*=(const Vector3& v)
{
  X *= v.X;
  Y *= v.Y;
  Z *= v.Z;

  return *this;
}

Vector3& Vector3::operator/=(const Vector3& v)
{
  X /= v.X;
  Y /= v.Y;
  Z /= v.Z;

  return *this;
}

Vector3 Vector3::Cross(const Vector3& v) const
{
  Vector3 result;

#if USE_GLM
  glm::vec3 glmvec3 = glm::cross(glm::vec3(X, Y, Z), Vector3ToGlmvec3(v));
  result = Glmvec3ToVector3(glmvec3);
#else

#endif

  return result;
}

/*
 *  Glmvec3ToVector3
 */
Vector3 Glmvec3ToVector3(const glm::vec3& v)
{
  Vector3 result;
  result.X = v.x;
  result.Y = v.y;
  result.Z = v.z;

  return result;
}

/*
 *  Vector3ToGlmvec3
 */
glm::vec3 Vector3ToGlmvec3(const Vector3& v)
{
  glm::vec3 result;
  result.x = v.X;
  result.y = v.Y;
  result.z = v.Z;

  return result;
}