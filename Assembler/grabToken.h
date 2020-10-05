#pragma once
#ifndef GRABTOKEN_H_
#define GRABTOKEN_H_

#include "C:\Users\Dominik\source\repos\Assembler\Assembler\tokens.h"
#include "C:\Users\Dominik\source\repos\Assembler\ConsoleApplication1\Lexical Analysis.cpp"

class grabToken {

public:
	static Token grab(istream& myfile, int& lineNumber) {
		return getNextToken(myfile, lineNumber);
	}
};

#endif