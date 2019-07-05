#include "CalculatorParams.h"
#include "CharacterParser.h"
#include <cmath>

#define M_PI 3.14159265359

double RunCalculations(CalculatorParams params)
{
	CharacterParser parser;
	double result = 0.0;
	if (params.CurrentNumber != 0.0) {
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
		params.Numbers[params.OpenBracketIndex] = result;
		params.OpenBracketIndex = -1;

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

	for (int i = 0; i < params.UnaryOperatorCount; i++) {
		if (params.UnaryOperators[i] == "sin") {
			result = sin(params.Numbers[i]);
		}
		if (params.UnaryOperators[i] == "cos") {
			result = cos(params.Numbers[i]);
		}
		if (params.UnaryOperators[i] == "tan") {
			result = tan(params.Numbers[i]);
		}
		if (params.UnaryOperators[i] == "sin⁻¹") {
			result = asin(params.Numbers[i]) * (180/M_PI);
		}
		if (params.UnaryOperators[i] == "cos⁻¹") {
			result = acos(params.Numbers[i]) * (180/M_PI);
		}
		if (params.UnaryOperators[i] == "tan⁻¹") {
			result = atan(params.Numbers[i]) * (180/M_PI);
		}
	}
	params.Input = result.ToString();
	return result;
}