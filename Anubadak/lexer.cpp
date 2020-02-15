#include <stack>
#include "lexer.h"

using namespace lexer;

Lexer::Lexer(std::string& program)
{
	int currentIndex = 0;
	Token tempTok;
	while (currentIndex < program.length())
	{
		tempTok = generateToken(program, currentIndex);
		tokens.push_back(tempTok);

	}
}

Token Lexer::nextToken()
{
		return tokens[currentToken++];

}
Token Lexer::generateToken(std::string& program, int& currentIndex)
{
	while (program[currentIndex] == ' ')
		currentIndex++;

	char currentSymbol = program[currentIndex];
	int currentState = 0;
	std::string lexeme;
	int finalState;

	while (currentState != e)
	{
		finalState = currentState;
		lexeme += currentSymbol;
		currentIndex++;
		currentSymbol = program[currentIndex];
		currentState = transitionFunction(currentState, currentSymbol);
	}
	return Token(finalState, lexeme, getLineNumber(program, currentIndex));
	
}

int Lexer::transitionFunction(int currentState, char symbol)
{
	switch (symbol)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return transitions[static_cast <int >(TRANSITION_TYPE::DIGIT)][currentState];

	case '.':
		return transitions[static_cast <int>(TRANSITION_TYPE::PERIOD)][currentState];

	case '+':
	case '-':
		return transitions[static_cast <int>(TRANSITION_TYPE::ADDITIVE_OP)][currentState];

	case '*':
		return transitions[static_cast <int>(TRANSITION_TYPE::ASTERISK)][currentState];

	case '!':
		return transitions[static_cast <int>(TRANSITION_TYPE::EXCL_MARK)][currentState];

	case '>':
	case '<':
		return transitions[static_cast <int>(TRANSITION_TYPE::ORDER_REL)][currentState];

	case '=':
		return transitions[static_cast <int>(TRANSITION_TYPE::EQUALS)][currentState];
	case '_':
		return transitions[static_cast <int>(TRANSITION_TYPE::UNDERSCORE)][currentState];
	case '/':
		return transitions[static_cast <int>(TRANSITION_TYPE::EQUALS)][currentState];
	case '\\':
		return transitions[static_cast <int>(TRANSITION_TYPE::EQUALS)][currentState];
	case '\"':
		return transitions[static_cast <int>(TRANSITION_TYPE::EQUALS)][currentState];

	case ':':
	case ';':
	case ',':
	case '(':
	case ')':
	case '{':
	case '}':
		return transitions[static_cast <int>(TRANSITION_TYPE::PUNCTUATION)][currentState];

	case '\n':
		return transitions[static_cast <int>(TRANSITION_TYPE::NEWLINE)][currentState];
	case EOF:
		return transitions[static_cast <int>(TRANSITION_TYPE::ENDOFFILE)][currentState];

	default:
		auto ascii = (int)symbol;

		// If alpha is in [A-Z] or [a-z]
		if (((0x41 <= ascii) && (ascii <= 0x5A)) ||
			((0x61 <= ascii) && (ascii <= 0x7A)))
			return transitions[static_cast <int>(TRANSITION_TYPE::LETTER)][currentState];

		// Else if Printable
		if ((0x20 <= ascii) && (ascii <= 0x7E))
			return transitions[static_cast <int>(TRANSITION_TYPE::PRINTABLE)][currentState];

		// If other
		return transitions[static_cast <int>(TRANSITION_TYPE::OTHER)][currentState];


	/*default:
		auto ascii = (int)symbol;
		if ((ascii >= 0x61) && (ascii <= 0x7A))
			return transitions[static_cast <int>(TRANSITION_TYPE::LETTER)][currentState];
		else
			return transitions[static_cast <int>(TRANSITION_TYPE::OTHER)][currentState];
			*/
	
	}
}

int Lexer::getLineNumber(std::string & program,int currentIndex)
{
	int lineNumber = 0;
	for (int i= 0; i < currentIndex;i++)
	{
		if (program[i] == '\n')
			lineNumber++;
	}
	return lineNumber;

}





