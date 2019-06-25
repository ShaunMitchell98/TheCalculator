#include "pch.h"
#include "CppUnitTest.h"
#include "..\TheCalculator\CharacterParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TheCalculatorTests
{
    TEST_CLASS(CharacterParserTest)
    {
    public:
        TEST_METHOD(RefStringToInt)
        {
			Platform::String^ Digit = "5";
			int five = 5;
			CharacterParser parser();
			int HandledDigit = parser.HandleDigit(Digit);
			Assert::AreEqual(five, HandledDigit);
        }

		TEST_METHOD(MultipleDigits)
		{
			Platform::String^ NumberArray[] = { "1", "2", "3" };
			Platform::String^ CurrentDigit;
			int Number = 123;
			CharacterParser parser();
			int HandledNumber;
			for (int i = 0; i < 2; i++) {
				CurrentDigit = NumberArray[i];
				HandledNumber = parser.HandleDigit(CurrentDigit);
			}
			Assert::AreEqual(Number, HandledNumber);
		}
    };
}