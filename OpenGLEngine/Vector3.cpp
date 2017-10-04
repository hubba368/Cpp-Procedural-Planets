#include "Vector3.h"
#include <math.h>


float Vector3::operator[](const int i) const
{
	return _mElement[i];
}

float& Vector3::operator [] (const int i)
{
	return _mElement[i];
}


Vector3 Vector3::operator + ( Vector3& val)
{
	return Vector3((*this)[0] + val[0],
				   (*this)[1] + val[1],
				   (*this)[2] + val[2]);
}


Vector3 Vector3::operator - (Vector3 & val)
{
	return Vector3((*this)[0] - val[0],
				   (*this)[1] - val[1],
				   (*this)[2] - val[2]);
}


Vector3& Vector3::operator = (Vector3 & val)
{
	_mElement[0] = val[0];
	_mElement[1] = val[1];
	_mElement[2] = val[2];
	return *this;
}


Vector3 Vector3::operator * (Vector3 & val)
{
	return Vector3(_mElement[0] * val[0],
				   _mElement[1] * val[1],
				   _mElement[2] * val[2]);
}

Vector3 Vector3::operator * (float val)
{
	return Vector3(_mElement[0] * val,
				   _mElement[1] * val,
				   _mElement[2] * val);
}

void Vector3::SetVector(float x, float y, float z)
{
	_mElement[0] = x, _mElement[1] = y, _mElement[2] = z;
}


float Vector3::GetMagnitude() 
{
	return sqrt(_mElement[0] * _mElement[0] + _mElement[1] * _mElement[1] + _mElement[2] * _mElement[2]);
}


Vector3 Vector3::Normalise()
{
	float magnitude = this->GetMagnitude();

	if (magnitude != 0) 
	{
		float val = 1.0f / magnitude;

		_mElement[0] *= val;
		_mElement[1] *= val;
		_mElement[2] *= val;
	}

	return *this;
}


Vector3 Vector3::CrossProduct(Vector3 & val)
{
	return Vector3(_mElement[1] * val[2] - _mElement[2] * val[1],
				   _mElement[2] * val[0] - _mElement[0] * val[2],
				   _mElement[0] * val[1] - _mElement[1] * val[0]);
}


float Vector3::DotProduct(Vector3 & val)
{
	return _mElement[0] * val[0] + _mElement[1] * val[1] + _mElement[2] * val[2];
}
