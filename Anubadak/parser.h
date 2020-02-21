#pragma once

#include "ast.h"
#include "lexer.h"
#include "token.h"
#include <vector>

namespace parser
{
	class Parser
	{
	public:
		//parser ko main kura parser constructor ta lekhekai xaina ni
		Parser(lexer::Lexer* lex);
		void consumeToken();
		parser::ASTProgramNode* parse_program();
		parser::ASTStatementNode* parseStatement();
		parser::ASTDeclarationNode* parseDeclarationStatement();
		parser::TYPE parseType();
		

		//member functions to evaluate expressoion
		parser::ASTExprNode* parseExpression();
		parser::ASTExprNode* parseSimpleExpression();
		parser::ASTExprNode* parseExpressionTerm();
		parser::ASTExprNode* parseExpressionFactor();

		parser::ASTFunctionCallNode* parseFunctionCallExpr();
		

		//parse type and parameters
		std::vector<ASTExprNode*>* parseActualParameter();
		
	private:
		lexer::Lexer* _lex;
		lexer::Token _currentToken;
		lexer::Token _nextToken;
	};
}

