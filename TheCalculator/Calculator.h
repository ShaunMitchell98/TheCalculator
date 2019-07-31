#pragma once

#include "CalculatorParams.h"
#include "CharacterParser.h"
#include <vector>
#include <iterator>


class Calculator
{
public:
	Calculator();
	int FindEndIndex(std::vector<Platform::String^> Tokens, int StartIndex);
    Platform::String^ EvaluateBracketedExpression(std::vector<Platform::String^> Tokens);
	Platform::String^ EvaluateUnaryOperation(Platform::String^ UnaryOperation, Platform::String^ StringNumber);
	Platform::String^ EvaluateBinaryOperation(Platform::String^ StringFirstNumber, Platform::String^ StringSecondNumber,
		Platform::String^ BinaryOperation);

private:
	CharacterParser parser;
	double Factorial(double Number);
};