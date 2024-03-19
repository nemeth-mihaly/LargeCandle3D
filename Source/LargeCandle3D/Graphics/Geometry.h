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

    Vector2();
    Vector2(f32 x, f32 y);
    Vector2(f32 value);

    Vector2& operator+=(const Vector2& other);
    Vector2& operator-=(const Vector2& other);
    Vector2& operator*=(const Vector2& other);
    Vector2& operator/=(const Vector2& other);
    
    Vector2& operator+=(f32 value);
    Vector2& operator-=(f32 value);
    Vector2& operator*=(f32 value);
    Vector2& operator/=(f32 value);

    friend Vector2 operator+(Vector2 left, const Vector2& right);
    friend Vector2 operator-(Vector2 left, const Vector2& right);
    friend Vector2 operator*(Vector2 left, const Vector2& right);
    friend Vector2 operator/(Vector2 left, const Vector2& right);

    friend Vector2 operator+(Vector2 left, f32 value);
    friend Vector2 operator-(Vector2 left, f32 value);
    friend Vector2 operator*(Vector2 left, f32 value);
    friend Vector2 operator/(Vector2 left, f32 value);

    const f32* AsValuePtr() const;

    Vector2& Add(const Vector2& other);
    Vector2& Subtract(const Vector2& other);
    Vector2& Multiply(const Vector2& other);
    Vector2& Divide(const Vector2& other);

    Vector2& Add(f32 value);
    Vector2& Subtract(f32 value);
    Vector2& Multiply(f32 value);
    Vector2& Divide(f32 value);

    f32 Length() const;
    Vector2& Normalize();
    f32 Distance(const Vector2& other) const;
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

    Vector3();
    Vector3(f32 x, f32 y, f32 z);
    Vector3(f32 value);

    Vector3& operator+=(const Vector3& other);
    Vector3& operator-=(const Vector3& other);
    Vector3& operator*=(const Vector3& other);
    Vector3& operator/=(const Vector3& other);
    
    Vector3& operator+=(f32 value);
    Vector3& operator-=(f32 value);
    Vector3& operator*=(f32 value);
    Vector3& operator/=(f32 value);

    friend Vector3 operator+(Vector3 left, const Vector3& right);
    friend Vector3 operator-(Vector3 left, const Vector3& right);
    friend Vector3 operator*(Vector3 left, const Vector3& right);
    friend Vector3 operator/(Vector3 left, const Vector3& right);

    friend Vector3 operator+(Vector3 left, f32 value);
    friend Vector3 operator-(Vector3 left, f32 value);
    friend Vector3 operator*(Vector3 left, f32 value);
    friend Vector3 operator/(Vector3 left, f32 value);

    const f32* AsValuePtr() const;

    Vector3& Add(const Vector3& other);
    Vector3& Subtract(const Vector3& other);
    Vector3& Multiply(const Vector3& other);
    Vector3& Divide(const Vector3& other);

    Vector3& Add(f32 value);
    Vector3& Subtract(f32 value);
    Vector3& Multiply(f32 value);
    Vector3& Divide(f32 value);

    f32 Length() const;
    Vector3& Normalize();
    f32 Distance(const Vector3& other) const;

    f32 Dot(const Vector3& other) const;
    Vector3 Cross(const Vector3& other) const;
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

    Vector4();
    Vector4(f32 x, f32 y, f32 z, f32 w);
    Vector4(f32 value);

    Vector4& operator+=(const Vector4& other);
    Vector4& operator-=(const Vector4& other);
    Vector4& operator*=(const Vector4& other);
    Vector4& operator/=(const Vector4& other);
    
    Vector4& operator+=(f32 value);
    Vector4& operator-=(f32 value);
    Vector4& operator*=(f32 value);
    Vector4& operator/=(f32 value);

    friend Vector4 operator+(Vector4 left, const Vector4& right);
    friend Vector4 operator-(Vector4 left, const Vector4& right);
    friend Vector4 operator*(Vector4 left, const Vector4& right);
    friend Vector4 operator/(Vector4 left, const Vector4& right);

    friend Vector4 operator+(Vector4 left, f32 value);
    friend Vector4 operator-(Vector4 left, f32 value);
    friend Vector4 operator*(Vector4 left, f32 value);
    friend Vector4 operator/(Vector4 left, f32 value);

    const f32* AsValuePtr() const;

    Vector4& Add(const Vector4& other);
    Vector4& Subtract(const Vector4& other);
    Vector4& Multiply(const Vector4& other);
    Vector4& Divide(const Vector4& other);

    Vector4& Add(f32 value);
    Vector4& Subtract(f32 value);
    Vector4& Multiply(f32 value);
    Vector4& Divide(f32 value);

    f32 Length() const;
    Vector4& Normalize();

    f32 Dot(const Vector4& other) const;
};

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

    Quaternion();
    Quaternion(f32 x, f32 y, f32 z, f32 w);
    // Builds a quaternion from an angle (radians) and a normalized axis.
    Quaternion(f32 angle, const Vector3& axis); 
};

//
//  Matrix4x4
//

class Matrix4x4
{
  public:
    f32   Data[4][4];

    Matrix4x4();
    Matrix4x4(f32 data[4][4]);

    Matrix4x4& operator*=(const Matrix4x4& other);
    friend Matrix4x4 operator*(Matrix4x4 left, const Matrix4x4& right);

    const f32* AsValuePtr() const;

    Matrix4x4& Multiply(const Matrix4x4& other);

    static Matrix4x4 g_Perspective(f32 fov, f32 width, f32 height, f32 near, f32 far);
    static Matrix4x4 g_LookAt(Vector3 eye, Vector3 center, Vector3 up);

    static Matrix4x4 g_Translate(const Vector3& translation);
    
    // TODO: g_Rotate();

    static Matrix4x4 g_Scale(const Vector3& scale);
};