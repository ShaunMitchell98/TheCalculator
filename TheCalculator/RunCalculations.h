#pragma once
#include "CalculatorParams.h"
#include "CharacterParser.h"
#include <cmath>


#define M_PI 3.14159265359
#define M_E 2.7182818284 //e to 10 decimal places

inline double RunCalculations(CalculatorParams params)
{
	CharacterParser parser;
	double result = 0.0;
	if (params.CurrentNumber != 0) {
		params = parser.TerminateNumber(params);
	}


	if (params.NumberCount = 1) {
		result = params.Numbers[0];
	}

	if (params.OpenBracketIndex != -1) {
		for (int i = params.OpenBracketIndex; i < params.CloseBracketIndex; i++) {
			if (params.BinaryOperators[i] == "+") {
				result = params.Numbers[i] + params.Numbers[i + 1];
				params.Numbers[i] = 0;
				params.Numbers[i + 1] = result;
				params.BinaryOperators[i] = "D";
			}
			if (params.BinaryOperators[i] == "-") {
				result = params.Numbers[i] - params.Numbers[i + 1];
				params.Numbers[i] = 0;
				params.Numbers[i + 1] = result;
				params.BinaryOperators[i] == "D";
			}
			if (params.BinaryOperators[i] == "X") {
				result = params.Numbers[i] * params.Numbers[i + 1];
				params.Numbers[i] = 0;
				params.Numbers[i + 1] = result;
				params.BinaryOperators[i] == "D";
			}
			if (params.BinaryOperators[i] == "÷") {
				result = params.Numbers[i] / params.Numbers[i + 1];
				params.Numbers[i] = 0;
				params.Numbers[i + 1] = result;
				params.BinaryOperators[i] == "D";
			}
		}
		params.Numbers[params.OpenBracketIndex] = result;
		params.OpenBracketIndex = -1;

	}

	for (int i = 0; i < params.UnaryOperatorCount; i++) {
		if (params.UnaryOperators[i] == L"sin") {
			result = sin(params.Numbers[i]);
		}
		else if (params.UnaryOperators[i] == L"cos") {
			result = cos(params.Numbers[i]);
		}
		else if (params.UnaryOperators[i] == L"tan") {
			result = tan(params.Numbers[i]);
		}
		else if (params.UnaryOperators[i] == L"sin⁻¹") {
			result = asin(params.Numbers[i]) * (180 / M_PI);
		}
		else if (params.UnaryOperators[i] == L"cos⁻¹") {
			result = acos(params.Numbers[i]) * (180 / M_PI);
		}
		else if (params.UnaryOperators[i] == L"tan⁻¹") {
			result = atan(params.Numbers[i]) * (180 / M_PI);
		}
		else if (params.UnaryOperators[i] == L"x²") {
			result = pow(params.Numbers[i], 2);
		}
		else if (params.UnaryOperators[i] == L"10ˣ") {
			result = pow(10, result);
		}
		else if (params.UnaryOperators[i] == L"log") {
			result = log10(result);
		}
		else if (params.UnaryOperators[i] == L"eˣ") {
			result = pow(M_E, result);
		}
		else if (params.UnaryOperators[i] == L"x³") {
			result = pow(result, 3);
		}
		else if (params.UnaryOperators[i] == L"ln") {
			result = log(result);
		}
		else if (params.UnaryOperators[i] == L"√") {
			result = sqrt(result);
		}
		else if (params.UnaryOperators[i] == L"1/x") {
			result = 1 / result;
		}
	}
	for (int i = 0; i < params.BinaryOperatorCount; i++) {
		if (params.BinaryOperators[i] == "+") {
			result = params.Numbers[i] + params.Numbers[i + 1];
			params.Numbers[i] = 0;
			params.Numbers[i + 1] = result;
		}
		if (params.BinaryOperators[i] == "-") {
			result = params.Numbers[i] - params.Numbers[i + 1];
			params.Numbers[i] = 0;
			params.Numbers[i + 1] = result;
		}
		if (params.BinaryOperators[i] == "X") {
			result = params.Numbers[i] * params.Numbers[i + 1];
			params.Numbers[i] = 0;
			params.Numbers[i + 1] = result;
		}
		if (params.BinaryOperators[i] == "÷") {
			result = params.Numbers[i] / params.Numbers[i + 1];
			params.Numbers[i] = 0;
			params.Numbers[i + 1] = result;
		}
	}
	return result;
}
