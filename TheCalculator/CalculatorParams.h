#pragma once
struct CalculatorParams {
	int CurrentNumber = 0;
	int NumberOfDigits = 0;
	double Numbers[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	Platform::String^ BinaryOperators[10] = { "D", "D", "D", "D", 
	"D", "D", "D", "D", "D", "D", };
	Platform::String^ UnaryOperators[10] = { "D", "D", "D", "D",
	"D", "D", "D", "D", "D", "D", };
	int BinaryOperatorCount = 0;
	int UnaryOperatorCount = 0;
	int NumberCount = 0;
};
