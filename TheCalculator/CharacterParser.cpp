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
	
	ScreenText->Text = ScreenText->Text + ClickedText;

}


TextBlock^ CharacterParser::DisplayLoggedCharacters(String^ LoggedCharacters, TextBlock^ ScreenLoggedCharacters) {
	ScreenLoggedCharacters->Text = LoggedCharacters;
	return ScreenLoggedCharacters;
}

String^ CharacterParser::LogCharacter(String^ ClickedText, String^ LoggedText) {
	if (LoggedText == "") {
		LoggedText = ClickedText;
	}
	else {
		LoggedText = LoggedText + ClickedText;
	}

	return LoggedText;
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
bool CharacterParser::IsOperator(String^ character) {
	bool IsOperator;
	if (character == "+" || character == "-" || character == "X" ||
		character == "÷") {
		IsOperator = true;
	}
	else {
		IsOperator = false;
	}
	return IsOperator;
}


int CharacterParser::RefStringToInt(String^ theString) {
	return _wtoi(theString->Data());
}


HandleDigitParams CharacterParser::HandleDigit(String^ Digit, HandleDigitParams params) {
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

HandleDigitParams CharacterParser::TerminateNumber(HandleDigitParams params) {
    params.Numbers[params.NumberCount] = params.CurrentNumber;
    params.CurrentNumber = 0;
	params.NumberOfDigits = 0;
	params.NumberCount = params.NumberCount + 1;
	return params;
}

HandleDigitParams CharacterParser::HandleOperator(HandleDigitParams params, Platform::String^ character) {
	params.Operators[params.OperatorCount] = character;
	params.OperatorCount++;
	return params;
}

//Platform::String^ * CharacterParser::GetOperators(CharacterParser::HandleDigitParams params) {
	//return params.Operators;
//}