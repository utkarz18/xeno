#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

namespace xeno {namespace maths {
	inline float toRadians(float degree)
	{
		return degree * ((float)M_PI / 180.0f);
	}
} }
