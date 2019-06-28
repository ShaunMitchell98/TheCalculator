#include "CharacterParser.h"
#include "App.xaml.h"
#include <iostream>

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

void CharacterParser::DisplayCharacter(String^ ClickedText, TextBlock^ ScreenText) {
	
	if (this->IsUnaryOperator(ClickedText)) {
		ScreenText->Text = ScreenText->Text + ClickedText + "(";
	}
	if (ScreenText->Text == "0") {
		ScreenText->Text = ClickedText;
	}
	else {
		ScreenText->Text = ScreenText->Text + ClickedText;
	}
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
	if (character == "sin" || character == "cos" || character == "tan") {
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
	
	int CurrentNumber = params.CurrentNumber;
	int NumberOfDigits = params.NumberOfDigits;
   	int CurrentDigit = CharacterParser::RefStringToInt(Digit);

	if (NumberOfDigits == 0) {
		CurrentNumber = CurrentDigit;
		NumberOfDigits++; //Increment the number of Digits so that a new number will not be created.
	}

	else {
		CurrentNumber = CurrentNumber * 10;
		CurrentNumber = CurrentNumber + CurrentDigit;
		NumberOfDigits++;
	}
	params.CurrentNumber = CurrentNumber;
	params.NumberOfDigits = NumberOfDigits;
	return params;
}

CalculatorParams CharacterParser::TerminateNumber(CalculatorParams params) {
    params.Numbers[params.NumberCount] = params.CurrentNumber;
    params.CurrentNumber = 0;
	params.NumberOfDigits = 0;
	params.NumberCount = params.NumberCount + 1;
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
	return params;
}

