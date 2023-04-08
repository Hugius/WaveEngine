#pragma once

#include "fmat33.hpp"

class Mathematics final
{
public:
	Mathematics() = delete;

	static const fmat33 createTranslationMatrix(const float x, const float y);
	static const fmat33 createRotationMatrix(const float angle);
	static const fmat33 createScalingMatrix(const float x, const float y);

	static const float convertToRadians(const float degrees);
	static const float limitAngle(const float angle);
	static const float getSignum(float value);
	static const float getPi();

private:
	static inline const float DEG2RAD = 0.017453292f;
	static inline const float PI = 3.141592653f;
};