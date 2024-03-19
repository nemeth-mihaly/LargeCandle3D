#pragma once

#include <string.h>
#include <cmath>

#include "LargeCandle3D/Core/PrimTypes.h"

//-----------------------------------------------
//    Forward declarations
//-----------------------------------------------

class Vector2;
class Vector3;
class Vector4;

//-----------------------------------------------
//
//-----------------------------------------------

extern Vector3 g_Forward;
extern Vector3 g_Right;
extern Vector3 g_Up;

extern f32 Radians(f32 degrees);

//
//  Vector2f
//

class Vector2
{
  public:
    f32   X;
    f32   Y;

    Vector2()
    {
      X = 0.0f;
      Y = 0.0f;
    }

    Vector2(f32 x, f32 y)
      : X(x), Y(y)
    {
    }
};

//
//  Vector3
//

class Vector3
{
  public:
    f32   X;
    f32   Y;
    f32   Z;

    Vector3()
    {
      X = 0.0f;
      Y = 0.0f;
      Z = 0.0f;
    }

    Vector3(f32 x, f32 y, f32 z)
      : X(x), Y(y), Z(z)
    {
    }

    Vector3& Subtract(const Vector3& other)
    {
      X -= other.X;
      Y -= other.Y;
      Z -= other.Z;
      return *this;
    }

    f32 Length() const
    {
      return sqrtf(X * X + Y * Y + Z * Z);
    }

    static Vector3 Normalize(const Vector3& vec3)
    {
      Vector3 result(vec3);
      f32 len = result.Length();

      result.X /= len;
      result.Y /= len;
      result.Z /= len;

      return result;
    }

    Vector3 Cross(const Vector3& other)
    {
      return Vector3({Y * other.Z - Z * other.Y}, 
                    {Z * other.X - X * other.Z}, 
                    {X * other.Y - Y * other.X});
    }

    f32 Dot(const Vector3& other)
    {
      return X * other.X + Y * other.Y + Z * other.Z;
    }
};

//
//  Vector4
//

class Vector4
{
  public:
    f32   X;
    f32   Y;
    f32   Z;
    f32   W;

    Vector4()
    {
      X = 0.0f;
      Y = 0.0f;
      Z = 0.0f;
      W = 0.0f;
    }

    Vector4(f32 x, f32 y, f32 z, f32 w)
      : X(x), Y(y), Z(z), W(w)
    {
    }
};

//
//  Matrix4x4
//

class Matrix4x4
{
  public:
    f32   Data[4][4];

    Matrix4x4()
    {
      memset(&Data[0][0], 0.0f, sizeof(Data));

      Data[0][0] = 1.0f;
      Data[1][1] = 1.0f;
      Data[2][2] = 1.0f;
      Data[3][3] = 1.0f;
    }

    Matrix4x4(f32 data[4][4])
    {
      memcpy(&Data[0][0], &data[0][0], sizeof(Data));
    }

    const f32* AsValuePtr() const
    {
      return reinterpret_cast<const f32*>(&Data[0][0]);
    }

