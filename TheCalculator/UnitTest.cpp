#include "pch.h"
#include "CppUnitTest.h"
#include "..\TheCalculator\CharacterParser.h"
#include "..\TheCalculator\CalculatorParams.h"
//#include "..\TheCalculator\MainPage.xaml.h"
#include "..\TheCalculator\RunCalculations.h"
#include <math.h>

#define M_PI 3.14159265359
#define M_E 2.7182818284

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Platform;

namespace TheCalculatorUnitTests
{
	TEST_CLASS(CharacterParserTests)
	{
	public:

		TEST_METHOD(RefStringToInt)
		{
			Platform::String^ Digit = "5";
			double five = 5.0;
			CalculatorParams params;
			CharacterParser parser;
			params = parser.HandleCharacter(Digit, params);
			Assert::AreEqual(five, params.CurrentNumber);
		}


		//When HandleDigits is passed a sequence of digits, the
		//first digit should be stored in a temporary 
		TEST_METHOD(MultipleDigits)
		{
			Platform::String^ TestString[] = { "1", "2", "3" };
			double Number = 123.0;
			CalculatorParams params;
			CharacterParser parser;
			for (int i = 0; i < (sizeof(TestString) / sizeof(*TestString)); i++) {
				params = parser.HandleCharacter(TestString[i], params);
			}
			Assert::AreEqual(Number, params.CurrentNumber);
		}

		TEST_METHOD(TerminateNumber)
		{
			Platform::String^ TestString[] = { "1", "2", "3", "+" };
			CharacterParser parser;
			CalculatorParams params;
			for (int i = 0; i < (sizeof(TestString) / sizeof(*TestString)); i++) {
				params = parser.HandleCharacter(TestString[i], params);
			}
			Assert::AreEqual(123.0, params.Numbers[0]);
		}

		TEST_METHOD(DecimalSupport) {
			Platform::String^ TestString[] = { "2", ".", "5", "+", "7", ".", "5" };
			CalculatorParams params;
			CharacterParser parser;
			double ExpectedOutput = 10.0;
			for (int i = 0; i < (sizeof(TestString)/sizeof(*TestString)); i++) {;
				params = parser.HandleCharacter(TestString[i], params);
			}
            double result = RunCalculations(params);
			Assert::AreEqual(result, ExpectedOutput);
		}

		TEST_METHOD(Pi) {
			Platform::String^ Pi = L"π";
			CalculatorParams params;
			CharacterParser parser;
			params = parser.HandleCharacter(Pi, params);
			Assert::AreEqual(params.Numbers[0], M_PI);
		}
		TEST_METHOD(Exponential) {
			Platform::String^ TestString[] = { L"eˣ", "2" };
			CalculatorParams params;
			Platform::String^ ExpectedOutput = "7.38906";
			CharacterParser parser;
			for (int i = 0; i < (sizeof(TestString) / sizeof(*TestString)); i++) {
				params = parser.HandleCharacter(TestString[i], params);
			}
			double result = RunCalculations(params);
			Platform::String^ ActualOutput = result.ToString();
			Assert::AreEqual(ExpectedOutput, ActualOutput);
		}

		TEST_METHOD(Square_x) {
			Platform::String^ TestString[] = { "5", L"x²" };
			CalculatorParams params;
			Platform::String^ ExpectedOutput = "25";
			CharacterParser parser;
			for (int i = 0; i < (sizeof(TestString) / sizeof(*TestString)); i++) {
				params = parser.HandleCharacter(TestString[i], params);
			}
			double result = RunCalculations(params);
			Platform::String^ ActualOutput = result.ToString();
			Assert::AreEqual(ExpectedOutput, ActualOutput);
		}

		TEST_METHOD(ExponentToY) {
			Platform::String^ TestString[] = { "5", L"xʸ", "4" };
			CalculatorParams params;
			Platform::String^ ExpectedOutput = "625";
			CharacterParser parser;
			for (int i = 0; i < (sizeof(TestString) / sizeof(*TestString)); i++) {
				params = parser.HandleCharacter(TestString[i], params);
			}
			double result = RunCalculations(params);
			Platform::String^ ActualOutput = result.ToString();
			Assert::AreEqual(ExpectedOutput, ActualOutput);
		}

		TEST_METHOD(Cube_x) {
			Platform::String^ TestString[] = { L"x³", "5" };
			CalculatorParams params;
			Platform::String^ ExpectedOutput = "125";
			CharacterParser parser;
			for (int i = 0; i < (sizeof(TestString) / sizeof(*TestString)); i++) {
				params = parser.HandleCharacter(TestString[i], params);
			}
			double result = RunCalculations(params);
			Platform::String^ ActualOutput = result.ToString();
			Assert::AreEqual(ExpectedOutput, ActualOutput);
		}

		TEST_METHOD(Square_Root) {
			Platform::String^ TestString[] = { L"√", "1", "6" };
			CalculatorParams params;
			Platform::String^ ExpectedOutput = "4";
			CharacterParser parser;
			for (int i = 0; i < (sizeof(TestString) / sizeof(*TestString)); i++) {
				params = parser.HandleCharacter(TestString[i], params);
			}
			double result = RunCalculations(params);
			Platform::String^ ActualOutput = result.ToString();
			Assert::AreEqual(ExpectedOutput, ActualOutput);
		}

		TEST_METHOD(Ten_To_Power_Of_x) {
			Platform::String^ TestString[] = { L"10ˣ", "3"};
			CalculatorParams params;
			Platform::String^ ExpectedOutput = "1000";
			CharacterParser parser;
			for (int i = 0; i < (sizeof(TestString) / sizeof(*TestString)); i++) {
				params = parser.HandleCharacter(TestString[i], params);
			}
			double result = RunCalculations(params);
			Platform::String^ ActualOutput = result.ToString();
			Assert::AreEqual(ExpectedOutput, ActualOutput);
		}

		TEST_METHOD(Log_Base_10) {
			Platform::String^ TestString[] = {  L"log", "1", "0", "0", };
			CalculatorParams params;
			Platform::String^ ExpectedOutput = "2";
			CharacterParser parser;
			for (int i = 0; i < (sizeof(TestString) / sizeof(*TestString)); i++) {
				params = parser.HandleCharacter(TestString[i], params);
			}
			double result = RunCalculations(params);
			Platform::String^ ActualOutput = result.ToString();
			Assert::AreEqual(ExpectedOutput, ActualOutput);
		}

		TEST_METHOD(Natural_Log) {
			Platform::String^ TestString[] = { L"ln", "2" };
			CalculatorParams params;
			Platform::String^ ExpectedOutput = "0.693147";
			CharacterParser parser;
			for (int i = 0; i < (sizeof(TestString) / sizeof(*TestString)); i++) {
				params = parser.HandleCharacter(TestString[i], params);
			}
			double result = RunCalculations(params);
			Platform::String^ ActualOutput = result.ToString();
			Assert::AreEqual(ExpectedOutput, ActualOutput);
		}

		TEST_METHOD(Plus_Minus) {
			Platform::String^ TestString[] = { "3", L"±" };
			CalculatorParams params;
			double ExpectedOutput = -3;
			CharacterParser parser;
			for (int i = 0; i < (sizeof(TestString) / sizeof(*TestString)); i++) {
				params = parser.HandleCharacter(TestString[i], params);
			}
			Assert::AreEqual(ExpectedOutput, params.CurrentNumber);
		}

		TEST_METHOD(Factorial) {
			Platform::String^ TestString[] = { "5", L"n!" };
			CalculatorParams params;
			double ExpectedOutput = 120;
			CharacterParser parser;
			for (int i = 0; i < (sizeof(TestString) / sizeof(*TestString)); i++) {
				params = parser.HandleCharacter(TestString[i], params);
			}
			Assert::AreEqual(ExpectedOutput, params.CurrentNumber);
		}

		TEST_METHOD(asin) {
			Platform::String^ TestString[] = { L"sin⁻¹", "0", ".", "5", ")" };
			CalculatorParams params;
			Platform::String^ ExpectedOutput = "30";
			CharacterParser parser;
			for (int i = 0; i < (sizeof(TestString) / sizeof(*TestString)); i++) {
				params = parser.HandleCharacter(TestString[i], params);
			}
			double result = RunCalculations(params);
			Platform::String^ ActualOutput = result.ToString();
			Assert::AreEqual(ExpectedOutput, ActualOutput);
		}

		TEST_METHOD(acos) {
			Platform::String^ TestString[] = { L"cos⁻¹", "0", ".", "5", ")" };
			CalculatorParams params;
			Platform::String^ ExpectedOutput ="60";
			CharacterParser parser;
			for (int i = 0; i < (sizeof(TestString) / sizeof(*TestString)); i++) {
				params = parser.HandleCharacter(TestString[i], params);
			}
			double result = RunCalculations(params);
			Platform::String^ ActualOutput = result.ToString();
			Assert::AreEqual(ExpectedOutput, ActualOutput);
		}

		TEST_METHOD(atan) {
			Platform::String^ TestString[] = { L"tan⁻¹", "1", ")"};
			CalculatorParams params;
			Platform::String^ ExpectedOutput = "45";
			CharacterParser parser;
			for (int i = 0; i < (sizeof(TestString) / sizeof(*TestString)); i++) {
				params = parser.HandleCharacter(TestString[i], params);
			}
			double result = RunCalculations(params);
			Platform::String^ ActualOutput = result.ToString();
			Assert::AreEqual(ExpectedOutput, ActualOutput);
		}

		TEST_METHOD(Exp) {
			Platform::String^ TestString[] = { "2", "Exp", "2" };
			CalculatorParams params;
			double ExpectedOutput = 200;
			CharacterParser parser;
			for (int i = 0; i < (sizeof(TestString) / sizeof(*TestString)); i++) {
				params = parser.HandleCharacter(TestString[i], params);
			}
			params = parser.TerminateNumber(params);
			Assert::AreEqual(ExpectedOutput, params.Numbers[0]);
		}

		TEST_METHOD(Reciprocal) {
			Platform::String^ TestString[] = { L"1/x", "2" };
			CalculatorParams params;
			Platform::String^ ExpectedOutput = "0.5";
			CharacterParser parser;
			for (int i = 0; i < (sizeof(TestString) / sizeof(*TestString)); i++) {
				params = parser.HandleCharacter(TestString[i], params);
			}
			double result = RunCalculations(params);
			Platform::String^ ActualOutput = result.ToString();
			Assert::AreEqual(ExpectedOutput, ActualOutput);
		}

		TEST_METHOD(Brackets) {
			Platform::String^ TestString[] = { L"sin", "6", "+", "7", L")"};
			Platform::String^ ExpectedOutput ="0.420167";
			CalculatorParams params;
			CharacterParser parser;
			for (int i = 0; i < (sizeof(TestString) / sizeof(*TestString)); i++) {
				params = parser.HandleCharacter(TestString[i], params);
			}
			double result = RunCalculations(params);
			Platform::String^ ActualOutput = result.ToString();
			Assert::AreEqual(ExpectedOutput, ActualOutput);
		}
	};
}