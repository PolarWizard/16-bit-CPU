#include <string>
#include <iostream>
#include <vector>
using namespace std;

#include "C:\Users\Dominik\source\repos\Assembler\Assembler\grabToken.h"

void HALT_instruction(unsigned& iteration, vector<Token>& TokenQueue);
void MATH_instruction(unsigned& iteration, vector<Token>& TokenQueue, TokenType type);
void PC_instruction(unsigned& iteration, vector<Token>& TokenQueue, TokenType type);
void MEM_instruction(unsigned& iteration, vector<Token>& TokenQueue);
void Instruction(unsigned& iteration, vector<Token>& TokenQueue);
void MOV_instruction(unsigned& iteration, vector<Token>& TokenQueue);

extern int errors = 0;
int errorFlag = 0;
string sgHold;
int igHold;


void Error(Token token, string errorMsg) {
	cout << "Error at line " << token.getLineNumber() + 1 << ": " << errorMsg << endl;
	errors += 1;
	errorFlag = 1;
}

void Program(vector<Token>& TokenQueue) {
	unsigned it = 0;
	Token token = TokenQueue[it];
	if (token.getTokenType() == NL) {
		Error(token, "program cannot start with NL");
		return;
	}
	else if (token.getTokenType() == DONE) {
		Error(token, "program empty");
		return;
	}
	while (it < TokenQueue.size()) {
		token = TokenQueue[it];
		if (token.getTokenType() == DONE) {
			Error(token, "missing HALT instruction to signify program termination");
			return;
		}
		Instruction(it, TokenQueue);
		if (errorFlag) {
			errorFlag = 0;
			token = TokenQueue[--it];
			while (token.getTokenType() != NL) {
				token = TokenQueue[it++];
			}
		}
	}
}

void Instruction(unsigned& iteration, vector<Token>& TokenQueue) {
	Token token = TokenQueue[iteration++];
	switch (token.getTokenType()) {
	case HALT:
		HALT_instruction(iteration, TokenQueue);
		break;
	case ADD:
		MATH_instruction(iteration, TokenQueue, ADD);
		break;
	case SUB:
		MATH_instruction(iteration, TokenQueue, SUB);
		break;
	case AND:
		MATH_instruction(iteration, TokenQueue, AND);
		break;
	case XOR:
		MATH_instruction(iteration, TokenQueue, XOR);
		break;
	case NOT:
		MATH_instruction(iteration, TokenQueue, NOT);
		break;
	case JMP:
		PC_instruction(iteration, TokenQueue, JMP);
		break;
	case CMP:
		PC_instruction(iteration, TokenQueue, CMP);
		break;
	case MOV:
		MOV_instruction(iteration, TokenQueue);
		break;
	case ASL:
		MATH_instruction(iteration, TokenQueue, ASL);
		break;
	case ASR:
		MATH_instruction(iteration, TokenQueue, ASR);
		break;
	case LSL:
		MATH_instruction(iteration, TokenQueue, LSL);
		break;
	case LSR:
		MATH_instruction(iteration, TokenQueue, LSR);
		break;
	case LOAD:
		MEM_instruction(iteration, TokenQueue);
		break;
	case SAVE:
		MEM_instruction(iteration, TokenQueue);
		break;
	}
}

void HALT_instruction(unsigned& iteration, vector<Token>& TokenQueue) {
	Token token = TokenQueue[iteration++];
	if (token.getTokenType() == DONE) {
		Error(token, "missing NL");
		return;
	}
	else if (token.getTokenType() != NL) {
		Error(token, "unexpected expression after HALT");
		return;
	}
	token = TokenQueue[iteration++];
	if (token.getTokenType() != DONE) {
		Error(token, "unexpected instruction after HALT");
		return;
	}
}

