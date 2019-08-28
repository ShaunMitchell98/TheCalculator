#pragma once
#include <vector>

enum AngleUnit {
	Degrees,
	Radians
};

struct CalculatorParams {
	double CurrentNumber = 0.0;
	bool Decimal = false;
	double Multiplier = 1.0;
	Platform::String^ DisplayOutput = "0";
	std::vector<Platform::String^> Tokens;
	AngleUnit Unit = Radians;
};