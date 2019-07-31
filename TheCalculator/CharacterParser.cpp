#include "CharacterParser.h"
#include "App.xaml.h"


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


CalculatorParams CharacterParser::HandleCharacter(String^ ClickedText, CalculatorParams params) {

	params.DisplayOutput = this->LogCharacter(params.DisplayOutput, ClickedText);

	if (this->IsBinaryOperator(ClickedText)) {
		//We save the number before our binary operator to params.Tokens. If
		//the previous token is a close bracket then there is no number that
		//needs saving.
		if (params.Tokens.size() != 0) {
			if (params.Tokens[params.Tokens.size()-1] != ")") {
				params.Tokens.push_back(params.CurrentNumber.ToString());
				params = this->TerminateNumber(params);
			}
		}
		else if (params.Tokens.size() == 0) {
			params.Tokens.push_back(params.CurrentNumber.ToString());
			params = this->TerminateNumber(params);
		}
		params.Tokens.push_back(ClickedText);
	}
	else if (this->IsUnaryOperator(ClickedText)) {
		if (params.CurrentNumber != 0) {
			params.Tokens.push_back(params.CurrentNumber.ToString());
			params = this->TerminateNumber(params);
		}

		params.Tokens.push_back(ClickedText);
		if (ClickedText != L"x²" && ClickedText != L"x³" &&
			ClickedText != L"xʸ" && ClickedText != L"n!") {
			params.Tokens.push_back("(");
		}
	}
	else if (ClickedText == L"(") {
		params.Tokens.push_back(ClickedText);
	}

	//If the user clicks a number the parser converts the number clicked
	//into an internally stored number it can use for arithmetic.
	else if (this->IsInt(ClickedText)) {
		params = this->HandleDigit(ClickedText, params);
	}
	if (ClickedText != L"." && !this->IsInt(ClickedText) && params.CurrentNumber != 0) {
		params.Tokens.push_back(params.CurrentNumber.ToString());
		params = this->TerminateNumber(params);
		params.Tokens.push_back(ClickedText);
	}

	if (ClickedText == L"." && params.Decimal == false) {
		params.Decimal = true;
		params.Multiplier = 0.1;
	}
	else if (ClickedText == L"CE") {
		//int LastCharIndex = (*params.DisplayOutput->Length - 1);
		//params.DisplayOutput[LastCharIndex] = "";
		//params.CurrentNumber = 0;
	}
	else if (ClickedText == L"Del") {

	}
	else if (ClickedText == L"y√x") {

	}
	else if (ClickedText == L"Exp") {
		params.DisplayOutput = params.DisplayOutput + ".e+0";
		params.Exp = true;
	}
	else if (ClickedText == L"Mod") {

	}
	else if (ClickedText == L"dms") {

	}
	else if (ClickedText == L"deg") {

	}
	else if (ClickedText == L"π") {
		params.CurrentNumber = M_PI;
	}
	return params;
}



Platform::String^ CharacterParser::LogCharacter(String^ Input, String^ ClickedText) {

	if (Input == "0" && !(this->IsUnaryOperator(ClickedText))) {
		Input = ClickedText;
	}

	else if (ClickedText == L"sin" || ClickedText == L"cos" || ClickedText == L"tan"
		|| ClickedText == L"sin⁻¹" || ClickedText == L"cos⁻¹" || ClickedText == L"tan⁻¹" || ClickedText == L"log"
		|| ClickedText == L"ln") {
		if (Input == "0") {
			Input = ClickedText + "(";
		}
		else {
			Input = Input + ClickedText + "(";
		}
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
		if (Input == "0") {
			Input = L"√";
		}
		else {
			Input = Input + L"√";
		}
	}
	else if (ClickedText == L"1/x") {
		if (Input == "0") {
			Input = "1/";
		}
		else {
			Input = Input + "1/";
		}
	}
	else if (ClickedText == "n!") {
		if (Input == "0") {
			Input = "0";
		}
		else {
			Input = Input + "!";
		}
	}
	else if (ClickedText == "Exp") {
		Input = Input + ".e+0";
	}
	else if (ClickedText == L"xʸ") {
		Input = Input + "^";
	}
	else if (this->DoDisplay(ClickedText)) {
		Input = Input + ClickedText;
	}
	return Input;
}

bool CharacterParser::IsInt(String^ ClickedText) {
	bool IsInt;
	if (ClickedText == "0" || ClickedText == "1" || ClickedText == "2" || ClickedText == "3" || ClickedText == "4" ||
		ClickedText == "5" || ClickedText == "6" || ClickedText == "7" || ClickedText == "8" || ClickedText == "9") {
		IsInt = true;
	}
	else {
		IsInt = false;
	}
	return IsInt;
}

//This function checks whether the button clicked is an operator.
bool CharacterParser::IsBinaryOperator(String^ ClickedText) {
	bool IsBinaryOperator;
	if (ClickedText == "+" || ClickedText == "-" || ClickedText == "X" ||
		ClickedText == "÷" || ClickedText == "Exp" || 
		ClickedText == L"xʸ") {
		IsBinaryOperator = true;
	}
	else {
		IsBinaryOperator = false;
	}
	return IsBinaryOperator;
}

bool CharacterParser::IsUnaryOperator(String^ ClickedText) {
	bool IsUnaryOperator;
	if (ClickedText == L"sin" || ClickedText == L"cos" || ClickedText == L"tan"
		|| ClickedText == L"sin⁻¹" || ClickedText == L"cos⁻¹" || ClickedText == L"tan⁻¹"
		|| ClickedText == L"x²" || ClickedText == L"10ˣ" || ClickedText == L"log" || ClickedText == L"eˣ"
		|| ClickedText == L"x³" || ClickedText == L"ln" || ClickedText == L"√"
		|| ClickedText == L"1/x" || ClickedText == L"n!") {
		IsUnaryOperator = true;
	}
	else {
		IsUnaryOperator = false;
	}
	return IsUnaryOperator;
}


CalculatorParams CharacterParser::HandleDigit(String^ Digit, CalculatorParams params) {
	//If the button clicked is a number, this section adds the number to the current number.

	int CurrentDigit = _wtoi(Digit->Data());

	if (!params.Decimal) {
		params.CurrentNumber = params.CurrentNumber * 10;
		params.CurrentNumber = params.CurrentNumber + CurrentDigit;
	}

	else if (params.Decimal) {
		params.CurrentNumber = params.CurrentNumber + (CurrentDigit * params.Multiplier);
		params.Multiplier = params.Multiplier * 0.1;
	}
	return params;
}

CalculatorParams CharacterParser::TerminateNumber(CalculatorParams params) {
	if (params.Exp) {
		params.Exp = false;
	}

	params.CurrentNumber = 0;
	params.Decimal = false;
	params.Multiplier = 1.0;
	return params;
}

bool CharacterParser::DoDisplay(Platform::String^ ClickedText) {
	bool DoDisplay = false;
	if (this->IsInt(ClickedText) || this->IsUnaryOperator(ClickedText) ||
		this->IsBinaryOperator(ClickedText) || ClickedText == L"π" || ClickedText == "(" ||
		ClickedText == L")" || ClickedText == ".") {
		DoDisplay = true;
	}
	return DoDisplay;
}