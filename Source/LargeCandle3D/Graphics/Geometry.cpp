#include "LargeCandle3D/Graphics/Geometry.hpp"

#include <string.h>
#include <iostream>

float Radians(float degrees)
{
  constexpr float PI = 3.1415926535f;
  return degrees * PI / 180.0f;
}

//Vector3::Vector3()
//{
//  X = 0.0f;
//  Y = 0.0f;
//  Z = 0.0f;
//}
//
//Vector3::Vector3(float x, float y, float z)
//  : X(x), Y(y), Z(z)
//{
//}
//
//Vector3::Vector3(float value)
//  : X(value), Y(value), Z(value)
//{
//}
//
//Vector3& Vector3::operator+=(const Vector3& other)
//{
//  return Add(other);
//}
//
//Vector3& Vector3::operator-=(const Vector3& other)
//{
//  return Subtract(other);
//}
//
//Vector3& Vector3::operator*=(const Vector3& other)
//{
//  return Multiply(other);
//}
//
//Vector3& Vector3::operator/=(const Vector3& other)
//{
//  return Divide(other);
//}
//
//Vector3& Vector3::operator+=(float value)
//{
//  return Add(value);
//}
//
//Vector3& Vector3::operator-=(float value)
//{
//  return Subtract(value);
//}
//
//Vector3& Vector3::operator*=(float value)
//{
//  return Multiply(value);
//}
//
//Vector3& Vector3::operator/=(float value)
//{
//  return Divide(value);
//}
//
//Vector3 operator+(Vector3 left, const Vector3& right) 
//{
//  return left.Add(right);
//}
//
//Vector3 operator-(Vector3 left, const Vector3& right) 
//{
//  return left.Subtract(right);
//}
//
//Vector3 operator*(Vector3 left, const Vector3& right) 
//{
//  return left.Multiply(right);
//}
//
//Vector3 operator/(Vector3 left, const Vector3& right) 
//{
//  return left.Divide(right);
//}
//
//Vector3 operator+(Vector3 left, float value)
//{
//  return left.Add(value);
//}
//
//Vector3 operator-(Vector3 left, float value)
//{
//  return left.Subtract(value);
//}
//
//Vector3 operator*(Vector3 left, float value)
//{
//  return left.Multiply(value);
//}
//
//Vector3 operator/(Vector3 left, float value)
//{
//  return left.Divide(value);
//}
//
//const float* Vector3::AsValuePtr() const
//{
//  return reinterpret_cast<const float*>(&X);
//}
//
//float* Vector3::AsValuePtr()
//{
//  return reinterpret_cast<float*>(&X);
//}
//
//Vector3& Vector3::Add(const Vector3& other) 
//{
//  X += other.X;
//  Y += other.Y;
//  Z += other.Z;
//
//  return *this;
//}
//
//Vector3& Vector3::Subtract(const Vector3& other) 
//{
//  X -= other.X;
//  Y -= other.Y;
//  Z -= other.Z;
//
//  return *this;
//}
//
//Vector3& Vector3::Multiply(const Vector3& other) 
//{
//  X *= other.X;
//  Y *= other.Y;
//  Z *= other.Z;
//
//  return *this;
//}
//
//Vector3& Vector3::Divide(const Vector3& other) 
//{
//  X /= other.X;
//  Y /= other.Y;
//  Z /= other.Z;
//
//  return *this;
//}
//
//Vector3& Vector3::Add(float value) 
//{
//  X += value;
//  Y += value;
//  Z += value;
//
//  return *this;
//}
//
//Vector3& Vector3::Subtract(float value) 
//{
//  X -= value;
//  Y -= value;
//  Z -= value;
//
//  return *this;
//}
//
//Vector3& Vector3::Multiply(float value) 
//{
//  X *= value;
//  Y *= value;
//  Z *= value;
//
//  return *this;
//}
//
//Vector3& Vector3::Divide(float value) 
//{
//  X /= value;
//  Y /= value;
//  Z /= value;
//
//  return *this;
//}
//
//float Vector3::Length() const
//{
//  return sqrtf((X * X) + (Y * Y) + (Z * Z));
//}
//
//Vector3 Vector3::Normalize() const
//{
//  float length = Length();
//
//  Vector3 resultVector;
//  resultVector.X = X / length;
//  resultVector.Y = Y / length;
//  resultVector.Z = Z / length;
//
//  return resultVector;
//}
//
//float Vector3::Distance(const Vector3& other) const
//{
//  Vector3 vector;
//  vector.X = X - other.X;
//  vector.Y = Y - other.Y;
//  vector.Z = Z - other.Z;
//
//  return vector.Length();
//}
//
//float Vector3::Dot(const Vector3& other) const
//{
//  return (X * other.X) + (Y * other.Y) + (Z * other.Z);
//}
//
//Vector3 Vector3::Cross(const Vector3& other) const
//{
//  Vector3 resultVector;
//  resultVector.X = (Y * other.Z) - (Z * other.Y);
//  resultVector.Y = (Z * other.X) - (X * other.Z);
//  resultVector.Z = (X * other.Y) - (Y * other.X);
//
//  return resultVector;
//}
//
//Vector3 Vector3::Forward()
//{
//  return Vector3(0.0f, 0.0f, -1.0f);
//}
//
//Vector3 Vector3::Right()
//{
//  return Vector3(1.0f, 0.0f, 0.0f);
//}
//
//Vector3 Vector3::Up()
//{
//  return Vector3(0.0f, 1.0f, 0.0f);
//}

