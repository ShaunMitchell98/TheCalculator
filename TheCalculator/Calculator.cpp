#include "Calculator.h"
#include <cmath>
#include <vector>
#include <iterator>


constexpr auto M_PI = 3.1415926535;
constexpr auto M_E = 2.7182818284; //e to 10 decimal places
constexpr auto DIVIDE_BY_ZERO_ERROR = DBL_MAX;

Calculator::Calculator() {

}


int Calculator::FindEndIndex(std::vector<Platform::String^> Tokens, int StartIndex) {

	int EmbeddedOpenBrackets = 0;
	int EndIndex = StartIndex;

	//If we find an embedded open bracket before we find the closed bracket, we increment
	//a counter. If we find a closed bracket while there are embedded open brackets we 
	//decrement this counter. If the counter is zero and we find a closed bracket we know
	//it closes the open bracket we are interested in and we pass its index to the caller.
	//Note that this function assumes all open brackets have been closed and therefore 
	//the CloseBrackets() function needs to have been called on the Tokens vector
	//prior to calling this function.

	for (int j = (StartIndex+1); j < Tokens.size(); j++) {
		if (Tokens[j] == "(") {
			EmbeddedOpenBrackets++;
		}
		else if (Tokens[j] == ")" && EmbeddedOpenBrackets != 0) {
			EmbeddedOpenBrackets--;
		}
		else if (Tokens[j] == ")" && EmbeddedOpenBrackets == 0) {
			EndIndex = j;
			break;
		}
	}
	return EndIndex;
}

//Replace a bracketed expression with a single number.
Platform::String^ Calculator::EvaluateBracketedExpression(std::vector<Platform::String^> Tokens, AngleUnit Unit) {

	//If there is a bracketed expression within the bracketed expression we
	//must recursively call this function until there are no more embedded
	//bracketed expressions. At this point we can evaluate the innermost bracketed
	//expression then work outwards.

	int EmbeddedOpenBracketIndex;
	int EmbeddedCloseBracketIndex;

	for (int j = 1; j  < Tokens.size(); j++) {
		//Check if a close bracket occurs before an open bracket is found.
		//If this occurs then there are no embedded brackets and we
		//can continue to the evaluation stage.
		if (Tokens[j] == "(") {
			EmbeddedOpenBracketIndex = j;
			EmbeddedCloseBracketIndex = FindEndIndex(Tokens, j);
			std::vector<Platform::String^> EmbeddedBracket(Tokens.begin() + EmbeddedOpenBracketIndex,
				Tokens.begin() + EmbeddedCloseBracketIndex + 1);
			for (int i = EmbeddedCloseBracketIndex; i >= EmbeddedOpenBracketIndex; i--) {
				Tokens.erase(Tokens.begin() + i);
			}
			Tokens.emplace(Tokens.begin() + EmbeddedOpenBracketIndex, EvaluateBracketedExpression(EmbeddedBracket, Unit));
			j = 1;
		}
	}



	for (int i = 1; i < Tokens.size(); i++) {
		if (parser.IsUnaryOperator(Tokens[i])) {
			//For these five unary operations, the operators follow their operands, for all
			//other operations, the operator precedes the operand.
			if (Tokens[i] == L"x²" || Tokens[i] == L"x³" ||
				Tokens[i] == L"xʸ" || Tokens[i] == L"n!" || Tokens[i] == L"%") {
				Tokens[i - 1] = EvaluateUnaryOperation(Tokens[i], Tokens[i - 1], Unit);
				Tokens.erase(Tokens.begin() + i);
				//This line restarts the loop from the beginning of tokens. This
				//may be needed if index changes executed by 
				//EvaluateUnaryOperation mess up the indexing here.
				i = 0;
			}
			else {
				Tokens[i] = EvaluateUnaryOperation(Tokens[i],
					Tokens[i + 1], Unit);
				Tokens.erase(Tokens.begin() + i + 1);
				i = 0;
			}
		}
	}
	for (int i = 1; i < Tokens.size(); i++) {
		if (Tokens[i] == "X" || Tokens[i] == "÷") {
			Tokens[i - 1] = EvaluateBinaryOperation(Tokens[i - 1], Tokens[i + 1],
				Tokens[i]);
			if (Tokens[i - 1] == DIVIDE_BY_ZERO_ERROR.ToString()) {
				return Tokens[i - 1];
			}
			//Erase the elements at addresses j+1 and j from params.Tokens.
			Tokens.erase(Tokens.begin() + i + 1);
			Tokens.erase(Tokens.begin() + i);
			i = 1;
		}
	}
	for (int i = 1; i < Tokens.size(); i++) {
		if (parser.IsBinaryOperator(Tokens[i])) {
			Tokens[i - 1] = EvaluateBinaryOperation(Tokens[i - 1], Tokens[i + 1],
				Tokens[i]);
			if (Tokens[i - 1] == DIVIDE_BY_ZERO_ERROR.ToString()) {
				return Tokens[i - 1];
			}
			//Erase the elements at addresses j+1 and j from params.Tokens.
			Tokens.erase(Tokens.begin() + i + 1);
			Tokens.erase(Tokens.begin() + i);
			i = 1;
		}
	}
	Tokens.erase(Tokens.begin() + Tokens.size() - 1);
	Tokens.erase(Tokens.begin());
	return Tokens[0]; 
}



