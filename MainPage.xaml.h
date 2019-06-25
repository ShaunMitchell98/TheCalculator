//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "CharacterParser.h"
#include "HandleDigitParams.h"

namespace TheCalculator
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>

	public ref class MainPage sealed
	{
	public:
		MainPage();
		void HandleCharacter(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

	private:
		void RunCalculations(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		HandleDigitParams params;
		void ResetParams(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}