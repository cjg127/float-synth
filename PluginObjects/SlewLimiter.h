/**
\struct SlewLimiter
\ingroup SynthStructures
\brief A structure the implements a simple 1-pole LPF to use as a slew-limiter
*/
struct SlewLimiter
{
public:
	SlewLimiter() {}

	// --- slewing functions
	void reset() { z1 = 0; }		///< reset the counter

	// --- slew value is:  0 <= slewvalue <= 0.9999
	void setSlewValue(double _g) { g = _g; }		///< reset the counter
	double doSlewLimiter(double input)
	{
		double output = input*(1.0 - g) + g*z1;
		z1 = output;
		return output;
	}

protected:
	double g = 0;
	double z1 = 0.0;
};