Platform::String^ Calculator::EvaluateUnaryOperation(Platform::String^ UnaryOperator, Platform::String^ StringNumber, AngleUnit Unit) {

	double result;
	double Number = _wtof(StringNumber->Data());
	double UnitConversion; //Used for converting between radians and degrees if necessary.
	if (Unit == Degrees) {
		UnitConversion = 180 / M_PI;
	}
	else {
		UnitConversion = 1;
	}
	if (UnaryOperator == L"sin") {
		result = sin((1/UnitConversion) * Number);
	}
	else if (UnaryOperator == L"cos") {
		result = cos((1/UnitConversion) * Number);
	}
	else if (UnaryOperator == L"tan") {
		result = tan((1/UnitConversion) * Number);
	}
	else if (UnaryOperator == L"sin⁻¹") {
		result = asin(Number) * UnitConversion;
	}
	else if (UnaryOperator == L"cos⁻¹") {
		result = acos(Number) * UnitConversion;
	}
	else if (UnaryOperator == L"tan⁻¹") {
		result = atan(Number) * UnitConversion;
	}
	else if (UnaryOperator == L"x²") {
		result = pow(Number, 2);
	}
	else if (UnaryOperator == L"10ˣ") {
		result = pow(10, Number);
	}
	else if (UnaryOperator == L"log") {
		result = log10(Number);
	}
	else if (UnaryOperator == L"eˣ") {
		result = pow(M_E, Number);
	}
	else if (UnaryOperator == L"n!") {
		result = Factorial(Number);
	}
	else if (UnaryOperator == L"x³") {
		result = pow(Number, 3);
	}
	else if (UnaryOperator == L"ln") {
		result = log(Number);
	}
	else if (UnaryOperator == L"√") {
		result = sqrt(Number);
	}
	else if (UnaryOperator == L"1/x") {
		result = 1 / Number;
	}
	else if (UnaryOperator == L"%") {
		result = Number / 100;
	}
	else if (UnaryOperator == L"Mod") {
		result = Number;
		if (Number < 0) {
			result = -Number;
		}
	}
	Platform::String^ StringResult = result.ToString();
	return StringResult;
}

Platform::String^ Calculator::EvaluateBinaryOperation(Platform::String^ StringFirstNumber,
	Platform::String^ StringSecondNumber, Platform::String^ BinaryOperator)
{
	double result;
	double FirstNumber = _wtof(StringFirstNumber->Data());
	double SecondNumber = _wtof(StringSecondNumber->Data());

	if (BinaryOperator == "+") {
		result = FirstNumber + SecondNumber;
	}
	else if (BinaryOperator == "-") {
		result = FirstNumber - SecondNumber;
	}
	else if (BinaryOperator == "X") {
		result = FirstNumber * SecondNumber;
	}
	else if (BinaryOperator == "÷") {
		if (SecondNumber == 0) {
			result = DIVIDE_BY_ZERO_ERROR;
		}
		else {
			result = FirstNumber / SecondNumber;
		}
	}
	else if (BinaryOperator == "Exp") {
		result = FirstNumber * pow(10, SecondNumber);
	}
	else if (BinaryOperator == L"xʸ") {
		result = pow(FirstNumber, SecondNumber);
	}
	else if (BinaryOperator == L"yvx") {
		result = pow(SecondNumber, 1 / (FirstNumber));
	}
	Platform::String^ StringResult = result.ToString();
	return StringResult;
}

double Calculator::Factorial(double Number) {
	return (Number == 1 || Number == 0) ? 1 : Factorial(Number - 1) * Number;
}