void MATH_instruction(unsigned& iteration, vector<Token>& TokenQueue, TokenType type) {
	Token token = TokenQueue[iteration++];
	switch (type) {
	case ADD:
		sgHold = token.getLexeme();
		igHold = (int)sgHold[1] - '0';
		if (igHold > 3) {
			Error(token, "REGISTER parameter exceeding max value of R3");
			return;
		}
		if (token.getTokenType() != REGISTER) {
			Error(token, "expecting REGISTER parameter");
			return;
		}
		token = TokenQueue[iteration++];
		if (token.getTokenType() != COMMA) {
			Error(token, "expecting COMMA parameter after REGISTER parameter");
			return;
		}

		token = TokenQueue[iteration++];
		if (token.getTokenType() != REGISTER) {
			Error(token, "expecting REGISTER parameter after COMMA parameter");
			return;
		}
		token = TokenQueue[iteration++];
		if (token.getTokenType() != NL) {
			Error(token, "missing NL");
			return;
		}
		break;
	case SUB:
		sgHold = token.getLexeme();
		igHold = (int)sgHold[1] - '0';
		if (igHold > 3) {
			Error(token, "REGISTER parameter exceeding max value of R3");
			return;
		}
		if (token.getTokenType() != REGISTER) {
			Error(token, "expecting REGISTER parameter");
			return;
		}
		token = TokenQueue[iteration++];
		if (token.getTokenType() != COMMA) {
			Error(token, "expecting COMMA parameter after REGISTER parameter");
			return;
		}
		token = TokenQueue[iteration++];
		if (token.getTokenType() != REGISTER) {
			Error(token, "expecting REGISTER parameter");
			return;
		}
		token = TokenQueue[iteration++];
		if (token.getTokenType() != NL) {
			Error(token, "missing NL");
			return;
		}
		break;
	case AND:
		sgHold = token.getLexeme();
		igHold = (int)sgHold[1] - '0';
		if (igHold > 3) {
			Error(token, "REGISTER parameter exceeding max value of R3");
			return;
		}
		if (token.getTokenType() != REGISTER) {
			Error(token, "expecting REGISTER parameter");
			return;
		}
		token = TokenQueue[iteration++];
		if (token.getTokenType() != COMMA) {
			Error(token, "expecting COMMA parameter after REGISTER parameter");
			return;
		}
		token = TokenQueue[iteration++];
		if (token.getTokenType() != REGISTER) {
			Error(token, "expecting REGISTER parameter");
			return;
		}
		token = TokenQueue[iteration++];
		if (token.getTokenType() != NL) {
			Error(token, "missing NL");
			return;
		}
		break;
	case XOR:
		sgHold = token.getLexeme();
		igHold = (int)sgHold[1] - '0';
		if (igHold > 3) {
			Error(token, "REGISTER parameter exceeding max value of R3");
			return;
		}
		if (token.getTokenType() != REGISTER) {
			Error(token, "expecting REGISTER parameter");
			return;
		}
		token = TokenQueue[iteration++];
		if (token.getTokenType() != COMMA) {
			Error(token, "expecting COMMA parameter after REGISTER parameter");
			return;
		}
		token = TokenQueue[iteration++];
		if (token.getTokenType() != REGISTER) {
			Error(token, "expecting REGISTER parameter");
			return;
		}
		token = TokenQueue[iteration++];
		if (token.getTokenType() != NL) {
			Error(token, "missing NL");
			return;
		}
		break;
	case NOT:
		sgHold = token.getLexeme();
		igHold = (int)sgHold[1] - '0';
		if (igHold > 3) {
			Error(token, "REGISTER parameter exceeding max value of R3");
			return;
		}
		if (token.getTokenType() != REGISTER) {
			Error(token, "expecting REGISTER parameter");
			return;
		}
		token = TokenQueue[iteration++];
		if (token.getTokenType() != NL) {
			Error(token, "missing NL");
			return;
		}
		break;
	case ASL:
		sgHold = token.getLexeme();
		igHold = (int)sgHold[1] - '0';
		if (igHold > 3) {
			Error(token, "REGISTER parameter exceeding max value of R3");
			return;
		}
		if (token.getTokenType() != REGISTER) {
			Error(token, "expecting REGISTER parameter");
			return;
		}
		token = TokenQueue[iteration++];
		if (token.getTokenType() != NL) {
			Error(token, "missing NL");
			return;
		}
		break;
	case ASR:
		sgHold = token.getLexeme();
		igHold = (int)sgHold[1] - '0';
		if (igHold > 3) {
			Error(token, "REGISTER parameter exceeding max value of R3");
			return;
		}
		if (token.getTokenType() != REGISTER) {
			Error(token, "expecting REGISTER parameter");
			return;
		}
		token = TokenQueue[iteration++];
		if (token.getTokenType() != NL) {
			Error(token, "missing NL");
			return;
		}
		break;
	case LSL:
		sgHold = token.getLexeme();
		igHold = (int)sgHold[1] - '0';
		if (igHold > 3) {
			Error(token, "REGISTER parameter exceeding max value of R3");
			return;
		}
		if (token.getTokenType() != REGISTER) {
			Error(token, "expecting REGISTER parameter");
			return;
		}
		token = TokenQueue[iteration++];
		if (token.getTokenType() != NL) {
			Error(token, "missing NL");
			return;
		}
		break;
	case LSR:
		sgHold = token.getLexeme();
		igHold = (int)sgHold[1] - '0';
		if (igHold > 3) {
			Error(token, "REGISTER parameter exceeding max value of R3");
			return;
		}
		if (token.getTokenType() != REGISTER) {
			Error(token, "expecting REGISTER parameter");
			return;
		}
		token = TokenQueue[iteration++];
		if (token.getTokenType() != NL) {
			Error(token, "missing NL");
			return;
		}
		break;
	}
}

