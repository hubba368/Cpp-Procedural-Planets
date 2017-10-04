#pragma once

#include "Vector3.h"
#include <stdlib.h>
#include <math.h>

/**
*
*/
class Quaternion
{
private:
	
	Vector3		_mVector;
	float		_mScalar;

public:
	Quaternion();
	~Quaternion();

	/// Gets a Vector3.
	Vector3&	GetVector();

	///	Gets a float scalar value.
	float		GetScalar();

	/// Allows access for vector elements.
	const float&operator [] (int index);

	/// Quaternion addition operator.
	Quaternion	operator + (Quaternion& val);

	/// Quaternion multiplication operator.
	Quaternion	operator * (Quaternion& val);

	/// Gets the conjugate of the input quaternion.
	Quaternion	GetConjugate(Quaternion& val);

	/// Gets the square root for quaternion normalisation.
	float		GetSquareRoot();

	/// Converts a quaternion to a rotation matrix.
	void		ConvertToRotationMatrix(float* rot);

	///
	//void		SetQuaternion(float vx, float vy, float vz, float scalar);

	/// Sets a quaternion based on a given Vector3 and float scalar value.
	void		SetQuaternion(Vector3& vec, float scalar);


};

