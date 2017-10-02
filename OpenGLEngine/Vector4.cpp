#include "Vector4.h"
#include <math.h>





float& Vector4::operator [] (const int i)
{
	return _mElement[i];
}


Vector4 Vector4::operator + (Vector4& val)
{
	return Vector4((*this)[0] + val[0],
				   (*this)[1] + val[1],
				   (*this)[2] + val[2],
				   (*this)[3] + val[3]);
}


Vector4 Vector4::operator - (Vector4& val)
{
	return Vector4((*this)[0] - val[0],
				   (*this)[1] - val[1],
				   (*this)[2] - val[2],
				   (*this)[3] - val[3]);
}


Vector4& Vector4::operator = (Vector4& val)
{
	_mElement[0] = val[0];
	_mElement[1] = val[1];
	_mElement[2] = val[2];
	_mElement[3] = val[3];
	return *this;
}


Vector4 Vector4::operator * (Vector4& val)
{
	return Vector4(_mElement[0] * val[0],
				   _mElement[1] * val[1],
				   _mElement[2] * val[2],
				   _mElement[3] * val[3]);
}


float Vector4::GetMagnitude()
{
	return sqrt(_mElement[0] * _mElement[0] + _mElement[1] * _mElement[1] + _mElement[2] * _mElement[2] + _mElement[3] * _mElement[3]);
}


Vector4 Vector4::Normalise()
{
	float magnitude = this->GetMagnitude();

	if (magnitude != 0)
	{
		float val = 1.0f / magnitude;

		_mElement[0] *= val;
		_mElement[1] *= val;
		_mElement[2] *= val;
		_mElement[3] *= val;
	}

	return *this;
}


Vector4 Vector4::CrossProduct(Vector4& val)
{
	return Vector4(_mElement[1] * val[2] - _mElement[2] * val[1],
				   _mElement[2] * val[0] - _mElement[0] * val[2],
				   _mElement[0] * val[1] - _mElement[1] * val[0], 1.0f);
}


float Vector4::DotProduct(Vector4& val)
{
	return _mElement[0] * val[0] + _mElement[1] * val[1] + _mElement[2] * val[2] + _mElement[3] * val[3];
}
