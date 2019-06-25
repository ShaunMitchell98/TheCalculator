#pragma once
struct HandleDigitParams {
	int CurrentNumber = 0;
	int NumberOfDigits = 0;
	int Numbers[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	Platform::String^ Operators[10] = { "Yikes", "Yikes", "Yikes", "Yikes", 
	"Yikes", "Yikes", "Yikes", "Yikes", "Yikes", "Yikes", };
	int OperatorCount = 0;
	int NumberCount = 0;
};
