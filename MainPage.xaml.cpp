//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "CharacterParser.h"
#include <iostream>

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
	Button^ ClickedButton = safe_cast <Button^> (sender);
	TextBlock^ ClickedTextBlock = safe_cast <TextBlock^> (ClickedButton->Content);
	Platform::String^ ClickedText = ClickedTextBlock->Text;
	
	CharacterParser parser; // The parser handles the clicked text.
    parser.DisplayCharacter(ClickedText, ScreenText);

	//If the user clicks a number the parser converts the number clicked
	//into an internally stored number it can use for arithmetic.
	if (parser.IsInt(ClickedText)) {
      params = parser.HandleDigit(ClickedText, params);
	}
	if (parser.IsOperator(ClickedText) && params.NumberOfDigits != 0) 
	{
			params = parser.TerminateNumber(params);
			params = parser.HandleOperator(params, ClickedText);
	}
}


void TheCalculator::MainPage::RunCalculations(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	CharacterParser parser;
	int result = 0;
	if (params.CurrentNumber != 0) {
		params = parser.TerminateNumber(params);
	}
	

	for (int i = 0; i < (sizeof(params.Operators)/sizeof(*params.Operators)); i++) {
		if (params.Operators[i] == "+") {
			result = params.Numbers[i] + params.Numbers[i + 1];
			params.Numbers[i] = 0;
			params.Numbers[i + 1] = result;
        }
		if (params.Operators[i] == "-") {
			result = params.Numbers[i] - params.Numbers[i + 1];
			params.Numbers[i] = 0;
			params.Numbers[i + 1] = result;
		}
		if (params.Operators[i] == "X") {
			result = params.Numbers[i] * params.Numbers[i + 1];
			params.Numbers[i] = 0;
			params.Numbers[i + 1] = result;
		}
		if (params.Operators[i] == "÷") {
			result = params.Numbers[i] / params.Numbers[i + 1];
			params.Numbers[i] = 0;
			params.Numbers[i + 1] = result;
		}
	}
	ScreenText->Text = result.ToString();
}

void TheCalculator::MainPage::ResetParams(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	params.CurrentNumber = 0;
	params.NumberOfDigits = 0;
	for (int i = 0; i < (sizeof(params.Operators)/sizeof(*params.Operators)); i++) {
		if (params.Operators[i] != "") {
		params.Operators[i] = "";
		}
	}
	for (int j = 0; j < sizeof(params.Numbers); j++) {
		params.Numbers[j] = 0;
	}
	params.OperatorCount = 0;
	params.NumberCount = 0;
	ScreenText->Text = "";
}
