#include "CharacterParser.h"
#include "App.xaml.h"
#include <iostream>
#include <math.h>
#include "RunCalculations.h"


#define M_PI 3.14159265359
#define M_E 2.7182818284 //e to 10 decimal places

using namespace TheCalculator;
using namespace Platform;

using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

CharacterParser::CharacterParser() {
}


CalculatorParams CharacterParser::HandleCharacter(String^ character, CalculatorParams params) {
	
	params.Input = this->LogCharacter(params.Input, character);
	
	//If the user clicks a number the parser converts the number clicked
	//into an internally stored number it can use for arithmetic.
	if (this->IsInt(character)) {
		params = this->HandleDigit(character, params);
	}
	if (character != L"." && params.Exponent == true) {
		params.Exponent = false;
	}
	//Check whether the button clicked is a binary operator. If this is the case
	//we close the current number and save it for calculations and save the 
	//operator which is to be used on that number.
	else if (this->IsBinaryOperator(character) && params.CurrentNumber != 0)
	{
		params = this->TerminateNumber(params);
		params = this->HandleBinaryOperator(params, character);
	}
	else if (this->IsUnaryOperator(character))
	{
		params = this->HandleUnaryOperator(params, character);
	}

	else if (character == L"." && params.Decimal == false) {
		params.Decimal = true;
		params.Multiplier = 0.1;
	}
	else if (character == L"xʸ") {
		params.Exponent = true;
		params.Input = params.Input + "^";
	}
	else if (character == L"CE") {
		//int LastCharIndex = (*params.Input->Length - 1);
		//params.Input[LastCharIndex] = "";
		//params.CurrentNumber = 0;
	}
	else if (character == L"Del") {

	}
	else if (character == L"y√x") {

	}
	else if (character == L"Exp") {
		params.Input = params.Input + ".e+0";
		params = TerminateNumber(params);
		params.Exp = true;
	}
	else if (character == L"Mod") {

	}
	else if (character == L"dms") {

	}
	else if (character == L"deg") {

	}
	else if (character == L"↑") {

	}
	else if (character == L"n!") {
		params.CurrentNumber = this->Factorial(params.CurrentNumber);
	}
	else if (character == L"±") {
		params.CurrentNumber = -params.CurrentNumber;
	}
	else if (character == L")") {
		params.CloseBracketIndex = params.NumberCount;
	    //params.CurrentNumber = RunCalculations(params);
		params = this->TerminateNumber(params);
	}
	if (character == L"π") {
		params.Numbers[params.NumberCount] = M_PI;
		params.NumberCount = params.NumberCount + 1;
		//params.Input =  params.Input + M_PI.ToString();
	}
	return params;
}



String^ CharacterParser::LogCharacter(String^ Input, String^ ClickedText) {
	

	if (Input == "0" && !(this->IsUnaryOperator(ClickedText))) {
		Input = ClickedText;
	}

	else if (Input == "0" && (ClickedText == L"sin" || ClickedText == L"cos" || ClickedText == L"tan"
		|| ClickedText == L"sin⁻¹" || ClickedText == L"cos⁻¹" || ClickedText == L"tan⁻¹" || ClickedText == L"log")
		|| ClickedText == L"ln") {
		Input = ClickedText + "(";
	}
	else if (ClickedText == L"x²") {
		Input = Input + "²";
	}
	else if (ClickedText == L"10ˣ") {
		if (Input == "0") {
			Input = L"10^";
		}
		else {
			Input = Input + L"10^";
		}
	}
	else if (ClickedText == L"eˣ") {
		if (Input == "0") {
			Input = L"e^";
		}
		else {
			Input = Input + L"e^";
		}
	}
	else if (ClickedText == L"x³") {
		Input = Input + "³";
	}
	else if (ClickedText == L"√") {
		Input = Input + L"√";
	}
	else if (ClickedText == L"1/x") {
		if (Input == "0") {
			Input = "1/";
		}
		else {
			Input = Input + "1/";
		}
	}
	else if (this->DoDisplay(ClickedText)) {
		Input = Input + ClickedText;
	}
	return Input;
}

