#pragma once

#include <cmath>

extern float Radians(float degrees);

class Vector4
{
  public:
    float   X;
    float   Y;
    float   Z;
    float   W;

    Vector4();
    Vector4(float x, float y, float z, float w);
    Vector4(float value);

    Vector4& operator+=(const Vector4& other);
    Vector4& operator-=(const Vector4& other);
    Vector4& operator*=(const Vector4& other);
    Vector4& operator/=(const Vector4& other);
    
    Vector4& operator+=(float value);
    Vector4& operator-=(float value);
    Vector4& operator*=(float value);
    Vector4& operator/=(float value);

    friend Vector4 operator+(Vector4 left, const Vector4& right);
    friend Vector4 operator-(Vector4 left, const Vector4& right);
    friend Vector4 operator*(Vector4 left, const Vector4& right);
    friend Vector4 operator/(Vector4 left, const Vector4& right);

    friend Vector4 operator+(Vector4 left, float value);
    friend Vector4 operator-(Vector4 left, float value);
    friend Vector4 operator*(Vector4 left, float value);
    friend Vector4 operator/(Vector4 left, float value);

    const float* AsValuePtr() const;

    Vector4& Add(const Vector4& other);
    Vector4& Subtract(const Vector4& other);
    Vector4& Multiply(const Vector4& other);
    Vector4& Divide(const Vector4& other);

    Vector4& Add(float value);
    Vector4& Subtract(float value);
    Vector4& Multiply(float value);
    Vector4& Divide(float value);

    float Length() const;
    Vector4 Normalize() const;
    float Distance(const Vector4& other) const;

    float Dot(const Vector4& other) const;
};