#pragma once
#include <iostream>
#include <exception>
#include <string>


#include"parser.h"
#include "lexer.h"

using namespace parser;
using namespace lexer;

namespace parser
{
	Parser::Parser(lexer::Lexer* lex) :_lex(lex)
	{
		_currentToken = lex->nextToken();
		_nextToken = lex->nextToken();
	}

	///
	void Parser::consumeToken()
	{
		_currentToken = _nextToken;
		_nextToken = _lex->nextToken();
	}
	ASTProgramNode* Parser::parse_program() {
		auto statements = new::std::vector<ASTNode*>;
		while (_currentToken.type != TOKEN::TOK_EOF)
		{
			statements->push_back(parseStatement());
			consumeToken();
		}
		//rememnber that astprogramnode constructor uses std::move() to the statements argument
		return new parser::ASTProgramNode(*statements);
	}
	ASTStatementNode* Parser::parseStatement() {
		if (_currentToken.type == TOKEN::TOK_VAR)
		{

			return parseDeclarationStatement();
		}
		else
			std::cout << "error in the astStatementNode" << std::endl;
	}
	ASTDeclarationNode* Parser::parseDeclarationStatement()
	{
		TYPE type;
		std::string identifier;
		ASTExprNode* expr;
		int lineNumber;

		consumeToken();
		lineNumber = _currentToken.getLineNumber();

		if (_currentToken.getType() != static_cast<int>(TOKEN::TOK_IDENTIFIER)) {
			throw std::runtime_error("Expected variable name after 'var' on line "
				+ std::to_string(_currentToken.getLineNumber()) + ".");
		}

		consumeToken();
		if (_currentToken.type != TOKEN::TOK_COLON)
		{
			throw std::runtime_error("expected colon ':' after identifier  in line "
				+ std::to_string(_currentToken.getLineNumber()));
		}

		consumeToken();

		// in future identifier will be passed into this function
		type = parseType();

		consumeToken();
		if (_currentToken.type != TOKEN::TOK_EQUALS) {
			throw std::runtime_error("expected '=' after  in line "
				+ std::to_string(_currentToken.getLineNumber()));
		}

		
		expr = parseExpression();
		//checkPurpose
		std::cout << "curretn token=" << _currentToken.getVal() << " type= "<<_currentToken.getType() << std::endl;
		if (_currentToken.type != TOKEN::TOK_SEMICOLON)
		consumeToken();	
		//checkPurpose
		std::cout << "curretn token="<<_currentToken.getVal() << " type= "<< _currentToken.getType() << std::endl;
		if (_currentToken.type != TOKEN::TOK_SEMICOLON)
		{
			throw std::runtime_error("expected ';'   in line "
				+ std::to_string(_currentToken.getLineNumber()));
		}

		std::cout << "sucessfully declared variable " << identifier << std::endl;



		return new ASTDeclarationNode(type, identifier, lineNumber, expr);

	}
	// in future this function will take string i e identifier from calling place
	TYPE Parser::parseType()
	{
		switch (_currentToken.type)
		{
		case TOKEN::TOK_INT:
			return TYPE::INT;
		case TOKEN::TOK_STRING_TYPE:
			return TYPE::STRING;
		case TOKEN::TOK_REAL:
			return TYPE::REAL;
		case TOKEN::TOK_BOOL:
			return TYPE::BOOL;


		}
	}

