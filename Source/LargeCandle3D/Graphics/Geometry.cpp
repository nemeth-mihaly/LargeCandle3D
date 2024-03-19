#include "LargeCandle3D/Graphics/Geometry.h"

Vector3 g_Forward(0.0f, 0.0f, -1.0f);
Vector3 g_Right(1.0f, 0.0f, 0.0f);
Vector3 g_Up(0.0f, 1.0f, 0.0f);

f32 Radians(f32 degrees)
{
  constexpr f32 PI = 3.1415926535f;
  return degrees * PI / 180.0f;
}

//-----------------------------------------------
//    Impl. of Vector2 class
//-----------------------------------------------

Vector2::Vector2()
{
  X = 0.0f;
  Y = 0.0f;
}

Vector2::Vector2(f32 x, f32 y)
  : X(x), Y(y)
{
}

Vector2::Vector2(f32 value)
  : X(value), Y(value)
{
}

Vector2& Vector2::operator+=(const Vector2& other)
{
  return Add(other);
}

Vector2& Vector2::operator-=(const Vector2& other)
{
  return Subtract(other);
}

Vector2& Vector2::operator*=(const Vector2& other)
{
  return Multiply(other);
}

Vector2& Vector2::operator/=(const Vector2& other)
{
  return Divide(other);
}

Vector2& Vector2::operator+=(f32 value)
{
  return Add(value);
}

Vector2& Vector2::operator-=(f32 value)
{
  return Subtract(value);
}

Vector2& Vector2::operator*=(f32 value)
{
  return Multiply(value);
}

Vector2& Vector2::operator/=(f32 value)
{
  return Divide(value);
}

Vector2 operator+(Vector2 left, const Vector2& right)
{
  return left.Add(right);
}

Vector2 operator-(Vector2 left, const Vector2& right)
{
  return left.Subtract(right);
}

Vector2 operator*(Vector2 left, const Vector2& right)
{
  return left.Multiply(right);
}

Vector2 operator/(Vector2 left, const Vector2& right)
{
  return left.Divide(right);
}

Vector2 operator+(Vector2 left, f32 value)
{
  return left.Add(value);
}

Vector2 operator-(Vector2 left, f32 value)
{
  return left.Subtract(value);
}

Vector2 operator*(Vector2 left, f32 value)
{
  return left.Multiply(value);
}

Vector2 operator/(Vector2 left, f32 value)
{
  return left.Divide(value);
}

const f32* Vector2::AsValuePtr() const
{
  return reinterpret_cast<const f32*>(&X);
}

f32 Vector2::Length() const
{
  return sqrtf((X * X) + (Y * Y));
}

Vector2& Vector2::Add(const Vector2& other)
{
  X += other.X;
  Y += other.Y;

  return *this;
}

Vector2& Vector2::Subtract(const Vector2& other)
{
  X -= other.X;
  Y -= other.Y;

  return *this;
}

Vector2& Vector2::Multiply(const Vector2& other)
{
  X *= other.X;
  Y *= other.Y;

  return *this;
}

Vector2& Vector2::Divide(const Vector2& other)
{
  X /= other.X;
  Y /= other.Y;

  return *this;
}

Vector2& Vector2::Add(f32 value)
{
  X += value;
  Y += value;

  return *this;
}

Vector2& Vector2::Subtract(f32 value)
{
  X -= value;
  Y -= value;

  return *this;
}

Vector2& Vector2::Multiply(f32 value)
{
  X *= value;
  Y *= value;

  return *this;
}

Vector2& Vector2::Divide(f32 value)
{
  X /= value;
  Y /= value;

  return *this;
}

Vector2& Vector2::Normalize()
{
  f32 length = Length();
  Divide(length);

  return *this;
}

f32 Vector2::Distance(const Vector2& other) const
{
  Vector2 vector;
  vector.X = X - other.X;
  vector.Y = Y - other.Y;

  return vector.Length();
}

//-----------------------------------------------
//    Impl. of Vector3 class
//-----------------------------------------------

Vector3::Vector3()
{
  X = 0.0f;
  Y = 0.0f;
  Z = 0.0f;
}

Vector3::Vector3(f32 x, f32 y, f32 z)
  : X(x), Y(y), Z(z)
{
}

Vector3::Vector3(f32 value)
  : X(value), Y(value), Z(value)
{
}

Vector3& Vector3::operator+=(const Vector3& other)
{
  return Add(other);
}

Vector3& Vector3::operator-=(const Vector3& other)
{
  return Subtract(other);
}

Vector3& Vector3::operator*=(const Vector3& other)
{
  return Multiply(other);
}

Vector3& Vector3::operator/=(const Vector3& other)
{
  return Divide(other);
}

Vector3& Vector3::operator+=(f32 value)
{
  return Add(value);
}

