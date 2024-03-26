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
 *  Quaternion.hpp
 *-----------------------------------------------------------------------*/

/*
 *  Quaternion
 */
class Quaternion
{
  public:
    float X;
    float Y;
    float Z;
    float W;

    Quaternion();
    Quaternion(float x, float y, float z, float w);
    Quaternion(float angle, const Vector3& axis);

    Quaternion operator*(const Quaternion& q) const;
    Vector3 operator*(const Vector3& v) const;

    float Length() const;
    Quaternion& Normalize();
};

/*
 *  GlmquatToQuaternion
 */
extern Quaternion GlmquatToQuaternion(const glm::quat& q);

/*
 *  QuaternionToGlmquat
 */
extern glm::quat QuaternionToGlmquat(const Quaternion& q);