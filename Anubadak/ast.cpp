#include <iostream>
#include "ast.h"
using namespace parser;

//i think std::move is used to invoke move constructor 
ASTProgramNode::ASTProgramNode(std::vector<ASTNode*>statements)
	:_statements(std::move(statements)){}

ASTDeclarationNode::ASTDeclarationNode(TYPE type, std::string identifier, 
	int lineNumber, ASTExprNode* expression)
		: _type(type),_identifier(identifier),_lineNumber(lineNumber),_expression(std::move(expression))

{

}
ASTIdentifierNode::ASTIdentifierNode(std::string identifier, int lineNumber):_identifier(identifier),
		_lineNumber(lineNumber){}

ASTFunctionCallNode::ASTFunctionCallNode(std::string identifier, std::vector<ASTExprNode*>parameters,
	int lineNumber):_identifier(identifier),_parameters(std::move(parameters)) {}

ASTBinaryExprNode::ASTBinaryExprNode(std::string optor, ASTExprNode* expr1, ASTExprNode* expr2, int lineNumber)
	:_optor(std::move(optor)),_expr1(expr1), _expr2(expr2), _lineNumber(lineNumber) {}

ASTUnaryExprNode::ASTUnaryExprNode(std::string optor, ASTExprNode* expr, int lineNumber)
	: _optor(std::move(optor)), _expr(expr), _lineNumber(lineNumber) {}
