#pragma once

#include "dvec3.hpp"

struct Colors final
{
	static inline const dvec3 BLACK = dvec3(0.0);
	static inline const dvec3 GRAY = dvec3(0.3);
	static inline const dvec3 WHITE = dvec3(1.0);
	static inline const dvec3 RED = dvec3(1.0, 0.0, 0.0);
	static inline const dvec3 DARK_RED = dvec3(0.25, 0.0, 0.0);
	static inline const dvec3 DARK_GRAY = dvec3(0.15);
	static inline const dvec3 LIGHT_GRAY = dvec3(0.45);
};