bool CharacterParser::IsInt(String^ character) {
	bool IsInt;
	if (character == "0" || character == "1" || character == "2" || character == "3" || character == "4" ||
		character == "5" || character == "6" || character == "7" || character == "8" || character == "9") {
		IsInt = true;
	}
	else {
		IsInt = false;
	}
	return IsInt;
}

//This function checks whether the button clicked is an operator.
bool CharacterParser::IsBinaryOperator(String^ character) {
	bool IsBinaryOperator;
	if (character == "+" || character == "-" || character == "X" ||
		character == "÷") {
		IsBinaryOperator = true;
	}
	else {
		IsBinaryOperator = false;
	}
	return IsBinaryOperator;
}

bool CharacterParser::IsUnaryOperator(String^ character) {
	bool IsUnaryOperator;
	if (character == L"sin" || character == L"cos" || character == L"tan" 
		|| character == L"sin⁻¹" || character == L"cos⁻¹" || character == L"tan⁻¹"
		|| character == L"x²" || character == L"10ˣ" || character == L"log" || character == L"eˣ"
		|| character == L"x³" || character == L"ln" || character == L"√" 
		|| character == L"1/x") {
		IsUnaryOperator = true;
	}
	else {
		IsUnaryOperator = false;
	}
	return IsUnaryOperator;
}

int CharacterParser::RefStringToInt(String^ theString) {
	return _wtoi(theString->Data());
}


CalculatorParams CharacterParser::HandleDigit(String^ Digit, CalculatorParams params) {
	//If the button clicked is a number, this section adds the number to the current number.
	
   	int CurrentDigit = this->RefStringToInt(Digit);

     if (!params.Decimal && !params.Exponent) {
		params.CurrentNumber = params.CurrentNumber * 10;
		params.CurrentNumber = params.CurrentNumber + CurrentDigit;
	}
	
	else if (params.Decimal) {
		params.CurrentNumber = params.CurrentNumber + (CurrentDigit * params.Multiplier);
		params.Multiplier = params.Multiplier * 0.1;
	}
	else if (params.Exponent) {
		params.CurrentNumber = pow(params.CurrentNumber, CurrentDigit);
	}
	return params;
}

CalculatorParams CharacterParser::TerminateNumber(CalculatorParams params) {
	if (params.Exp) {
		params.Numbers[params.NumberCount -1] =  params.Numbers[params.NumberCount-1] * pow(10, params.CurrentNumber);
		params.Exp = false;
   }
	
	params.Numbers[params.NumberCount] = params.CurrentNumber;
    params.CurrentNumber = 0;
	params.NumberCount = params.NumberCount + 1;
	params.Decimal = false;
	params.Multiplier = 1.0;
	return params;
}

CalculatorParams CharacterParser::HandleBinaryOperator(CalculatorParams params, Platform::String^ character) {
	params.BinaryOperators[params.BinaryOperatorCount] = character;
	params.BinaryOperatorCount++;
	return params;
}

CalculatorParams CharacterParser::HandleUnaryOperator(CalculatorParams params, Platform::String^ character) {
	params.UnaryOperators[params.UnaryOperatorCount] = character;
	params.UnaryOperatorCount++;
	params.OpenBracketIndex = params.NumberCount;
	
	return params;
}

bool CharacterParser::DoDisplay(Platform::String^ character) {
	bool DoDisplay = false;
	if (this->IsInt(character) || this->IsUnaryOperator(character) ||
		this->IsBinaryOperator(character) || character == L"π" || character == L")") {
		DoDisplay = true;
	}
	return DoDisplay;
}

double CharacterParser::Factorial(double n) {
    return (n == 1 || n == 0) ? 1 : Factorial(n - 1) * n;
}