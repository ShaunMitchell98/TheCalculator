#pragma once
#include "CalculatorParams.h"
using namespace Windows::UI::Xaml::Controls;

class TokenParser sealed
{
public:
	TokenParser();
	CalculatorParams ParseToken(Platform::String^ character, CalculatorParams params);
	bool IsBinaryOperator(Platform::String^ character);
	bool IsUnaryOperator(Platform::String^ character);

private:
	CalculatorParams ParseDigit(Platform::String^ Digit, CalculatorParams params);
	bool IsInt(Platform::String^ character);
};
