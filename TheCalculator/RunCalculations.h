#pragma once
#include "CalculatorParams.h"
#include "CharacterParser.h"
#include "Calculator.h"
#include "CloseBrackets.h"
#include <vector>
#include <iterator>


double RunCalculations(CalculatorParams params)
{
	CharacterParser parser;
	Calculator calculator;
	double result = 0.0;
	if (params.CurrentNumber != 0) {
		params.Tokens.push_back(params.CurrentNumber.ToString());
		params = parser.TerminateNumber(params);
	}


	if (params.Tokens.size() == 1) {
		result = _wtof(params.Tokens[0]->Data());
	}

	//Check for any unclosed brackets. If any are found the last open bracket
	//is closed at the end. All others are closed two tokens away, such that
	//there is one token between the open and closed bracket.
	params.Tokens = CloseBrackets(params.Tokens);
	
	//Loop over each open bracket and pass the numbers between this
	//open bracket and the close bracket with the same index to 
	//HandleBracketedExpression.
	
	for (int i = 0; i < params.Tokens.size(); i++) {
		
		//Check each token to see if it is an open bracket.
		if (params.Tokens[i] == "(") {
			int StartIndex = i;
			int EndIndex = calculator.FindEndIndex(params.Tokens, StartIndex);
			std::vector<Platform::String^> BracketedExpression(params.Tokens.begin() + 
				StartIndex, params.Tokens.begin() + EndIndex + 1);
				
			for (int i = EndIndex; i >= StartIndex; i--) {
				params.Tokens.erase(params.Tokens.begin() + i);
			}
			params.Tokens.emplace(params.Tokens.begin() + StartIndex, 
				calculator.EvaluateBracketedExpression(BracketedExpression));
			i = 0;
			}
	}

	for (int i = 0;  i < params.Tokens.size(); i++) {
		if (parser.IsUnaryOperator(params.Tokens[i])) {
			if (params.Tokens[i] == L"x²" || params.Tokens[i] == L"x³" || 
				params.Tokens[i] == L"xʸ" || params.Tokens[i] == L"n!") {
				params.Tokens[i-1] = calculator.EvaluateUnaryOperation(params.Tokens[i], params.Tokens[i-1]);
				params.Tokens.erase(params.Tokens.begin() + i);
				//This line restarts the loop from the beginning of tokens. This
		        //may be needed if index changes executed by 
		        //HandleUnaryOperation mess up the indexing here.
				i = 0;
		   }
			else {
				params.Tokens[i] = calculator.EvaluateUnaryOperation(params.Tokens[i],
					params.Tokens[i + 1]);
				params.Tokens.erase(params.Tokens.begin() + i + 1);
				i = 0;
			}
		}
	}

	for (int i = 0; i < params.Tokens.size(); i++) {
		if (parser.IsBinaryOperator(params.Tokens[i])) {
		    params.Tokens[i-1] = calculator.EvaluateBinaryOperation(params.Tokens[i-1], 
				params.Tokens[i+1], params.Tokens[i]);
			params.Tokens.erase(params.Tokens.begin() + i + 1);
			params.Tokens.erase(params.Tokens.begin() + i);
		}
	}

	result = _wtof(params.Tokens[0]->Data());
	return result;
}