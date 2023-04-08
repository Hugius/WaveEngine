#pragma once

struct dvec3 final
{
	dvec3(const double value);
	dvec3(const double x, const double y, const double z);

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