    Matrix4x4& Multiply(const Matrix4x4& other)
    {
      // Row 0
      Data[0][0] = 
        Data[0][0] * other.Data[0][0] + 
        Data[0][1] * other.Data[1][0] + 
        Data[0][2] * other.Data[2][0] +
        Data[0][3] * other.Data[3][0];

      Data[0][1] = 
        Data[0][0] * other.Data[0][1] + 
        Data[0][1] * other.Data[1][1] + 
        Data[0][2] * other.Data[2][1] + 
        Data[0][3] * other.Data[3][1];

      Data[0][2] = 
        Data[0][0] * other.Data[0][2] + 
        Data[0][1] * other.Data[1][2] + 
        Data[0][2] * other.Data[2][2] + 
        Data[0][3] * other.Data[3][2];
      
      Data[0][3] = 
        Data[0][0] * other.Data[0][3] + 
        Data[0][1] * other.Data[1][3] + 
        Data[0][2] * other.Data[2][3] + 
        Data[0][3] * other.Data[3][3];

      // row 1
      Data[1][0] = 
        Data[1][0] * other.Data[0][0] + 
        Data[1][1] * other.Data[1][0] + 
        Data[1][2] * other.Data[2][0] + 
        Data[1][3] * other.Data[3][0];

      Data[1][1] = 
        Data[1][0] * other.Data[0][1] + 
        Data[1][1] * other.Data[1][1] + 
        Data[1][2] * other.Data[2][1] + 
        Data[1][3] * other.Data[3][1];

      Data[1][2] = 
        Data[1][0] * other.Data[0][2] + 
        Data[1][1] * other.Data[1][2] + 
        Data[1][2] * other.Data[2][2] + 
        Data[1][3] * other.Data[3][2];

      Data[1][3] = 
        Data[1][0] * other.Data[0][3] +
        Data[1][1] * other.Data[1][3] +
        Data[1][2] * other.Data[2][3] +
        Data[1][3] * other.Data[3][3];

      // row 2
      Data[2][0] = 
        Data[2][0] * other.Data[0][0] +
        Data[2][1] * other.Data[1][0] +
        Data[2][2] * other.Data[2][0] +
        Data[2][3] * other.Data[3][0];

      Data[2][1] = 
        Data[2][0] * other.Data[0][1] + 
        Data[2][1] * other.Data[1][1] + 
        Data[2][2] * other.Data[2][1] + 
        Data[2][3] * other.Data[3][1];

      Data[2][2] = 
        Data[2][0] * other.Data[0][2] +
        Data[2][1] * other.Data[1][2] + 
        Data[2][2] * other.Data[2][2] + 
        Data[2][3] * other.Data[3][2];

      Data[2][3] = 
        Data[2][0] * other.Data[0][3] + 
        Data[2][1] * other.Data[1][3] + 
        Data[2][2] * other.Data[2][3] + 
        Data[2][3] * other.Data[3][3];

      // row 3
      Data[3][0] = 
        Data[3][0] * other.Data[0][0] + 
        Data[3][1] * other.Data[1][0] + 
        Data[3][2] * other.Data[2][0] + 
        Data[3][3] * other.Data[3][0];

      Data[3][1] = 
        Data[3][0] * other.Data[0][1] + 
        Data[3][1] * other.Data[1][1] + 
        Data[3][2] * other.Data[2][1] + 
        Data[3][3] * other.Data[3][1];

      Data[3][2] = 
        Data[3][0] * other.Data[0][2] +
        Data[3][1] * other.Data[1][2] +
        Data[3][2] * other.Data[2][2] +
        Data[3][3] * other.Data[3][2];

      Data[3][3] = 
        Data[3][0] * other.Data[0][3] +
        Data[3][1] * other.Data[1][3] +
        Data[3][2] * other.Data[2][3] +
        Data[3][3] * other.Data[3][3];

      return *this;
    }
};

extern Matrix4x4 Translate(const Vector3& tv);
extern Matrix4x4 Scale(const Vector3& sv);
extern Matrix4x4 Perspective(f32 fieldOfView, f32 width, f32 height, f32 zNear, f32 zFar);
extern Matrix4x4 LookAt(Vector3 eye, Vector3 center, Vector3 up);

//extern void CopyMatrix4x4From(const glm::mat4& glmMat4, Matrix4x4& mat4x4);
//extern void CopyMatrix4x4To(const Matrix4x4& mat4x4, glm::mat4& glmMat4);

//
//  Quaternion
//

class Quaternion
{
  public:
    f32   X;
    f32   Y;
    f32   Z;
    f32   W;

    Quaternion()
    {
      X = 0.0f;
      Y = 0.0f;
      Z = 0.0f;
      W = 0.0f;
    }

    Quaternion(f32 x, f32 y, f32 z, f32 w)
      : X(x), Y(y), Z(z), W(w)
    {
    }

    // Builds a quaternion from an angle (radians) and a normalized axis.
    Quaternion(f32 angle, const Vector3& axis)
    {
      f32 s = sinf(angle * 0.5f);

      X = axis.X * s;
      Y = axis.Y * s;
      Z = axis.Z * s;
      W = cos(s);
    }


};