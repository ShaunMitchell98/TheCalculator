//
//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "TokenParser.h"

namespace TheCalculator
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>

	public ref class MainPage sealed
	{
	public:
		MainPage();
		void HandleToken(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void ResetParams(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void DisplayResult(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void ToggleUnit(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

	private:
		Platform::String^ DisplayToken(Platform::String^ Input, Platform::String^ ClickedText);
		CalculatorParams params;
		TokenParser parser;
	};
}