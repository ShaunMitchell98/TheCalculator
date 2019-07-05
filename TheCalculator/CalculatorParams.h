#pragma once
struct CalculatorParams {
	double CurrentNumber = 0.0;
	bool Decimal = false;
	bool Exponent = false;
	bool Exp = false;
	double Multiplier = 1.0;
	double Numbers[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	Platform::String^ BinaryOperators[10] = { "D", "D", "D", "D", 
	"D", "D", "D", "D", "D", "D", };
	Platform::String^ UnaryOperators[10] = { "D", "D", "D", "D",
	"D", "D", "D", "D", "D", "D", };
	int BinaryOperatorCount = 0;
	int UnaryOperatorCount = 0;
	int NumberCount = 0;
	Platform::String^ Input = "0";
	int OpenBracketIndex = -1; 
	int CloseBracketIndex;
};
