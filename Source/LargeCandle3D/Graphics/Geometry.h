#pragma once

#include <cmath>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#define USE_GLM 1

#include "LargeCandle3D/Core/PrimTypes.h"

extern f32 Radians(f32 degrees);

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
    Vector2 Normalize() const;
    f32 Distance(const Vector2& other) const;

    f32 Dot(const Vector2& other) const;
};

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
    f32* AsValuePtr();

    Vector3& Add(const Vector3& other);
    Vector3& Subtract(const Vector3& other);
    Vector3& Multiply(const Vector3& other);
    Vector3& Divide(const Vector3& other);

    Vector3& Add(f32 value);
    Vector3& Subtract(f32 value);
    Vector3& Multiply(f32 value);
    Vector3& Divide(f32 value);

    f32 Length() const;
    Vector3 Normalize() const;
    f32 Distance(const Vector3& other) const;

    f32 Dot(const Vector3& other) const;
    Vector3 Cross(const Vector3& other) const;

    static Vector3 Forward();
    static Vector3 Right();
    static Vector3 Up();
};

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
    Vector4 Normalize() const;
    f32 Distance(const Vector4& other) const;

    f32 Dot(const Vector4& other) const;
};

class Quaternion
{
  public:
    f32   X;
    f32   Y;
    f32   Z;
    f32   W;

    Quaternion();
    Quaternion(f32 x, f32 y, f32 z, f32 w);

    // Builds a quaternion from an angle in radians and a normalized axis.
    Quaternion(f32 angle, const Vector3& axis); 

    Quaternion Conjugate() const;

    f32 Length() const;
    Quaternion Normalize() const;
};

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

    static Matrix4x4 Perspective(f32 fovY, f32 width, f32 height, f32 zNear, f32 zFar);
    static Matrix4x4 LookAt(const Vector3& eye, const Vector3& center, const Vector3& up);

    static Matrix4x4 Translate(const Vector3& translation);

    //static Matrix4x4 Rotate(f32 angle, const Vector3& axis);

    static Matrix4x4 RotateX(f32 angle);
    static Matrix4x4 RotateY(f32 angle);
    static Matrix4x4 RotateZ(f32 angle);

    static Matrix4x4 Scale(const Vector3& scale);

    static Matrix4x4 Identity();
};