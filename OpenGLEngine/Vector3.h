#pragma once

/**
* Implementation of 3D Vectors for 3D math usage.
*/
class Vector3
{
private:
	float	_mElement[3];

public:
	/// Default
	Vector3()
	{
		_mElement[0] = 0.0f;
		_mElement[1] = 0.0f;
		_mElement[2] = 0.0f;
	}

	Vector3(float x, float y, float z) 
	{
		_mElement[0] = x;
		_mElement[1] = y;
		_mElement[2] = z;
	}

	virtual ~Vector3() { ; }

	/// Allows access to each vector element.
	float operator [] (const int i) const;

	float& operator [] (const int i);

	/// Vector Addition operator.
	Vector3 operator + ( Vector3& val);

	/// Vector Subtraction operator.
	Vector3 operator - (Vector3& val);

	/// Vector assignment operator.
	Vector3& operator = (Vector3& val);

	/// Vector Multiplication operator.
	Vector3 operator * (Vector3& val);

	/// Scalar Multiplication operator.
	Vector3	operator * (float val);

	/// Sets a vector3 object to the inputted values.
	void	SetVector(float x, float y, float z);

	/// Returns magnitude (length) of a vector.
	float	GetMagnitude();

	/// Generates a normalised (unit) vector, a vector with a magnitude of 1.
	Vector3 Normalise();

	/// Vector * Vector multiplication - produces a third vector which is orthogonal to the inputs.
	Vector3 CrossProduct(Vector3& val);

	/// Vector * Vector multiplication - returns the cosine angle between 2 vectors.
	float	DotProduct(Vector3& val);

};

