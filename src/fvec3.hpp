#pragma once

struct fvec3 final
{
	fvec3(const double value);
	fvec3(const double x, const double y, const double z);

	union
	{
		struct
		{
			double x;
			double y;
			double z;
		};

		struct
		{
			double r;
			double g;
			double b;
		};
	};
};