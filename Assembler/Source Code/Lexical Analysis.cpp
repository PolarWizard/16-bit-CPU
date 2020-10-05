//Pass1 aka the Lexical Analysis

#include <iostream>
#include <cctype>
#include <string>
#include <map>
using namespace std;

#include "C:\Users\Dominik\source\repos\Assembler\Assembler\tokens.h"
#include "C:\Users\Dominik\source\repos\Assembler\Assembler\grabToken.h"
#include "C:\Users\Dominik\source\repos\Assembler\Assembler\Instructions.cpp"

static map<string, TokenType> OperatorMap = {
	{"HALT", HALT},
	{"ADD", ADD},
	{"SUB", SUB},
	{"AND", AND},
	{"XOR", XOR},
	{"NOT", NOT},
	{"JMP", JMP},
	{"CMP", CMP},
	{"MOV", MOV},
	{"ASL", ASL},
	{"ASR", ASR},
	{"LSL", LSL},
	{"LSR", LSR},
	{"LOAD", LOAD},
	{"SAVE", SAVE}
};

Token find_OperationType(string& lexeme, int& lineNumber) {
	TokenType type = OPERATOR;
	auto Operator = OperatorMap.find(lexeme);
	if (Operator != OperatorMap.end()) {
		type = Operator->second;
		return Token(type, lexeme, lineNumber);
	}
	else {
		return Token(INVALID_operator_nonexistant, lexeme, lineNumber);
	}
}

Token getNextToken(istream& myfile,int& lineNumber){
	//error flags
	int INV_operator_digit = 0,
		INV_register_digit = 0,
		INV_register_alpha = 0,
		INV_address_digit = 0,
		INV_address_alpha = 0;
	
	string hold;

	enum LexState {BEGIN, inREGISTER, inADDRESS, inOPERATOR, inLABEL} lexState = BEGIN;
	char ch;
	string lexeme;
	while (myfile.get(ch)) {
		switch (lexState) {
		//BEGIN
		case BEGIN:
			if (ch == '\n') {
				return Token(NL, "", lineNumber++);
			}
			if (isspace(ch)) {
				break;
			}
			lexeme = ch;
			if (isalpha(ch) && ch != 'R') {
				lexState = inOPERATOR;
			}
			else if (isalpha(ch) && ch == 'R') {
				lexState = inREGISTER;
			}
			else if(isdigit(ch)) {
				lexState = inADDRESS;
			}
			else {
				TokenType type = INVALID_symbol;
				if (ch == ',') {
					type = COMMA;
					return Token(type, lexeme, lineNumber);
				}
				else if (ch == '.') {
					lexState = inLABEL;
					break;
				}
				return Token(type, lexeme, lineNumber);
			}
			break;
		//Getting Register
		case inREGISTER:
			//correct
			if (isdigit(ch)) {
				lexeme += ch;
				hold = hold + ch;
			}
			//incorrect
			else if(isalpha(ch)) {
				lexeme += ch;
				INV_register_alpha = 1;
			}
			else {
				myfile.putback(ch);
				if (INV_register_alpha) {
					return Token(INVALID_register_alpha, lexeme, lineNumber);
				}
				else if (stoi(hold) > 7) {
					return Token(INVALID_register_digit, lexeme, lineNumber);
				}
				else {
					return Token(REGISTER, lexeme, lineNumber);
				}
			}
			break;
		//Getting Address
		case inADDRESS:
			//correct
			if (isdigit(ch)) {
				lexeme += ch;
			}
			//incorrect
			else if(isalpha(ch)) {
				lexeme += ch;
				INV_address_alpha = 1;
			}
			//reached a non digit/alpha char so we putback the char and return the Token
			else {
				myfile.putback(ch);
				if (stoi(lexeme) > 512) {
					return Token(INVALID_address_digit, lexeme, lineNumber);
				}
				else if (INV_address_alpha){
					return Token(INVALID_address_alpha, lexeme, lineNumber);
				}
				else {
				return Token(ADDRESS, lexeme, lineNumber);
				}
			}
			break;
		//Getting Operation
		case inOPERATOR:
			//correct
			if (isalpha(ch)) {
				lexeme += ch;
			}
			//incorrect
			else if (isdigit(ch)) {
				lexeme += ch;
			}
			//reached a non digit/alpha char so we putback the char and return the Token
			else {
				myfile.putback(ch);
				return find_OperationType(lexeme, lineNumber);
			}
			break;
		case inLABEL:
			if (isalpha(ch) || isdigit(ch)) {
				lexeme += ch;
			}
			else if (myfile.peek() == EOF) {
				return Token(LABEL, lexeme, lineNumber);
			}
			else {
				myfile.putback(ch);
				return Token(LABEL, lexeme, lineNumber--);
			}
			break;
		}
	}
	if (myfile.eof()) {
		return Token(DONE, lexeme, lineNumber);
	}
	return Token(INVALID, "some strange I/O error", lineNumber);
}
