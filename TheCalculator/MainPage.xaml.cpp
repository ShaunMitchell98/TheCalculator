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

	params = parser.HandleCharacter(ClickedText, params);
	ScreenText->Text = params.DisplayOutput;
}


//This function resets CalculatorParams and the ScreenText. It is called when
//the user clicks C.
void TheCalculator::MainPage::ResetParams(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	params.CurrentNumber = 0;

	params.Tokens.clear();

	//Reset parameters tracking numbers and operators.
	params.Decimal = false;
	params.Multiplier = 1.0;
	params.DisplayOutput = "0";
	ScreenText->Text = "0";
}


void TheCalculator::MainPage::DisplayResult(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
 	double result = RunCalculations(params);
	ScreenText->Text = result.ToString();
}
