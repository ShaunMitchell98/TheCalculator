#pragma once
#include <vector>

enum AngleUnit {
	Degrees,
	Radians
};

struct CalculatorParams {
	bool EditingNumber = false;
	bool Mod = false;
	Platform::String^ DisplayOutput = "0";
	std::vector<Platform::String^> Tokens;
	AngleUnit Unit = Radians;
};