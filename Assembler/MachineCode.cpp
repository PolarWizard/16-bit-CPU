#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;

#include "C:\Users\Dominik\source\repos\Assembler\Assembler\tokens.h"

static map<TokenType, string> InstCode = {
	{HALT, "1111"},
	{ADD, "0001"},
	{SUB, "0010"},
	{AND, "0011"},
	{XOR, "0100"},
	{NOT, "0101"},
	{JMP, "0110"},
	{CMP, "0111"},
	{MOV, "1000"},
	{ASL, "1001"},
	{ASR, "1010"},
	{LSL, "1011"},
	{LSR, "1100"},
	{LOAD, "1101"},
	{SAVE, "1110"}
};

static map<string, string> RegCode = {
	{"R0", "000"},
	{"R1", "001"},
	{"R2", "010"},
	{"R3", "011"},
	{"R4", "100"},
	{"R5", "101"},
	{"R6", "110"},
	{"R7", "111"}
};

string MachineCode;

string den2bin(string addr) {
	int i_addr = stoi(addr);
	string str_remainder, bin;
	int i = 0, remainder;
	while (i_addr != 0)
	{
		remainder = i_addr % 2;
		i_addr /= 2;
		str_remainder = to_string(remainder);
		bin += str_remainder;
		++i;
	}
	switch (bin.size()) {
	case 0:
		bin = "000000000" + bin;
		break;
	case 1:
		bin = "00000000" + bin;
		break;
	case 2:
		bin = "0000000" + bin;
		break;
	case 3:
		bin = "000000" + bin;
		break;
	case 4:
		bin = "00000" + bin;
		break;
	case 5:
		bin = "0000" + bin;
		break;
	case 6:
		bin = "000" + bin;
		break;
	case 7:
		bin = "00" + bin;
		break;
	case 8:
		bin = "0" + bin;
		break;
	}
	return bin;
}