Vector4::Vector4()
{
  X = 0.0f;
  Y = 0.0f;
  Z = 0.0f;
  W = 0.0f;
}

Vector4::Vector4(float x, float y, float z, float w)
  : X(x), Y(y), Z(z), W(w)
{
}

Vector4::Vector4(float value)
  : X(value), Y(value), Z(value), W(value)
{
}

Vector4& Vector4::operator+=(const Vector4& other)
{
  return Add(other);
}

Vector4& Vector4::operator-=(const Vector4& other)
{
  return Subtract(other);
}

Vector4& Vector4::operator*=(const Vector4& other)
{
  return Multiply(other);
}

Vector4& Vector4::operator/=(const Vector4& other)
{
  return Divide(other);
}

Vector4& Vector4::operator+=(float value)
{
  return Add(value);
}

Vector4& Vector4::operator-=(float value)
{
  return Subtract(value);
}

Vector4& Vector4::operator*=(float value)
{
  return Multiply(value);
}

Vector4& Vector4::operator/=(float value)
{
  return Divide(value);
}

Vector4 operator+(Vector4 left, const Vector4& right) 
{
  return left.Add(right);
}

Vector4 operator-(Vector4 left, const Vector4& right) 
{
  return left.Subtract(right);
}

Vector4 operator*(Vector4 left, const Vector4& right) 
{
  return left.Multiply(right);
}

Vector4 operator/(Vector4 left, const Vector4& right) 
{
  return left.Divide(right);
}

Vector4 operator+(Vector4 left, float value)
{
  return left.Add(value);
}

Vector4 operator-(Vector4 left, float value)
{
  return left.Subtract(value);
}

Vector4 operator*(Vector4 left, float value)
{
  return left.Multiply(value);
}

Vector4 operator/(Vector4 left, float value)
{
  return left.Divide(value);
}

const float* Vector4::AsValuePtr() const
{
  return reinterpret_cast<const float*>(&X);
}

Vector4& Vector4::Add(const Vector4& other)
{
  X += other.X;
  Y += other.Y;
  Z += other.Z;
  W += other.W;

  return *this;
}

Vector4& Vector4::Subtract(const Vector4& other)
{
  X -= other.X;
  Y -= other.Y;
  Z -= other.Z;
  W -= other.W;

  return *this;
}

Vector4& Vector4::Multiply(const Vector4& other)
{
  X *= other.X;
  Y *= other.Y;
  Z *= other.Z;
  W *= other.W;

  return *this;
}

Vector4& Vector4::Divide(const Vector4& other)
{
  X /= other.X;
  Y /= other.Y;
  Z /= other.Z;
  W /= other.W;

  return *this;
}

Vector4& Vector4::Add(float value)
{
  X += value;
  Y += value;
  Z += value;
  W += value;

  return *this;
}

Vector4& Vector4::Subtract(float value)
{
  X -= value;
  Y -= value;
  Z -= value;
  W -= value;

  return *this;
}

