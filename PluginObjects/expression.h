#pragma once

#include "synthdefs.h"
#include "SlewLimiter.h"

enum class ExpressionType
{kCC, kChannelPressure};

enum {
	kEXPSmoothOutput,
	kEXPRawOutput
};

struct ExpressionParameters
{
	ExpressionParameters() {}
	ExpressionParameters& operator=(const ExpressionParameters& params)	// need this override for collections to work
	{
		if (this == &params)
			return *this;

		slew = params.slew;
		type = params.type;
		ccNumber = params.ccNumber;

		return *this;
	}

	// --- individual parameters
	double slew = 0.0;
	int ccNumber = 0;
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
	Expression(const std::shared_ptr<MidiInputData> _midiInputData, std::shared_ptr<ExpressionParameters> _parameters)
		: midiInputData(_midiInputData)
		, parameters(_parameters) {
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

	virtual bool doNoteOn(double midiPitch, uint32_t _midiNoteNumber, uint32_t midiNoteVelocity)
	{
		return true;
	}

	virtual bool doNoteOff(double midiPitch, uint32_t _midiNoteNumber, uint32_t midiNoteVelocity)
	{
		return true;
	}

	virtual std::shared_ptr<ModInputData> getModulators() {
		return modulators;
	}

	virtual void setModulators(std::shared_ptr<ModInputData> _modulators) {
		modulators = _modulators;
	}

protected:
	const std::shared_ptr<MidiInputData> midiInputData = nullptr;
	std::shared_ptr<ModInputData> modulators = std::make_shared<ModInputData>();
	std::shared_ptr<ExpressionParameters> parameters = nullptr;
	SlewLimiter smoother;

	double sampleRate = 0.0;
};