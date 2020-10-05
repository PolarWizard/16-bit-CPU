// Assembler.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <vector>
using namespace std;

#include "C:\Users\Dominik\source\repos\Assembler\Assembler\grabToken.h"
#include "C:\Users\Dominik\source\repos\Assembler\ConsoleApplication1\MachineCode.cpp"

int main()
{
	int pass1_Errors = 0;
	Token token;
	vector<Token> TokenQueue;
	int lineNumber = 0;
	ifstream myfile("C:/Users/Dominik/Desktop/16 bit CPU/GladiusProgram.txt");
	istream* in = &myfile;
	if (!myfile.is_open()) {
		cout << "Cant find file/Cant open file";
		return 0;
	}
	while (in) {
		token = grabToken::grab(*in, lineNumber);
		TokenQueue.push_back(token);
		if (in->eof()) {
			break;
		}
		if (token.getTokenType() == INVALID) {
			cout << "Error on line: " << token.getLineNumber() + 1 << " (" << token.getLexeme() << ")" << endl;
			cout << "Reason for Error: " << "some strange I/O error" << endl << endl;
			pass1_Errors += 1;
		}
		else if (token.getTokenType() == INVALID_symbol) {
			cout << "Error on line: " << token.getLineNumber() + 1 << " (" << token.getLexeme() << ")" << endl;
			cout << "Reason for Error: " << "Symbol does not exist" << endl << endl;
			pass1_Errors += 1;
		}
		else if (token.getTokenType() == INVALID_operator_nonexistant) {
			cout << "Error on line: " << token.getLineNumber() + 1 << " (" << token.getLexeme() << ")" << endl;
			cout << "Reason for Error: " << "Operator does not exist" << endl << endl;
			pass1_Errors += 1;
		}
		else if (token.getTokenType() == INVALID_register_digit) {
			cout << "Error on line: " << token.getLineNumber() + 1 << " (" << token.getLexeme() << ")" << endl;
			cout << "Reason for Error: " << "R followed by digit exceeds 7" << endl << endl;
			pass1_Errors += 1;
		}
		else if (token.getTokenType() == INVALID_register_alpha) {
			cout << "Error on line: " << token.getLineNumber() + 1 << " (" << token.getLexeme() << ")" << endl;
			cout << "Reason for Error: " << "R is followed by another alphabetic character" << endl << endl;
			pass1_Errors += 1;
		}
		else if (token.getTokenType() == INVALID_address_digit) {
			cout << "Error on line: " << token.getLineNumber() + 1 << " (" << token.getLexeme() << ")" << endl;
			cout << "Reason for Error: " << "Address value exceeds 511" << endl << endl;
			pass1_Errors += 1;
		}
		else if (token.getTokenType() == INVALID_address_alpha) {
			cout << "Error on line: " << token.getLineNumber() + 1 << " (" << token.getLexeme() << ")" << endl;
			cout << "Reason for Error: " << "Address value contains an alphabetic character" << endl << endl;
			pass1_Errors += 1;
		}
	}
	if (pass1_Errors > 0) {
		return 0;
	}
	cout << "Pass 1 Completed Successfully!" << endl;
	Program(TokenQueue);
	if (errors) {
		return 0;
	}
	cout << "Pass 2 Completed Successfully!" << endl;
	MachineCodeGen(TokenQueue);
	myfile.close();
	return 0;
}