Vector4& Vector4::Multiply(float value)
{
  X *= value;
  Y *= value;
  Z *= value;
  W *= value;

  return *this;
}

Vector4& Vector4::Divide(float value)
{
  X /= value;
  Y /= value;
  Z /= value;
  W /= value;

  return *this;
}

float Vector4::Length() const
{
  return sqrtf((X * X) + (Y * Y) + (Z * Z) + (W * W));
}

Vector4 Vector4::Normalize() const
{
  float length = Length();

  Vector4 resultVector;
  resultVector.X = X / length;
  resultVector.Y = Y / length;
  resultVector.Z = Z / length;
  resultVector.W = W / length;

  return resultVector;
}

float Vector4::Distance(const Vector4& other) const
{
  Vector4 vector;
  vector.X = X - other.X;
  vector.Y = Y - other.Y;
  vector.Z = Z - other.Z;
  vector.W = W - other.W;

  return vector.Length();
}

float Vector4::Dot(const Vector4& other) const
{
  return (X * other.X) + (Y * other.Y) + (Z * other.Z) + (W * other.W);
}

//Quaternion::Quaternion()
//{
//  X = 0.0f;
//  Y = 0.0f;
//  Z = 0.0f;
//  W = 1.0f;
//}
//
//Quaternion::Quaternion(float x, float y, float z, float w)
//  : X(x), Y(y), Z(z), W(w)
//{
//}
//
//Quaternion::Quaternion(float angle, const Vector3& axis)
//{
//  float sinHalfAngle = sinf(angle * 0.5f);
//
//  X = axis.X * sinHalfAngle;
//  Y = axis.Y * sinHalfAngle;
//  Z = axis.Z * sinHalfAngle;
//  W = cos(sinHalfAngle * 0.5f);
//}
//
//Quaternion Quaternion::Conjugate() const
//{
//  Quaternion resultQuat(-X, -Y, -Z, W);
//  return resultQuat;
//}
//
//float Quaternion::Length() const
//{
//  return sqrtf((X * X) + (Y * Y) + (Z * Z) + (W * W));
//}
//
//Quaternion Quaternion::Normalize() const
//{
//  float length = Length();
//
//  Quaternion resultQuat;
//  resultQuat.X = X / length;
//  resultQuat.Y = Y / length;
//  resultQuat.Z = Z / length;
//  resultQuat.W = W / length;
//
//  return resultQuat;
//}