Vector3& Vector3::operator-=(f32 value)
{
  return Subtract(value);
}

Vector3& Vector3::operator*=(f32 value)
{
  return Multiply(value);
}

Vector3& Vector3::operator/=(f32 value)
{
  return Divide(value);
}

Vector3 operator+(Vector3 left, const Vector3& right) 
{
  return left.Add(right);
}

Vector3 operator-(Vector3 left, const Vector3& right) 
{
  return left.Subtract(right);
}

Vector3 operator*(Vector3 left, const Vector3& right) 
{
  return left.Multiply(right);
}

Vector3 operator/(Vector3 left, const Vector3& right) 
{
  return left.Divide(right);
}

Vector3 operator+(Vector3 left, f32 value)
{
  return left.Add(value);
}

Vector3 operator-(Vector3 left, f32 value)
{
  return left.Subtract(value);
}

Vector3 operator*(Vector3 left, f32 value)
{
  return left.Multiply(value);
}

Vector3 operator/(Vector3 left, f32 value)
{
  return left.Divide(value);
}

const f32* Vector3::AsValuePtr() const
{
  return reinterpret_cast<const f32*>(&X);
}

Vector3& Vector3::Add(const Vector3& other) 
{
  X += other.X;
  Y += other.Y;
  Z += other.Z;

  return *this;
}

Vector3& Vector3::Subtract(const Vector3& other) 
{
  X -= other.X;
  Y -= other.Y;
  Z -= other.Z;

  return *this;
}

Vector3& Vector3::Multiply(const Vector3& other) 
{
  X *= other.X;
  Y *= other.Y;
  Z *= other.Z;

  return *this;
}

Vector3& Vector3::Divide(const Vector3& other) 
{
  X /= other.X;
  Y /= other.Y;
  Z /= other.Z;

  return *this;
}

Vector3& Vector3::Add(f32 value) 
{
  X += value;
  Y += value;
  Z += value;

  return *this;
}

Vector3& Vector3::Subtract(f32 value) 
{
  X -= value;
  Y -= value;
  Z -= value;

  return *this;
}

Vector3& Vector3::Multiply(f32 value) 
{
  X *= value;
  Y *= value;
  Z *= value;

  return *this;
}

Vector3& Vector3::Divide(f32 value) 
{
  X /= value;
  Y /= value;
  Z /= value;

  return *this;
}

f32 Vector3::Length() const
{
  return sqrtf((X * X) + (Y * Y) + (Z * Z));
}

Vector3& Vector3::Normalize()
{
  f32 length = Length();
  Divide(length);

  return *this;
}

f32 Vector3::Distance(const Vector3& other) const
{
  Vector3 vector;
  vector.X = X - other.X;
  vector.Y = Y - other.Y;
  vector.Z = Z - other.Z;

  return vector.Length();
}

f32 Vector3::Dot(const Vector3& other) const
{
  return (X * other.X) + (Y * other.Y) + (Z * other.Z);
}

Vector3 Vector3::Cross(const Vector3& other) const
{
  Vector3 resultVector;
  resultVector.X = (Y * other.Z) - (Z * other.Y);
  resultVector.Y = (Z * other.X) - (X * other.Z);
  resultVector.Z = (X * other.Y) - (Y * other.X);

  return resultVector;
}

//-----------------------------------------------
//    Impl. of Vector4 class
//-----------------------------------------------

Vector4::Vector4()
{
  X = 0.0f;
  Y = 0.0f;
  Z = 0.0f;
  W = 0.0f;
}

Vector4::Vector4(f32 x, f32 y, f32 z, f32 w)
  : X(x), Y(y), Z(z), W(w)
{
}

Vector4::Vector4(f32 value)
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

Vector4& Vector4::operator+=(f32 value)
{
  return Add(value);
}

Vector4& Vector4::operator-=(f32 value)
{
  return Subtract(value);
}

Vector4& Vector4::operator*=(f32 value)
{
  return Multiply(value);
}

Vector4& Vector4::operator/=(f32 value)
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

Vector4 operator+(Vector4 left, f32 value)
{
  return left.Add(value);
}

Vector4 operator-(Vector4 left, f32 value)
{
  return left.Subtract(value);
}

Vector4 operator*(Vector4 left, f32 value)
{
  return left.Multiply(value);
}

Vector4 operator/(Vector4 left, f32 value)
{
  return left.Divide(value);
}

