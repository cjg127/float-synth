#pragma once

#include "synthdefs.h"
#include "SlewLimiter.h"

enum class ExpressionType
{kCC, kChannelPressure};

struct ExpressionParameters
{
	ExpressionParameters() {}
	ExpressionParameters& operator=(const ExpressionParameters& params)	// need this override for collections to work
	{
		if (this == &params)
			return *this;

		slew = params.slew;
		type = params.type;

		return *this;
	}

	// --- individual parameters
	double slew = 0.0;
	ExpressionType type = ExpressionType::kCC;
};

/**
\class Expression
\brief Expression object for maniuplating MIDI Data

Outputs: contains 1 output
- kExpressionOutput
*/

class Expression : public ISynthModulator
{
public:
	Expression(const std::shared_ptr<MidiInputData> _midiInputData, std::shared_ptr<ExpressionParameters> _parameters, int _ccNum)
		: midiInputData(_midiInputData)
		, parameters(_parameters) 
		, ccNum(_ccNum) {
		srand(time(NULL)); // --- seed random number generator
	}	

	virtual ~Expression() {}

	virtual bool reset(double _sampleRate)
	{
		sampleRate = _sampleRate;
		smoother.reset();
		return true;
	}

	virtual bool update(bool updateAllModRoutings = true);

	const ModOutputData renderModulatorOutput();

protected:
	const std::shared_ptr<MidiInputData> midiInputData = nullptr;
	std::shared_ptr<ExpressionParameters> parameters = nullptr;
	SlewLimiter smoother;

	double sampleRate = 0.0;
	int ccNum = 0;
};