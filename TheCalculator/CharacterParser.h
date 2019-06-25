#pragma once
#include "HandleDigitParams.h"
using namespace Windows::UI::Xaml::Controls;
using namespace Platform;

	class CharacterParser sealed 
	{
	public:
			CharacterParser();
			void DisplayCharacter(String^ ClickedText, TextBlock^ ScreenText);
			String^ LogCharacter(String^ ClickedText, String^ DisplayedText);
			HandleDigitParams HandleDigit(Platform::String^ Digit, HandleDigitParams params);
			int RefStringToInt(Platform::String^ theString);
			bool IsInt(String^ character);
			bool IsOperator(Platform::String^ character);
			TextBlock^ DisplayLoggedCharacters(String^ LoggedCharacters, TextBlock^ ScreenLoggedCharacters);
			HandleDigitParams TerminateNumber(HandleDigitParams params);
			HandleDigitParams HandleOperator(HandleDigitParams params, Platform::String^ character);
			//Platform::String^ * GetOperators(HandleDigitParams params);
	};


