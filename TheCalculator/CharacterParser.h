#pragma once
#include "CalculatorParams.h"
using namespace Windows::UI::Xaml::Controls;
using namespace Platform;

	class CharacterParser sealed 
	{
	public:
			CharacterParser();
			void DisplayCharacter(String^ ClickedText, TextBlock^ ScreenText);
			CalculatorParams HandleDigit(Platform::String^ Digit, CalculatorParams params);
			int RefStringToInt(Platform::String^ theString);
			bool IsInt(String^ character);
			bool IsBinaryOperator(Platform::String^ character);
			bool IsUnaryOperator(Platform::String^ character);
			CalculatorParams TerminateNumber(CalculatorParams params);
			CalculatorParams HandleBinaryOperator(CalculatorParams params, Platform::String^ character);
			CalculatorParams HandleUnaryOperator(CalculatorParams params, Platform::String^ character);
			//Platform::String^ * GetOperators(CalculatorParams params);
	};


