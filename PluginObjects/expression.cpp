#include "expression.h"

bool Expression::update(bool updateAllModRoutings)
{
	if (!updateAllModRoutings)
		return true;
	smoother.setSlewValue(parameters->slew);
	return true;
}

const ModOutputData Expression::renderModulatorOutput()
{
	ModOutputData expression_output_data;

	unsigned int input = 0;
	// should be done in update?
	if (parameters->type == ExpressionType::kCC)
	{
		input = midiInputData->ccMIDIData[ccNum];
	}
	else if (parameters->type == ExpressionType::kChannelPressure)
	{
		// input = midiInputData->globalMIDIData
	}
	
	
	double raw = mapUINTToDouble(input, 0, 127, 0.0, 1.0);

	double processed = smoother.doSlewLimiter(raw); 

	expression_output_data.modulationOutputs[kEXPSmoothOutput] = processed;

	return expression_output_data;
}