void MachineCodeGen(vector<Token>& TokenQueue) {
	ofstream ml;
	ml.open("Machine Langauage.txt");
	string op, reg, addr;
	unsigned it = 0;
	Token token = TokenQueue[it];
	while (it < TokenQueue.size()) {
		Token token = TokenQueue[it++];
		cout << token.getLexeme() << endl;
		if (token.getTokenType() == HALT) {
			auto Operator = InstCode.find(token.getTokenType());
			op = Operator->second;
			MachineCode = op + "000000000000";
			cout << MachineCode << endl;
			ml << token.getLineNumber() << " - " << MachineCode << endl;
		}
		else if (token.getTokenType() == ADD) {
			auto Operator = InstCode.find(token.getTokenType());
			op = Operator->second;
			MachineCode = op;
			token = TokenQueue[it++];
			auto Register = RegCode.find(token.getLexeme());
			reg = Register->second;
			MachineCode += reg;
			++it;
			token = TokenQueue[it++];
			Register = RegCode.find(token.getLexeme());
			reg = Register->second;
			MachineCode += reg + "000000";
			cout << MachineCode << endl;
			ml << token.getLineNumber() << " - " << MachineCode << endl;
		}
		else if (token.getTokenType() == SUB) {
			auto Operator = InstCode.find(token.getTokenType());
			op = Operator->second;
			MachineCode = op;
			token = TokenQueue[it++];
			auto Register = RegCode.find(token.getLexeme());
			reg = Register->second;
			MachineCode += reg;
			++it;
			token = TokenQueue[it++];
			Register = RegCode.find(token.getLexeme());
			reg = Register->second;
			MachineCode += reg + "000000";
			cout << MachineCode << endl;
			ml << token.getLineNumber() << " - " << MachineCode << endl;
		}
		else if (token.getTokenType() == AND) {
			auto Operator = InstCode.find(token.getTokenType());
			op = Operator->second;
			MachineCode = op;
			token = TokenQueue[it++];
			auto Register = RegCode.find(token.getLexeme());
			reg = Register->second;
			MachineCode += reg;
			++it;
			token = TokenQueue[it++];
			Register = RegCode.find(token.getLexeme());
			reg = Register->second;
			MachineCode += reg + "000000";
			cout << MachineCode << endl;
			ml << token.getLineNumber() << " - " << MachineCode << endl;
		}
		else if (token.getTokenType() == XOR) {
			auto Operator = InstCode.find(token.getTokenType());
			op = Operator->second;
			MachineCode = op;
			token = TokenQueue[it++];
			auto Register = RegCode.find(token.getLexeme());
			reg = Register->second;
			MachineCode += reg;
			++it;
			token = TokenQueue[it++];
			Register = RegCode.find(token.getLexeme());
			reg = Register->second;
			MachineCode += reg + "000000";
			cout << MachineCode << endl;
			ml << token.getLineNumber() << " - " << MachineCode << endl;
		}
		else if (token.getTokenType() == NOT) {
			auto Operator = InstCode.find(token.getTokenType());
			op = Operator->second;
			MachineCode = op;
			token = TokenQueue[it++];
			auto Register = RegCode.find(token.getLexeme());
			reg = Register->second;
			MachineCode += reg + "000000000";
			cout << MachineCode << endl;
			ml << token.getLineNumber() << " - " << MachineCode << endl;
		}
		else if (token.getTokenType() == JMP) {
			auto Operator = InstCode.find(token.getTokenType());
			op = Operator->second;
			MachineCode = op + "000";
			token = TokenQueue[it++];
			string addr = den2bin(token.getLexeme());
			MachineCode += addr;
			cout << MachineCode << endl;
			ml << token.getLineNumber() << " - " << MachineCode << endl;
		}
		else if (token.getTokenType() == CMP) {
			auto Operator = InstCode.find(token.getTokenType());
			op = Operator->second;
			MachineCode = op;
			token = TokenQueue[it++];
			auto Register = RegCode.find(token.getLexeme());
			reg = Register->second;
			MachineCode += reg;
			++it;
			token = TokenQueue[it++];
			string addr = den2bin(token.getLexeme());
			MachineCode += addr;
			cout << MachineCode << endl;
			ml << token.getLineNumber() << " - " << MachineCode << endl;
		}
		else if (token.getTokenType() == MOV) {
			auto Operator = InstCode.find(token.getTokenType());
			op = Operator->second;
			MachineCode = op;
			token = TokenQueue[it++];
			auto Register = RegCode.find(token.getLexeme());
			reg = Register->second;
			MachineCode += reg + "000000000";
			cout << MachineCode << endl;
			ml << token.getLineNumber() << " - " << MachineCode << endl;
		}
		else if (token.getTokenType() == ASL) {
			auto Operator = InstCode.find(token.getTokenType());
			op = Operator->second;
			MachineCode = op;
			token = TokenQueue[it++];
			auto Register = RegCode.find(token.getLexeme());
			reg = Register->second;
			MachineCode += reg + "000000000";
			cout << MachineCode << endl;
			ml << token.getLineNumber() << " - " << MachineCode << endl;
		}
		else if (token.getTokenType() == ASR) {
			auto Operator = InstCode.find(token.getTokenType());
			op = Operator->second;
			MachineCode = op;
			token = TokenQueue[it++];
			auto Register = RegCode.find(token.getLexeme());
			reg = Register->second;
			MachineCode += reg + "000000000";
			cout << MachineCode << endl;
			ml << token.getLineNumber() << " - " << MachineCode << endl;
		}
		else if (token.getTokenType() == LSL) {
			auto Operator = InstCode.find(token.getTokenType());
			op = Operator->second;
			MachineCode = op;
			token = TokenQueue[it++];
			auto Register = RegCode.find(token.getLexeme());
			reg = Register->second;
			MachineCode += reg + "000000000";
			cout << MachineCode << endl;
			ml << token.getLineNumber() << " - " << MachineCode << endl;
		}
		else if (token.getTokenType() == LSR) {
			auto Operator = InstCode.find(token.getTokenType());
			op = Operator->second;
			MachineCode = op;
			token = TokenQueue[it++];
			auto Register = RegCode.find(token.getLexeme());
			reg = Register->second;
			MachineCode += reg + "000000000";
			cout << MachineCode << endl;
			ml << token.getLineNumber() << " - " << MachineCode << endl;
		}
		else if (token.getTokenType() == LOAD) {
			auto Operator = InstCode.find(token.getTokenType());
			op = Operator->second;
			MachineCode = op;
			token = TokenQueue[it++];
			auto Register = RegCode.find(token.getLexeme());
			reg = Register->second;
			MachineCode += reg;
			++it;
			token = TokenQueue[it++];
			string addr = den2bin(token.getLexeme());
			MachineCode += addr;
			cout << MachineCode << endl;
			ml << token.getLineNumber() << " - " << MachineCode << endl;
		}
		else if (token.getTokenType() == SAVE) {
			auto Operator = InstCode.find(token.getTokenType());
			op = Operator->second;
			MachineCode = op;
			token = TokenQueue[it++];
			auto Register = RegCode.find(token.getLexeme());
			reg = Register->second;
			MachineCode += reg;
			++it;
			token = TokenQueue[it++];
			string addr = den2bin(token.getLexeme());
			MachineCode += addr;
			cout << MachineCode << endl;
			ml << token.getLineNumber() << " - " << MachineCode << endl;
		}
		++it;
	}
	ml.close();
}