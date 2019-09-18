#pragma once

#include "CalculatorParams.h"
#include "TokenParser.h"
#include <vector>
#include <iterator>


class Calculator
{
public:
	Calculator();
	int FindEndIndex(std::vector<Platform::String^> Tokens, int StartIndex);
    Platform::String^ EvaluateBracketedExpression(std::vector<Platform::String^> Tokens, AngleUnit Unit);
	Platform::String^ EvaluateUnaryOperation(Platform::String^ UnaryOperation, Platform::String^ StringNumber, AngleUnit Unit);
	Platform::String^ EvaluateBinaryOperation(Platform::String^ StringFirstNumber, Platform::String^ StringSecondNumber,
		Platform::String^ BinaryOperation);

private:
	TokenParser parser;
	double Factorial(double Number);
};