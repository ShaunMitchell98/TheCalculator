#include "Calculator.h"
#include <cmath>
#include <vector>
#include <iterator>


constexpr auto M_PI = 3.1415926535;
constexpr auto M_E = 2.7182818284; //e to 10 decimal places

Calculator::Calculator() {

}


int Calculator::FindEndIndex(std::vector<Platform::String^> Tokens, int StartIndex) {

	int EmbeddedOpenBrackets = 0;
	int EndIndex = StartIndex;

	//If we find an open bracket we track its index and start looking 
		//for a matching close bracket. If more open brackets occur while
		//searching for a closed bracket then these must be closed before
		//the open bracket of interest can be closed. Therefore embedded
		//brackets are checked for. Once a close bracket has been 
		//found for our open bracket, we track its index and pass this
		// along with the open bracket index and the Tokens array to 
		//EvaluateBracketedExpression 

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
Platform::String^ Calculator::EvaluateBracketedExpression(std::vector<Platform::String^> Tokens) {

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
			Tokens.emplace(Tokens.begin() + EmbeddedOpenBracketIndex, EvaluateBracketedExpression(EmbeddedBracket));
			j = 1;
		}
	}

	//Loop over each element in the bracket and check whether it is a unary operator or a binary operator. 
	for (int i = 1; i < Tokens.size(); i++) {
		if (parser.IsUnaryOperator(Tokens[i])) {
			Tokens[i] = EvaluateUnaryOperation(Tokens[i], Tokens[i+1]);
			//Erase the element at address j+1 from params.Tokens.
			Tokens.erase(Tokens.begin() + i + 1);
			i = 1;
		}
		else if (parser.IsBinaryOperator(Tokens[i])) {
			Tokens[i - 1] = EvaluateBinaryOperation(Tokens[i - 1], Tokens[i + 1],
		        Tokens[i]);
			//Erase the elements at addresses j+1 and j from params.Tokens.
			Tokens.erase(Tokens.begin() + i + 1);
		    Tokens.erase(Tokens.begin() + i);
			i = 1;
		}
		else if (i == Tokens.size() - 1) {
			Tokens.erase(Tokens.begin() + Tokens.size() - 1);
			Tokens.erase(Tokens.begin());
			i = 1;
		}
	}
	return Tokens[0];
}



Platform::String^ Calculator::EvaluateUnaryOperation(Platform::String^ UnaryOperator, Platform::String^ StringNumber) {

	double result;
	double Number = _wtof(StringNumber->Data());
	if (UnaryOperator == L"sin") {
		result = sin(Number);
	}
	else if (UnaryOperator == L"cos") {
		result = cos(Number);
	}
	else if (UnaryOperator == L"tan") {
		result = tan(Number);
	}
	else if (UnaryOperator == L"sin⁻¹") {
		result = asin(Number) * (180 / M_PI);
	}
	else if (UnaryOperator == L"cos⁻¹") {
		result = acos(Number) * (180 / M_PI);
	}
	else if (UnaryOperator == L"tan⁻¹") {
		result = atan(Number) * (180 / M_PI);
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
		result = FirstNumber / SecondNumber;
	}
	else if (BinaryOperator == "Exp") {
		result = FirstNumber * pow(10, SecondNumber);
	}
	else if (BinaryOperator == L"xʸ") {
		result = pow(FirstNumber, SecondNumber);
	}
	Platform::String^ StringResult = result.ToString();
	return StringResult;
}

double Calculator::Factorial(double Number) {
	return (Number == 1 || Number == 0) ? 1 : Factorial(Number - 1) * Number;
}