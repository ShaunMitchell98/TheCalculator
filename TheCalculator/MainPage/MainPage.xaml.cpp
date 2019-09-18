//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include <collection.h>
#include <ppltasks.h>
#include "App.xaml.h"
#include "MainPage.xaml.h"
#include <cmath>
#include "RunCalculations.h"
#include <string>

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


//This is the event handler for most button presses. It uses the parser to categories the input as a number, or operator.
//It also handles displaying the token in the output window.
void MainPage::HandleToken(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

	//Saves the text in the button clicked by the user as a string which
	//can be used in various Parser functions.
	Button^ ClickedButton = safe_cast <Button^> (sender);
	TextBlock^ ClickedTextBlock = safe_cast <TextBlock^> (ClickedButton->Content);
	Platform::String^ ClickedText = ClickedTextBlock->Text;

	params = parser.ParseToken(ClickedText, params);
 	params.DisplayOutput = DisplayToken(params.DisplayOutput, ClickedText);
	ScreenText->Text = params.DisplayOutput;
}

Platform::String^ MainPage::DisplayToken(Platform::String^ Input, Platform::String^ ClickedText) {

	if (ClickedText == L"sin" || ClickedText == L"cos" || ClickedText == L"tan"
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
			Input = L"10^(";
		}
		else {
			Input = Input + L"10^";
		}
	}
	else if (ClickedText == L"eˣ") {
		if (Input == "0") {
			Input = L"e^(";
		}
		else {
			Input = Input + L"e^(";
		}
	}
	else if (ClickedText == L"x³") {
		Input = Input + "³";
	}
	else if (ClickedText == L"1/x") {
		if (Input == "0") {
			Input = "1/(";
		}
		else {
			Input = Input + "1/(";
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
	else if (ClickedText == L"yvx") {
		Input = Input + "v";
	}
	else if (ClickedText == L"Mod") {
		if (Input == "0") {
			Input = "|";
		}
		else {
			Input = Input + "|";
		}
	}
	else {
		if (Input == "0") {
			Input = ClickedText;
		}
		else {
			Input = Input + ClickedText;
		}
	}
	return Input;
}

//When the user clicks the Ded/Rad button, this function is called to change the unit. This affects functions such as sin().
void MainPage::ToggleUnit(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
	
	Button^ ClickedButton = safe_cast <Button^> (sender);
	TextBlock^ ClickedTextBlock = safe_cast <TextBlock^> (ClickedButton->Content);
	Platform::String^ ClickedText = ClickedTextBlock->Text;

	if (ClickedText == L"Deg") {
		params.Unit = Degrees;
		ClickedTextBlock->Text = L"Rad";
	}
	else if (ClickedText == L"Rad") {
		params.Unit = Degrees;
		ClickedTextBlock->Text = L"Deg";
	}
}


//This function resets CalculatorParams and the ScreenText. It is called when
//the user clicks C.
void TheCalculator::MainPage::ResetParams(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    params.Tokens.clear();

	//Reset parameters tracking numbers and operators.
	params.EditingNumber = false;
	params.DisplayOutput = "0";
	ScreenText->Text = "0";
}

void TheCalculator::MainPage::DeleteToken(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
	int finalTokenLength = params.Tokens.back()->Length();
	params.Tokens.pop_back();
	std::wstring output = params.DisplayOutput->Data();
	output = output.substr(0, params.DisplayOutput->Length() - finalTokenLength);
	params.DisplayOutput = ref new Platform::String(output.c_str());
	ScreenText->Text = params.DisplayOutput;
}
//This function calculates the result of the inputs given by the user and displays the result.
void TheCalculator::MainPage::DisplayResult(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
 	double result = RunCalculations(params);
	if (result == 1.79769E+308) {
		ScreenText->Text = "Division by zero error!";
	}
	else {
		ScreenText->Text = result.ToString();
	}
}