void PC_instruction(unsigned& iteration, vector<Token>& TokenQueue, TokenType type) {
	Token token = TokenQueue[iteration++];
	switch (type) {
	case JMP:
		if (token.getTokenType() != ADDRESS) {
			Error(token, "expecting ADDRESS parameter");
			return;
		}
		token = TokenQueue[iteration++];
		if (token.getTokenType() != NL) {
			Error(token, "missing NL");
			return;
		}
		break;
	case CMP:
		if (token.getTokenType() != REGISTER) {
			Error(token, "expecting REGISTER parameter");
			return;
		}
		token = TokenQueue[iteration++];
		if (token.getTokenType() != COMMA) {
			Error(token, "expecting COMMA parameter after REGISTER parameter");
			return;
		}
		token = TokenQueue[iteration++];
		if (token.getTokenType() != ADDRESS) {
			Error(token, "expecting ADDRESS parameter");
			return;
		}
		token = TokenQueue[iteration++];
		if (token.getTokenType() != NL) {
			Error(token, "missing NL");
			return;
		}
		break;
	}
}

void MOV_instruction(unsigned& iteration, vector<Token>& TokenQueue) {
	Token token = TokenQueue[iteration++];
	if (token.getTokenType() != REGISTER) {
		Error(token, "expecting REGISTER parameter");
		return;
	}
	token = TokenQueue[iteration++];
	if (token.getTokenType() != NL) {
		Error(token, "missing NL");
		return;
	}
}

void MEM_instruction(unsigned& iteration, vector<Token>& TokenQueue) {
	Token token = TokenQueue[iteration++];
	if (token.getTokenType() != REGISTER) {
		Error(token, "expecting REGISTER parameter");
		return;
	}
	token = TokenQueue[iteration++];
	if (token.getTokenType() != COMMA) {
		Error(token, "expecting COMMA parameter after REGISTER parameter");
		return;
	}
	token = TokenQueue[iteration++];
	if (token.getTokenType() != ADDRESS) {
		Error(token, "expecting ADDRESS parameter");
		return;
	}
	token = TokenQueue[iteration++];
	if (token.getTokenType() != NL) {
		Error(token, "missing NL");
		return;
	}
}