	ASTExprNode*  Parser::parseExpression() {
		ASTExprNode* simpleExpression = parseSimpleExpression();
		int lineNumber = _currentToken.getLineNumber();

		if (_nextToken.type == TOKEN::TOK_RELATIONAL_OP) {
			consumeToken();
			return new ASTBinaryExprNode(_currentToken.getVal(), simpleExpression, parseExpression(), lineNumber);
		}
		return simpleExpression;



	}
	ASTExprNode* Parser::parseSimpleExpression() {
		ASTExprNode* term = parseExpressionTerm();
		
		int lineNumber = _currentToken.getLineNumber();

		if (_nextToken.type == TOKEN::TOK_ADDITIVE_OP) {
			consumeToken();
			return new ASTBinaryExprNode(_currentToken.getVal(), term, parseSimpleExpression(), lineNumber);
		}
		return term;
		

	}
	ASTExprNode* Parser::parseExpressionTerm() {
		ASTExprNode* factor = parseExpressionFactor();
		int lineNumber = _currentToken.getLineNumber();

		if (_nextToken.type == TOKEN::TOK_MULTIPLICATIVE_OP) {
			consumeToken();
			return new ASTBinaryExprNode(_currentToken.getVal(), factor, parseExpressionTerm(), lineNumber);
		}
		return factor;
		

	}
	ASTExprNode* Parser::parseExpressionFactor() {
		consumeToken();
		int lineNumber = _currentToken.getLineNumber();
		
		switch (_currentToken.type)
		{
		case TOKEN::TOK_INT:
			return new ASTLiteralNode<int>(std::stoi(_currentToken.getVal()), lineNumber);

		case TOKEN::TOK_REAL:
			return new ASTLiteralNode<float>(std::stof(_currentToken.getVal()), lineNumber);

		case TOKEN::TOK_BOOL:
			return new ASTLiteralNode<bool>(_currentToken.getVal()=="true", lineNumber);

		case TOKEN::TOK_STRING:
		{
			//removes two "  from begining and end
			std::string str = _currentToken.getVal().substr(1, _currentToken.getVal().size() - 2);
			//TODO: string checking for varipus specia; characters is left for  now
			return new ASTLiteralNode<std::string>(_currentToken.getVal(), lineNumber);
		}


		case TOKEN::TOK_IDENTIFIER: {
			if (_nextToken.type == TOKEN::TOK_LEFT_BRACKET) {
				return parseFunctionCallExpr();
			}
			else
				return new ASTIdentifierNode(_currentToken.getVal(), _currentToken.getLineNumber());
		}

		case TOKEN::TOK_ADDITIVE_OP:
		case TOKEN::TOK_NOT:
			return new ASTUnaryExprNode(_currentToken.getVal(), parseExpression(), _currentToken.getLineNumber());

		case TOKEN::TOK_LEFT_BRACKET: {
			ASTExprNode* subExpr = parseExpression();
			consumeToken();
	
			if(_currentToken.type!=TOKEN::TOK_RIGHT_BRACKET)
				throw std::runtime_error("Expected ')' on line "
					+ std::to_string(_currentToken.getLineNumber()) + ".");
			return subExpr;
		}
								
		}
	}
	
	ASTFunctionCallNode* Parser::parseFunctionCallExpr()
	{
		std::string identifier = _currentToken.getVal();
		int lineNumber = _currentToken.getLineNumber();
		auto parameters = new std::vector<ASTExprNode*>;

		consumeToken();
		//checkPurpose
		//std::cout << "curretn token =" << _currentToken.getVal()<<std::endl;
		if (_currentToken.type != TOKEN::TOK_LEFT_BRACKET)
		{
			throw std::runtime_error("Expected 'a(' on line "
				+ std::to_string(_currentToken.getLineNumber()) + ".");
		}
		if (_nextToken.type != TOKEN::TOK_RIGHT_BRACKET)
		{
			parameters = parseActualParameter();
		}
		else {
			//consumes ')'
			consumeToken();
		}
			
		//checkPurpose
		std::cout << "curretn token =" << _currentToken.getVal()<<std::endl;
		
		if (_currentToken.type != TOKEN::TOK_RIGHT_BRACKET) {
			throw std::runtime_error("Expected ')' on line "
				+ std::to_string(_currentToken.getLineNumber()) + ".");
		}

		return new ASTFunctionCallNode(identifier, *parameters, lineNumber);

	}
	std::vector<ASTExprNode*>* Parser::parseActualParameter() {
		//checkPurpose
		//std::cout << "check>>>>>>>>>>>>>>>>>" << std::endl;
		auto parameters = new std::vector<ASTExprNode*>;
		
		//this pushes first token then checks for comma token we also could have used do while loop instead
		parameters->push_back(parseExpression());
		
		//if there are more parameters than one
		consumeToken();
		while (_currentToken.type == TOKEN::TOK_COMMA)
		{
			parameters->push_back(parseExpression());
			consumeToken();
		}
		return parameters;
	}
		
}
