#include "LargeCandle3D/Graphics/Geometry.h"

Vector3 g_Forward(0.0f, 0.0f, -1.0f);
Vector3 g_Right(1.0f, 0.0f, 0.0f);
Vector3 g_Up(0.0f, 1.0f, 0.0f);

f32 Radians(f32 degrees)
{
  constexpr f32 PI = 3.1415926535f;
  return degrees * PI / 180.0f;
}

static f32 Cot(f32 angle)
{
  return 1.0f / tanf(angle);
}

Matrix4x4 Translate(const Vector3& tv)
{
  Matrix4x4 mat4x4;
  mat4x4.Data[3][0] = tv.X;
  mat4x4.Data[3][1] = tv.Y;
  mat4x4.Data[3][2] = tv.Z;

  return mat4x4;
}

Matrix4x4 Scale(const Vector3& sv)
{
  Matrix4x4 mat4x4;
  mat4x4.Data[0][0] = sv.X;
  mat4x4.Data[1][1] = sv.Y;
  mat4x4.Data[2][2] = sv.Z;

  return mat4x4;
}

Matrix4x4 Perspective(f32 fieldOfView, f32 width, f32 height, f32 zNear, f32 zFar)
{
  const f32 tanHalfFieldOfView = tan(fieldOfView / 2.0f);
  const f32 aspect = width / height;

  Matrix4x4 mat4x4;
  mat4x4.Data[0][0] = 1.0f / (aspect * tanHalfFieldOfView);
  mat4x4.Data[1][1] = 1.0f / tanHalfFieldOfView;
  mat4x4.Data[2][2] = -(zFar + zNear) / (zFar - zNear);
  mat4x4.Data[2][3] = -1.0f;
  mat4x4.Data[3][2] = -(2.0f * zNear * zFar) / (zFar - zNear);
  mat4x4.Data[3][3] = 0.0f;

  return mat4x4;
}

Matrix4x4 LookAt(Vector3 eye, Vector3 center, Vector3 up)
{
  Vector3 f(Vector3::Normalize(center.Subtract(eye)));
  Vector3 s(Vector3::Normalize(f.Cross(up)));
  Vector3 u(s.Cross(f));

  Matrix4x4 mat4x4;
  mat4x4.Data[0][0] = s.X;
  mat4x4.Data[1][0] = s.Y;
  mat4x4.Data[2][0] = s.Z;
  mat4x4.Data[0][1] = u.X;
  mat4x4.Data[1][1] = u.Y;
  mat4x4.Data[2][1] = u.Z;
  mat4x4.Data[0][2] = -f.X;
  mat4x4.Data[1][2] = -f.Y;
  mat4x4.Data[2][2] = -f.Z;
  mat4x4.Data[3][0] = -s.Dot(eye);
  mat4x4.Data[3][1] = -u.Dot(eye);
  mat4x4.Data[3][2] = f.Dot(eye);

  return mat4x4;
}

//void CopyMatrix4x4From(const glm::mat4& glmMat4, Matrix4x4& mat4x4)
//{
//  for (int i = 0; i < 4; ++i) 
//  {
//    for (int j = 0; j < 4; ++j)
//      mat4x4.Data[i][j] = glmMat4[i][j];
//  }
//}

//void CopyMatrix4x4To(const Matrix4x4& mat4x4, glm::mat4& glmMat4)
//{
//  for (int i = 0; i < 4; ++i) 
//  {
//    for (int j = 0; j < 4; ++j)
//      glmMat4[i][j] = mat4x4.Data[i][j];
//  }
//}