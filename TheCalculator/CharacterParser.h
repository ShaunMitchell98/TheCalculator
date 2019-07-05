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
			
	private:		
			String^ LogCharacter(String^ Input, String^ ClickedText);
			CalculatorParams HandleDigit(Platform::String^ Digit, CalculatorParams params);
			int RefStringToInt(Platform::String^ theString);
			bool IsInt(String^ character);
			bool IsBinaryOperator(Platform::String^ character);
			bool IsUnaryOperator(Platform::String^ character);
			CalculatorParams HandleBinaryOperator(CalculatorParams params, Platform::String^ character);
			CalculatorParams HandleUnaryOperator(CalculatorParams params, Platform::String^ character);
			bool DoDisplay(String^ character);
			double Factorial(double n);
	};


