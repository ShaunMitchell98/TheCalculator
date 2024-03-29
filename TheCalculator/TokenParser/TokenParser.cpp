﻿#include "TokenParser.h"
#include "App.xaml.h"
#include <string>

#define M_PI 3.14159265359
#define M_E 2.7182818284 //e to 10 decimal places

using namespace TheCalculator;

using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

TokenParser::TokenParser() {
}

//This function is called to categorise tokens as either numbers, unary operators or binary operators.
//The tokens are stored in params.Tokens 
CalculatorParams TokenParser::ParseToken(Platform::String^ ClickedText, CalculatorParams params) {

    //If the user has clicked a binary operator, it should follow
	//either a number or an expression. If it follows an expression then
	//the previous token should be a closed bracket. In this case only
	//the operator needs to be pushed to the Tokens vector. If the
	//binary operator follows a number then this number is not yet
	//stored in Tokens and so must be pushed into it before the
	//operator is pushed.
	
	if (IsBinaryOperator(ClickedText)) {
		if ((params.EditingNumber == false) && (params.Tokens.back() != L")") &&
			ClickedText == "-") {
			params.EditingNumber = true;
		}
		else if (params.Tokens.size() != 0) {
			//Note that the check on Token size above is necessary
			//to avoid attempting to access a non-existent element
			//of Tokens in the next statement.
			if (params.Tokens.back() != ")" && params.EditingNumber == true) {
				params.EditingNumber = false;
			}
		}
		params.Tokens.push_back(ClickedText);
	}

	else if (IsUnaryOperator(ClickedText) && ClickedText != L"Mod") {

		//Unary operators that precede their numerical input
		//should be given a bracket to account for an expression
		//as input. The four operators checked for below follow
		//their input so have no need for an open bracket to 
		//follow them.
		if (ClickedText != L"x²" && ClickedText != L"x³" &&
			ClickedText != L"xʸ" && ClickedText != L"n!" 
			&& ClickedText != L"%") {
			params.Tokens.push_back(ClickedText);
			params.Tokens.push_back("(");
		}
		else {
			params.EditingNumber = false;
			params.Tokens.push_back(ClickedText);
		}
	}

	else if (ClickedText == L"(") {
		params.Tokens.push_back(ClickedText);
	}

	else if (ClickedText == L")") {
		if (params.EditingNumber == true) {
			params.EditingNumber = false;
		}
		params.Tokens.push_back(ClickedText);
	}
	else if (ClickedText == L"Mod") {
		if (params.Mod == false) {
			params.Mod = true;
			params.Tokens.push_back(L"Mod");
			params.Tokens.push_back(L"(");
		}
		else if (params.Mod == true) {
			params.Mod = false;
			params.Tokens.push_back(L")");
		}
	}

	//If the user clicks a number the parser converts the number clicked
	//into an internally stored number it can use for arithmetic.
	else if (IsInt(ClickedText) || ClickedText == L".") {
		params = ParseDigit(ClickedText, params);
	}


	else if (ClickedText == L"π") {
		if (params.EditingNumber == true) {
			params.EditingNumber = false;
			params.Tokens.push_back("X");
		}
		params.Tokens.push_back(M_PI.ToString());
	}

	return params;
}


CalculatorParams TokenParser::ParseDigit(Platform::String^ Digit, CalculatorParams params) {

	if (params.EditingNumber == false) {
		params.Tokens.push_back(Digit);
		params.EditingNumber = true;
	}
	else {
		params.Tokens.back() = params.Tokens.back() + Digit;
	}
	return params;
}


bool TokenParser::IsInt(Platform::String^ ClickedText) {
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

bool TokenParser::IsBinaryOperator(Platform::String^ ClickedText) {
	bool IsBinaryOperator;
	if (ClickedText == "+" || ClickedText == "-" || ClickedText == "X" ||
		ClickedText == "÷" || ClickedText == "Exp" || 
		ClickedText == L"xʸ" || ClickedText == L"yvx") {
		IsBinaryOperator = true;
	}
	else {
		IsBinaryOperator = false;
	}
	return IsBinaryOperator;
}

bool TokenParser::IsUnaryOperator(Platform::String^ ClickedText) {
	bool IsUnaryOperator;
	if (ClickedText == L"sin" || ClickedText == L"cos" || ClickedText == L"tan"
		|| ClickedText == L"sin⁻¹" || ClickedText == L"cos⁻¹" || ClickedText == L"tan⁻¹"
		|| ClickedText == L"x²" || ClickedText == L"10ˣ" || ClickedText == L"log" || ClickedText == L"eˣ"
		|| ClickedText == L"x³" || ClickedText == L"ln" || ClickedText == L"√"
		|| ClickedText == L"1/x" || ClickedText == L"n!" || ClickedText == L"%" || ClickedText == L"Mod") {
		IsUnaryOperator = true;
	}
	else {
		IsUnaryOperator = false;
	}
	return IsUnaryOperator;
}