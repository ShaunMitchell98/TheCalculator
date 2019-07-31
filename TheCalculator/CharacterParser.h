#pragma once
#include "CalculatorParams.h"
using namespace Windows::UI::Xaml::Controls;
using namespace Platform;

class CharacterParser sealed
{
public:
	CharacterParser();
	CalculatorParams HandleCharacter(String^ character, CalculatorParams params);
	CalculatorParams TerminateNumber(CalculatorParams params);
	bool IsBinaryOperator(Platform::String^ character);
	bool IsUnaryOperator(Platform::String^ character);

private:
	String^ LogCharacter(String^ Input, String^ ClickedText);
	CalculatorParams HandleDigit(Platform::String^ Digit, CalculatorParams params);
	bool IsInt(String^ character);
	bool DoDisplay(String^ character);
};
