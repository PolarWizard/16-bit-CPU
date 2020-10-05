#pragma once
#ifndef TOKENS_H_
#define TOKENS_H_

#include <string>
#include <iostream>
using namespace std;

enum TokenType {
	//Operator Identifier
	OPERATOR, //0

	//Operations
	HALT, //1
	ADD, //2
	SUB,//3
	AND,//4
	XOR,//5
	NOT,//6
	JMP,//7
	CMP,//8
	MOV,//9
	ASL,//10
	ASR,//11
	LSL,//12
	LSR,//13
	LOAD,//14
	SAVE,//15

	//Have reached EOF
	DONE,//16

	//Delimeter
	COMMA,//17

	//Token that tells us that this is a register value
	REGISTER,//18

	//Token that tells us that its a address value
	ADDRESS,//19

	//Token that tells us that theres a new line
	NL,//20

	//Token that tell us that we are a label
	LABEL, //21

	//Bad Token - General
	INVALID,//22

	//Bad Token - Specifics
	INVALID_symbol,
	INVALID_operator_digit,
	INVALID_operator_nonexistant,
	INVALID_register_digit,
	INVALID_register_alpha,
	INVALID_address_digit,
	INVALID_address_alpha,
};

class Token {

public:
	TokenType type;
	string lexeme;
	int lineNumber;

	Token() {
		type = INVALID;
		lexeme = "";
		lineNumber = -1;
	}

	Token(TokenType type, string lexeme, int lineNumber) {
		this->type = type;
		this->lexeme = lexeme;
		this->lineNumber = lineNumber;
	}

	TokenType getTokenType() const { return type; }
	string getLexeme() const { return lexeme; }
	int getLineNumber() const { return lineNumber; }
};

extern Token getNextToken(istream& myfile, int& lineNumber);
#endif // !TOKENS_H_