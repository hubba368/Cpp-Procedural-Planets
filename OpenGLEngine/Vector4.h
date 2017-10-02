#pragma once

/**
* Implementation of 3D vectors with an additional 'w' magnitude component.
*/
class Vector4
{
private:
	float _mElement[4];

public:
	/// Default
	Vector4()
	{
		_mElement[0] = 0.0f;
		_mElement[1] = 0.0f;
		_mElement[2] = 0.0f;
		_mElement[3] = 1.0f;
	}

	Vector4(float x, float y, float z, float w = 1.0f)
	{
		_mElement[0] = x;
		_mElement[1] = y;
		_mElement[2] = z;
		_mElement[3] = w;
	}

	virtual ~Vector4() { ; }

	/// Allows access to each vector element.
//	float operator [] (const int i) const;

	float& operator [] (const int i);

	/// Vector Addition operator.
	Vector4 operator + (Vector4& val);

	/// Vector Subtraction operator.
	Vector4 operator - (Vector4& val);

	/// Vector Equality operator.
	Vector4& operator = (Vector4& val);

	/// Scalar Multiplication operator.
	Vector4 operator * (Vector4& val);

	/// Returns magnitude (length) of a vector.
	float GetMagnitude();

	/// Generates a normalised (unit) vector, a vector with a magnitude of 1.
	Vector4 Normalise();

	/// Vector * Vector multiplication - produces a third vector which is orthogonal to the inputs.
	Vector4 CrossProduct(Vector4& val);

	/// Vector * Vector multiplication - returns the cosine angle between 2 vectors.
	float DotProduct(Vector4& val);
};