//Matrix4x4::Matrix4x4()
//{
//  memset(&Data[0][0], 0.0f, sizeof(Data));
//
//  Data[0][0] = 1.0f;
//  Data[1][1] = 1.0f;
//  Data[2][2] = 1.0f;
//  Data[3][3] = 1.0f;
//}
//
//Matrix4x4::Matrix4x4(float data[4][4])
//{
//  memcpy(&Data[0][0], &data[0][0], 16 * sizeof(float));
//}
//
//Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& other)
//{
//  return Multiply(other);
//}
//
//Matrix4x4 operator*(Matrix4x4 left, const Matrix4x4& right)
//{
//  return left.Multiply(right);
//}
//
//const float* Matrix4x4::AsValuePtr() const
//{
//  return reinterpret_cast<const float*>(&Data[0][0]);
//}
//
//Matrix4x4& Matrix4x4::Multiply(const Matrix4x4& other)
//{
//  Matrix4x4 resultMatrix;
//
//  for (i32 i = 0; i < 4; i++)
//  {
//    for (i32 j = 0; j < 4; j++)
//    {
//      float sum = 0.0f;
//
//      for (i32 e = 0; e < 4; e++)
//        sum += Data[i][e] * other.Data[e][j];
//
//      resultMatrix.Data[i][j] = sum;
//    }
//  }
//
//  memcpy(&Data[0][0], &resultMatrix.Data[0][0], sizeof(resultMatrix));
//
//  return *this;
//}
//
//Matrix4x4 Matrix4x4::Perspective(float fovY, float width, float height, float zNear, float zFar)
//{
//  const float tanHalfFovY = tanf(fovY) * 0.5f;
//  const float aspect = width / height;
//
//  Matrix4x4 resultMatrix;
//  resultMatrix.Data[0][0] = 1.0f / (aspect * tanHalfFovY);
//  resultMatrix.Data[1][1] = 1.0f / tanHalfFovY;
//  resultMatrix.Data[2][2] = -(zFar + zNear) / (zFar - zNear);
//  resultMatrix.Data[2][3] = -1.0f;
//  resultMatrix.Data[3][2] = -(2.0f * zFar * zNear) / (zFar - zNear);
//  resultMatrix.Data[3][3] = 0.0f; 
//
//  return resultMatrix;
//}
//
//Matrix4x4 Matrix4x4::LookAt(const Vector3& eye, const Vector3& center, const Vector3& up)
//{
//  const Vector3 FORWARD(Vector3(center - eye).Normalize());
//  const Vector3 RIGHT(FORWARD.Cross(up).Normalize());
//  const Vector3 UP(RIGHT.Cross(FORWARD));
//
//  Matrix4x4 resultMatrix;
//  resultMatrix.Data[0][0] = RIGHT.X;
//  resultMatrix.Data[0][1] = RIGHT.Y;
//  resultMatrix.Data[0][2] = RIGHT.Z;
//  resultMatrix.Data[1][0] = UP.X;
//  resultMatrix.Data[1][1] = UP.Y;
//  resultMatrix.Data[1][2] = UP.Z;
//  resultMatrix.Data[2][0] = -FORWARD.X;
//  resultMatrix.Data[2][1] = -FORWARD.Y;
//  resultMatrix.Data[2][2] = -FORWARD.Z;
//  resultMatrix.Data[3][0] = -eye.Dot(RIGHT);
//  resultMatrix.Data[3][1] = -eye.Dot(UP);
//  resultMatrix.Data[3][2] = eye.Dot(FORWARD);
//
//  return resultMatrix;
//}
//
//Matrix4x4 Matrix4x4::Translate(const Vector3& translation)
//{
//  Matrix4x4 resultMatrix;
//  resultMatrix.Data[3][0] = translation.X;
//  resultMatrix.Data[3][1] = translation.Y;
//  resultMatrix.Data[3][2] = translation.Z;
//
//  return resultMatrix;
//}
//
////Matrix4x4 Matrix4x4::Rotate(float angle, const Vector3& axis)
////{
////}
//
//Matrix4x4 Matrix4x4::RotateX(float angle)
//{
//  const float c = cosf(angle);
//  const float s = sinf(angle);
//
//  Matrix4x4 resultMatrix;
//  resultMatrix.Data[1][1] = c;
//  resultMatrix.Data[1][2] = s;
//  resultMatrix.Data[2][1] = -s;
//  resultMatrix.Data[2][2] = c; 
//
//  return resultMatrix;
//}
//
//Matrix4x4 Matrix4x4::RotateY(float angle)
//{
//  const float c = cosf(angle);
//  const float s = sinf(angle);
//
//  Matrix4x4 resultMatrix;
//  resultMatrix.Data[0][0] = c;
//  resultMatrix.Data[0][2] = -s;
//  resultMatrix.Data[2][0] = s;
//  resultMatrix.Data[2][2] = c;
//
//  return resultMatrix;
//}
//
//Matrix4x4 Matrix4x4::RotateZ(float angle)
//{
//  const float c = cosf(angle);
//  const float s = sinf(angle);
//
//  Matrix4x4 resultMatrix;
//  resultMatrix.Data[0][0] = c;
//  resultMatrix.Data[0][1] = s;
//  resultMatrix.Data[1][0] = -s;
//  resultMatrix.Data[1][1] = c;
//
//  return resultMatrix;
//}
//
//Matrix4x4 Matrix4x4::Scale(const Vector3& scale)
//{
//  Matrix4x4 resultMatrix;
//  resultMatrix.Data[0][0] = scale.X;
//  resultMatrix.Data[1][1] = scale.Y;
//  resultMatrix.Data[2][2] = scale.Z;
//
//  return resultMatrix;
//}
//
//Matrix4x4 Matrix4x4::Identity()
//{
//  float data[4][4];
//  memset(&data[0][0], 0.0f, sizeof(data));
//
//  data[0][0] = 1.0f;
//  data[1][1] = 1.0f;
//  data[2][2] = 1.0f;
//  data[3][3] = 1.0f;
//
//  return Matrix4x4(data);
//}