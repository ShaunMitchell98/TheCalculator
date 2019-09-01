#pragma once
#include <vector>
#define DefaultNumber DBL_MAX

enum AngleUnit {
	Degrees,
	Radians
};

struct CalculatorParams {
	Platform::String^ CurrentNumber = DefaultNumber.ToString();
	Platform::String^ DisplayOutput = "0";
	std::vector<Platform::String^> Tokens;
	AngleUnit Unit = Radians;
};