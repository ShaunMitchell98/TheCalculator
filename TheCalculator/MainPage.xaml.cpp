//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//
#define _USE_MATH_DEFINES

#include "pch.h"
#include "MainPage.xaml.h"
#include <cmath>

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

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409


MainPage::MainPage()
{
	InitializeComponent();
}



void MainPage::HandleCharacter(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

    //Saves the text in the button clicked by the user as a string which
	//can be used in various Parser functions.
	Button^ ClickedButton = safe_cast <Button^> (sender);
	TextBlock^ ClickedTextBlock = safe_cast <TextBlock^> (ClickedButton->Content);
	Platform::String^ ClickedText = ClickedTextBlock->Text;

    
	//When the user clicks a button, the text is displayed in the screen output.
	parser.DisplayCharacter(ClickedText, ScreenText);

	//If the user clicks a number the parser converts the number clicked
	//into an internally stored number it can use for arithmetic.
	if (parser.IsInt(ClickedText)) {
      params = parser.HandleDigit(ClickedText, params);
	}

	//Check whether the button clicked is a binary operator. If this is the case
	//we close the current number and save it for calculations and save the 
	//operator which is to be used on that number.
	if (parser.IsBinaryOperator(ClickedText) && params.NumberOfDigits != 0) 
	{
			params = parser.TerminateNumber(params);
			params = parser.HandleBinaryOperator(params, ClickedText);
	}
	if (parser.IsUnaryOperator(ClickedText)) 
	{
		params = parser.HandleUnaryOperator(params, ClickedText);
	}
	if (ClickedText == ")") {
		params = parser.TerminateNumber(params);
	}
	if (ClickedText == "L\u03C0") {
		params.Numbers[params.NumberCount] = M_PI;
		params.NumberCount = params.NumberCount + 1;
		ScreenText->Text = M_PI.ToString();
	}
}


double TheCalculator::MainPage::RunCalculations()
{
	CharacterParser parser;
	double result = 0.0;
	if (params.CurrentNumber != 0) {
		params = parser.TerminateNumber(params);
	}
	
	if (params.NumberCount = 1) {
		result = params.Numbers[0];
	}
	for (int i = 0; i < (sizeof(params.BinaryOperators)/sizeof(*params.BinaryOperators)); i++) {
		if (params.BinaryOperators[i] == "+") {
			result = params.Numbers[i] + params.Numbers[i + 1];
			params.Numbers[i] = 0;
			params.Numbers[i + 1] = result;
        }
		if (params.BinaryOperators[i] == "-") {
			result = params.Numbers[i] - params.Numbers[i + 1];
			params.Numbers[i] = 0;
			params.Numbers[i + 1] = result;
		}
		if (params.BinaryOperators[i] == "X") {
			result = params.Numbers[i] * params.Numbers[i + 1];
			params.Numbers[i] = 0;
			params.Numbers[i + 1] = result;
		}
		if (params.BinaryOperators[i] == "÷") {
			result = params.Numbers[i] / params.Numbers[i + 1];
			params.Numbers[i] = 0;
			params.Numbers[i + 1] = result;
		}
	}

	for (int i = 0; i < (sizeof(params.UnaryOperators) / sizeof(*params.UnaryOperators)); i++) {
		if (params.UnaryOperators[i] == "sin") {
			result = sin(params.Numbers[i]);
		}
		if (params.UnaryOperators[i] == "cos") {
			result = cos(params.Numbers[i]);
		}
		if (params.UnaryOperators[i] == "tan") {
			result = tan(params.Numbers[i]);
		}
	}
	return result;
}

//This function resets CalculatorParams and the ScreenText. It is called when
//the user clicks C.
void TheCalculator::MainPage::ResetParams(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	params.CurrentNumber = 0;
	params.NumberOfDigits = 0;

	//Reset the BinaryOperators array.
	for (int i = 0; i < (sizeof(params.BinaryOperators)/sizeof(*params.BinaryOperators)); i++) {
		params.BinaryOperators[i] = "D";
	}

	//Reset the numbers array.
	for (int j = 0; j < (sizeof(params.Numbers)/sizeof(*params.Numbers)); j++) {
		params.Numbers[j] = 0;
	}

	//Reset the UnaryOperators array.
	for (int k = 0; k < (sizeof(params.UnaryOperators) / sizeof(*params.UnaryOperators)); k++) {
		params.UnaryOperators[k] = "D";
	}

	//Reset parameters tracking numbers and operators.
	params.BinaryOperatorCount = 0;
	params.NumberCount = 0;
	params.UnaryOperatorCount = 0;
	ScreenText->Text = "0";
}


void TheCalculator::MainPage::HandleExponential(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	double result = this->RunCalculations();
	result = pow(M_E, result);
	ScreenText->Text = result.ToString();
}


void TheCalculator::MainPage::DisplayResult(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	double result = this->RunCalculations();
	ScreenText->Text = result.ToString();
}
