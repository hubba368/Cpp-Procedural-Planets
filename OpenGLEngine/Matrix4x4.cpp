#include "Matrix4x4.h"
#include <math.h>
#include <memory.h>

#define PI_DIV_180 0.01745329251994329576923690768489f  //Used for calculating rotations

Matrix4x4::Matrix4x4()
{
	SetIdentity();
}


Matrix4x4::~Matrix4x4()
{
}


void Matrix4x4::SetIdentity()
{
	memset(&_mElement, 0, sizeof(_mElement));
	_mElement[0][0] = _mElement[1][1] = _mElement[2][2] = _mElement[3][3] = 1.0f;
}

float* Matrix4x4::ToPtr()
{
	return &_mElement[0][0];
}


Matrix4x4 Matrix4x4::operator * (Matrix4x4 & val)
{
	Matrix4x4 result;

	for (int r = 0; r < 4; r++)
		for (int c = 0; c < 4; c++)
			result._mElement[r][c] = _mElement[r][0] * val ._mElement[0][c]
			+ _mElement[r][1] * val._mElement[1][c]
			+ _mElement[r][2] * val._mElement[2][c]
			+ _mElement[r][3] * val._mElement[3][c];

	return result;
}


Vector4 Matrix4x4::operator * (Vector4 & val)
{
	Vector4 result;

	result = val;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result[i] += (_mElement[i][j] * result[j]);
		}
	}

	return result;
}


void Matrix4x4::RotateXAxis(float degrees)
{
	SetIdentity();

	float radian = degrees*PI_DIV_180;

	_mElement[1][1] = cosf(radian);
	_mElement[1][2] = -sinf(radian);
	_mElement[2][1] = sinf(radian);
	_mElement[2][2] = cosf(radian);
}


void Matrix4x4::RotateYAxis(float degrees)
{
	SetIdentity();

	float radian = degrees*PI_DIV_180;

	_mElement[0][0] = cosf(radian);
	_mElement[0][2] = sinf(radian);
	_mElement[2][0] = -sinf(radian);
	_mElement[2][2] = cosf(radian);
}


void Matrix4x4::RotateZAxis(float degrees)
{
	SetIdentity();

	float radian = degrees*PI_DIV_180;

	_mElement[0][0] = cosf(radian);
	_mElement[0][1] = -sinf(radian);
	_mElement[1][0] = sinf(radian);
	_mElement[1][1] = cosf(radian);
}


void Matrix4x4::Translate(Vector4 & vec)
{
	_mElement[3][0] = vec[0];
	_mElement[3][1] = vec[1];
	_mElement[3][2] = vec[2];
}


void Matrix4x4::Scale(float sx, float sy, float sz)
{
	_mElement[0][0] *= sx;
	_mElement[1][1] *= sy;
	_mElement[2][2] *= sz;
}


void Matrix4x4::SetPerspective(float fovy, float aspect, float zNear, float zFar)
{
	float radian = fovy*PI_DIV_180;
	float tan_fovy = tanf(radian*0.5f);

	memset(&_mElement, 0, sizeof(_mElement));

	_mElement[0][0] = 1.0f / (aspect * tan_fovy);
	_mElement[1][1] = 1.0f / tan_fovy;
	_mElement[2][2] = -(zFar + zNear) / (zFar - zNear);
	_mElement[2][3] = -1.0f;
	_mElement[3][2] = -(2.0f*zFar*zNear) / (zFar - zNear);
}


void Matrix4x4::SetViewMatrix(Vector3 & cameraPosition, Vector3 & viewVector, Vector3 & upVector)
{
	Vector3 zaxis = (cameraPosition - viewVector);
	zaxis.Normalise();
	Vector3 xaxis = upVector.CrossProduct(zaxis);
	xaxis.Normalise();
	Vector3 yaxis = zaxis.CrossProduct(xaxis);

	_mElement[0][0] = xaxis[0];
	_mElement[1][0] = xaxis[1];
	_mElement[2][0] = xaxis[2];

	_mElement[0][1] = yaxis[0];
	_mElement[1][1] = yaxis[1];
	_mElement[2][1] = yaxis[2];

	_mElement[0][2] = zaxis[0];
	_mElement[1][2] = zaxis[1];
	_mElement[2][2] = zaxis[2];

	_mElement[3][0] = -xaxis.DotProduct(cameraPosition);
	_mElement[3][1] = -yaxis.DotProduct(cameraPosition);
	_mElement[3][2] = -zaxis.DotProduct(cameraPosition);

	_mElement[0][3] = 0;
	_mElement[1][3] = 0;
	_mElement[2][3] = 0;
	_mElement[3][3] = 1.0f;
}