const f32* Vector4::AsValuePtr() const
{
  return reinterpret_cast<const f32*>(&X);
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

Vector4& Vector4::Add(f32 value)
{
  X += value;
  Y += value;
  Z += value;
  W += value;

  return *this;
}

Vector4& Vector4::Subtract(f32 value)
{
  X -= value;
  Y -= value;
  Z -= value;
  W -= value;

  return *this;
}

Vector4& Vector4::Multiply(f32 value)
{
  X *= value;
  Y *= value;
  Z *= value;
  W *= value;

  return *this;
}

Vector4& Vector4::Divide(f32 value)
{
  X /= value;
  Y /= value;
  Z /= value;
  W /= value;

  return *this;
}

f32 Vector4::Length() const
{
  return sqrtf((X * X) + (Y * Y) + (Z * Z) + (W * W));
}

Vector4& Vector4::Normalize()
{
  f32 length = Length();
  Divide(length);

  return *this;
}

f32 Vector4::Dot(const Vector4& other) const
{
  return (X * other.X) + (Y * other.Y) + (Z * other.Z) + (W * other.W);
}

//-----------------------------------------------
//    Impl. of Quaternion class
//-----------------------------------------------

Quaternion::Quaternion()
{
  X = 0.0f;
  Y = 0.0f;
  Z = 0.0f;
  W = 1.0f;
}

Quaternion::Quaternion(f32 x, f32 y, f32 z, f32 w)
  : X(x), Y(y), Z(z), W(w)
{
}

Quaternion::Quaternion(f32 angle, const Vector3& axis)
{
  f32 s = sinf(angle * 0.5f);

  X = axis.X * s;
  Y = axis.Y * s;
  Z = axis.Z * s;
  W = cos(s);
}

//-----------------------------------------------
//    Impl. of Matrix4x4 class
//-----------------------------------------------

Matrix4x4::Matrix4x4()
{
  memset(&Data[0][0], 0.0f, sizeof(Data));

  Data[0][0] = 1.0f;
  Data[1][1] = 1.0f;
  Data[2][2] = 1.0f;
  Data[3][3] = 1.0f;
}

Matrix4x4::Matrix4x4(f32 data[4][4])
{
  memcpy(&Data[0][0], &data[0][0], sizeof(Data));
}

Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& other)
{
  return Multiply(other);
}

Matrix4x4 operator*(Matrix4x4 left, const Matrix4x4& right)
{
  return left.Multiply(right);
}

const f32* Matrix4x4::AsValuePtr() const
{
  return reinterpret_cast<const f32*>(&Data[0][0]);
}

Matrix4x4& Matrix4x4::Multiply(const Matrix4x4& other)
{
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

Matrix4x4 Matrix4x4::g_Perspective(f32 fov, f32 width, f32 height, f32 near, f32 far)
{
  const f32 halfFieldOfView = tan(fov / 2.0f);
  const f32 aspect = width / height;

  Matrix4x4 resultMatrix;
  resultMatrix.Data[0][0] = 1.0f / (aspect * halfFieldOfView);
  resultMatrix.Data[1][1] = 1.0f / halfFieldOfView;
  resultMatrix.Data[2][2] = -(far + near) / (far - near);
  resultMatrix.Data[2][3] = -1.0f;
  resultMatrix.Data[3][2] = -(2.0f * near * far) / (far - near);
  resultMatrix.Data[3][3] = 0.0f;

  return resultMatrix;
}

Matrix4x4 Matrix4x4::g_LookAt(Vector3 eye, Vector3 center, Vector3 up)
{
  const Vector3 f(Vector3(center - eye).Normalize());
  const Vector3 s(f.Cross(up).Normalize());
  const Vector3 u(s.Cross(f));

  Matrix4x4 resultMatrix;
  resultMatrix.Data[0][0] = s.X;
  resultMatrix.Data[1][0] = s.Y;
  resultMatrix.Data[2][0] = s.Z;
  resultMatrix.Data[0][1] = u.X;
  resultMatrix.Data[1][1] = u.Y;
  resultMatrix.Data[2][1] = u.Z;
  resultMatrix.Data[0][2] = -f.X;
  resultMatrix.Data[1][2] = -f.Y;
  resultMatrix.Data[2][2] = -f.Z;
  resultMatrix.Data[3][0] = -s.Dot(eye);
  resultMatrix.Data[3][1] = -u.Dot(eye);
  resultMatrix.Data[3][2] = f.Dot(eye);

  return resultMatrix;
}

Matrix4x4 Matrix4x4::g_Translate(const Vector3& translation)
{
  Matrix4x4 resultMatrix;
  resultMatrix.Data[3][0] = translation.X;
  resultMatrix.Data[3][1] = translation.Y;
  resultMatrix.Data[3][2] = translation.Z;

  return resultMatrix;
}

Matrix4x4 Matrix4x4::g_Scale(const Vector3& scale)
{
  Matrix4x4 resultMatrix;
  resultMatrix.Data[0][0] = scale.X;
  resultMatrix.Data[1][1] = scale.Y;
  resultMatrix.Data[2][2] = scale.Z;

  return resultMatrix;
}