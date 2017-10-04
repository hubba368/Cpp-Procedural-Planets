#pragma once

#include "Vector4.h"
#include "Vector3.h"

class Matrix4x4
{
private:
	float	_mElement[4][4];


public:
	Matrix4x4();

	~Matrix4x4();

	/// Sets a matrix to an identity matrix (all components except diagonal have a value of 0).
	void				SetIdentity();

	/// Allows a matrix to be passed to an openGL method as an argument.
	float*				ToPtr();

	/// Matrix * Matrix multiplication.
	Matrix4x4			operator *(Matrix4x4& val);

	/// Matrix * Vector multiplication.
	Vector4				operator *(Vector4& val);

	/// Rotate a matrix about the X axis.
	void				RotateXAxis(float degrees);

	/// Rotate a matrix about the Y axis.
	void				RotateYAxis(float degrees);

	/// Rotate a matrix about the Z axis.
	void				RotateZAxis(float degrees);

	/// Translate a matrix by a given translation vector.
	void				Translate(Vector4& vec);

	/// Scale a matrix by given scale values, x, y or z.
	void				Scale(float sx, float sy, float sz);

	/// Set a matrix as a perspective matrix
	void				SetPerspective(float fovy, float aspect, float zNear, float zFar);

	/// Set a matrix as the view matrix for use by the main camera.
	void				SetViewMatrix(Vector3& cameraPosition, Vector3& viewVector, Vector3& upVector);
};

