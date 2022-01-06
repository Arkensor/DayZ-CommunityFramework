class CF_Math
{
	// https://en.wikipedia.org/wiki/Cubic_Hermite_spline 
	static vector CubicInterp(vector p0, vector p1, vector m0, vector m1, float t)
	{
		float t2 = t * t;
		float t3 = t * t * t;

		vector res = vector.Zero;
		res += ((2.0 * t3) - (3.0 * t2) + 1.0) * p0;
		res += ((t3) - (2.0 * t2) + t) * m0;
		res += ((-2.0 * t3) + (3.0 * t2)) * p1;
		res += (t3 - t2) * m1;
		return res;
	}
};
