#pragma once

struct fvec3 final
{
	fvec3(const float value);
	fvec3(const float x, const float y, const float z);

	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};

		struct
		{
			float r;
			float g;
			float b;
		};
	};
};