#pragma once

#include "CalculatorParams.h"
#include <vector>


int FindNumberOfUnclosedOpenBrackets(std::vector<Platform::String^> Tokens) {

	int NumberOfUnclosedOpenBrackets = 0;


	for (int i = 0; i < Tokens.size(); i++) {

		if (Tokens[i] == "(") {
			NumberOfUnclosedOpenBrackets++;
		}
		else if (Tokens[i] == ")") {
			NumberOfUnclosedOpenBrackets--;
		}
	}
	return NumberOfUnclosedOpenBrackets;
}

std::vector<Platform::String^> CloseBrackets(std::vector<Platform::String^> Tokens) {
	

	int NumberOfUnclosedOpenBrackets = FindNumberOfUnclosedOpenBrackets(Tokens);
	for (int i = 0; i < NumberOfUnclosedOpenBrackets; i++) {
		Tokens.push_back(")");
	}
	return Tokens;
}