#pragma once
#include <vector>

struct CalculatorParams {
	double CurrentNumber = 0.0;
	bool Decimal = false;
	bool Exp = false;
	double Multiplier = 1.0;
	Platform::String^ DisplayOutput = "0";
	std::vector<Platform::String^> Tokens;
};