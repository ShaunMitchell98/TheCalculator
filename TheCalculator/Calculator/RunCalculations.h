#pragma once
#include "CalculatorParams.h"
#include "TokenParser.h"
#include "Calculator.h"
#include "CloseBrackets.h"
#include <vector>
#include <iterator>

constexpr auto DIVIDE_BY_ZERO_ERROR = DBL_MAX;

double RunCalculations(CalculatorParams params)
{
	TokenParser parser;
	Calculator calculator;
	
	//This will store the result of the calculations.
	double result = 0.0;

	//If there is only a single token, we assume it is a number and return
	//it as the result.
	if (params.Tokens.size() == 1) {
		result = _wtof(params.Tokens[0]->Data());
		return result;
	}

	//Check for any unclosed brackets. If any are found, closed brackets
	//are pushed to the end of Tokens until all open brackets are closed.
	params.Tokens = CloseBrackets(params.Tokens);
	
	//Loop over each token and if it is an open bracket, pass the tokens between this
	//open bracket and the corresponnding closed bracket to 
	//EvaluateBracketedExpression. These tokens are removed from the Tokens vector
	//and replaced with the outut of the function.
	for (int i = 0; i < params.Tokens.size(); i++) {
		
		if (params.Tokens[i] == "(") {
			int StartIndex = i;
			int EndIndex = calculator.FindEndIndex(params.Tokens, StartIndex);
			std::vector<Platform::String^> BracketedExpression(params.Tokens.begin() +
				StartIndex, params.Tokens.begin() + EndIndex + 1);

			//Remove bracketed expression from Tokens.
			for (int i = EndIndex; i >= StartIndex; i--) {
				params.Tokens.erase(params.Tokens.begin() + i);
			}

			//Place result of bracketed expression where the bracketed expression
			//used to be.
			params.Tokens.emplace(params.Tokens.begin() + StartIndex,
				calculator.EvaluateBracketedExpression(BracketedExpression, params.Unit));
			i = 0;
			if (params.Tokens[StartIndex] == DIVIDE_BY_ZERO_ERROR.ToString()) {
				return _wtof(params.Tokens[StartIndex]->Data());
			}
		}
	}

	//Check Tokens for Unary operations and perform them.
	for (int i = 0;  i < params.Tokens.size(); i++) {
		if (parser.IsUnaryOperator(params.Tokens[i])) {
			//For these four unary operations, the operators follow their operands, for all
			//other operations, the operator precedes the operand.
			if (params.Tokens[i] == L"x²" || params.Tokens[i] == L"x³" || 
				params.Tokens[i] == L"xʸ" || params.Tokens[i] == L"n!" ||
				params.Tokens[i] == L"%") {
				params.Tokens[i-1] = calculator.EvaluateUnaryOperation(params.Tokens[i], params.Tokens[i-1], params.Unit);
				params.Tokens.erase(params.Tokens.begin() + i);
				//This line restarts the loop from the beginning of tokens. This
		        //may be needed if index changes executed by 
		        //EvaluateUnaryOperation mess up the indexing here.
				i = 0;
		   }
			else {
				params.Tokens[i] = calculator.EvaluateUnaryOperation(params.Tokens[i],
					params.Tokens[i + 1], params.Unit);
				params.Tokens.erase(params.Tokens.begin() + i + 1);
				i = 0;
			}
		}
	}

	//These for loops calculate binary operations. Multiplication and division are performed
	//before addition and subtraction, as per BIDMAS.
	for (int i = 0; i < params.Tokens.size(); i++) {
		if (params.Tokens[i] == "X" || params.Tokens[i] == "÷") {
			params.Tokens[i - 1] = calculator.EvaluateBinaryOperation(params.Tokens[i - 1],
				params.Tokens[i + 1], params.Tokens[i]);
			if (params.Tokens[i - 1] == DIVIDE_BY_ZERO_ERROR.ToString()) {
				return _wtof(params.Tokens[i - 1]->Data());
			}
			params.Tokens.erase(params.Tokens.begin() + i + 1);
			params.Tokens.erase(params.Tokens.begin() + i);
			i = 0;
		}
	}
	for (int i = 0; i < params.Tokens.size(); i++) {
		if (parser.IsBinaryOperator(params.Tokens[i])) {
			params.Tokens[i - 1] = calculator.EvaluateBinaryOperation(params.Tokens[i - 1],
				params.Tokens[i + 1], params.Tokens[i]);
			if (params.Tokens[i + 1] == DIVIDE_BY_ZERO_ERROR.ToString()) {
				return _wtof(params.Tokens[i+1]->Data());
			}
			params.Tokens.erase(params.Tokens.begin() + i + 1);
			params.Tokens.erase(params.Tokens.begin() + i);
			i = 0;
		}
	}

	result = _wtof(params.Tokens[0]->Data());
	return result;
}