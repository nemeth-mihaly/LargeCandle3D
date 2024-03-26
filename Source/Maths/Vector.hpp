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

/*-------------------------------------------------------------------------
 *  Vector.hpp
 *-----------------------------------------------------------------------*/

/*
 *  Vector2
 */
class Vector2
{
  public:
    float X;
    float Y;

    Vector2();
    Vector2(float x, float y);
    Vector2(float scalar);

    Vector2 operator+(const Vector2& v) const;
    Vector2 operator-(const Vector2& v) const;
    Vector2 operator*(const Vector2& v) const;
    Vector2 operator/(const Vector2& v) const;

    Vector2& operator+=(const Vector2& v);
    Vector2& operator-=(const Vector2& v);
    Vector2& operator*=(const Vector2& v);
    Vector2& operator/=(const Vector2& v);
};

/*
 *  Glmvec3ToVector2
 */
extern Vector2 Glmvec2ToVector2(const glm::vec2& v);

/*
 *  Vector3ToGlmvec2
 */
extern glm::vec2 Vector2ToGlmvec2(const Vector2& v);

/*
 *  Vector3
 */
class Vector3
{
  public:
    float X;
    float Y;
    float Z;

    Vector3();
    
    Vector3(float x, float y, float z);
    Vector3(float scalar);

    Vector3 operator+(const Vector3& v) const;
    Vector3 operator-(const Vector3& v) const;
    Vector3 operator*(const Vector3& v) const;
    Vector3 operator/(const Vector3& v) const;

    Vector3& operator+=(const Vector3& v);
    Vector3& operator-=(const Vector3& v);
    Vector3& operator*=(const Vector3& v);
    Vector3& operator/=(const Vector3& v);

    Vector3 Cross(const Vector3& v) const;
};

/*
 *  Glmvec3ToVector3
 */
extern Vector3 Glmvec3ToVector3(const glm::vec3& v);

/*
 *  Vector3ToGlmvec3
 */
extern glm::vec3 Vector3ToGlmvec3(const Vector3& v);