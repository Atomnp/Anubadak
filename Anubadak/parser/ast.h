#pragma once
#include <iostream>
#include <vector>

//abstract nodes which cannot be instantiaated
namespace parser
{
	enum class TYPE
	{
		INT,
		REAL,
		BOOL,
		STRING
	};

	//abstract nodes
	class ASTNode
	{
	};

	class ASTExprNode :public ASTNode
	{
	};
	class ASTStatementNode : public ASTNode
	{

	};

	//statement Nodes
	class ASTProgramNode :public ASTStatementNode
	{
	public:
		std::vector<ASTNode*> _statements;
		ASTProgramNode(std::vector<ASTNode*>statements);
	};


	class ASTDeclarationNode :public ASTStatementNode
	{
	public:
		TYPE _type;
		std::string _identifier;
		int _lineNumber;
		ASTExprNode* _expression;

		ASTDeclarationNode(TYPE type, std::string identifier, int lineNumber, ASTExprNode* expression);

	};


	class ASTAssignmentNode :public ASTStatementNode
	{
	private:
		std::string _identifier;
		int _lineNumber;
		ASTExprNode* _expression;
	public:
		ASTAssignmentNode(std::string identifier, int lineNumber, ASTExprNode* expression);
	};


	class ASTPrintNode :public ASTStatementNode
	{
	private:
		int _lineNumber;
		ASTExprNode* _expression;

	public:
		ASTPrintNode(int lineNumber, ASTExprNode* expression);
	};


	class ASTReturnNode :public ASTStatementNode
	{
		int _lineNumber;
		ASTExprNode* _expr;
	public:
		ASTReturnNode(ASTExprNode * expression, int lineNumber);
	};


	class ASTBlockNode :public ASTStatementNode
	{
		std::vector<ASTStatementNode*> _statements;
		int _lineNumber;
	public:
		ASTBlockNode(std::vector<ASTStatementNode*> statements, int lineNumber);
	};


	class ASTIfNode :public ASTStatementNode
	{
		int _lineNumber;
		ASTExprNode* _condition;
		ASTBlockNode* _ifBlock;
		ASTBlockNode* _elseBlock;
	public:
		ASTIfNode(ASTExprNode *condition, ASTBlockNode * ifBlock , 
			int lineNumber, ASTBlockNode* elseBlock=nullptr);
	};
	class ASTWhileNode :public ASTStatementNode
	{
		int _lineNumber;
		ASTExprNode* _condition;
		ASTBlockNode* _whileBlock;
	public:
		ASTWhileNode(ASTExprNode * condition, ASTBlockNode* ifBlock,
			int lineNumber);
	};
	class ASTFunctionDefinitionNode :public ASTStatementNode
	{
		int _lineNumber;
		std::string _funcName;
		std::vector < std:: pair<std::string, TYPE >> _parameters;
		std::vector <TYPE>_signature;
		std::vector <std::string>_variableNames;

		ASTBlockNode* _funcDefBlock;
		TYPE _returnType;

	public:
		ASTFunctionDefinitionNode(std::string,std::vector<std::pair<std::string,TYPE>>,TYPE,
			ASTBlockNode *funcDefBlock,int lineNumber);
	};

	template <typename T>
	class ASTLiteralNode:public ASTExprNode
	{
	public:
		ASTLiteralNode(T value, int lineNumber) :_value(value), _lineNumber(lineNumber){}
		T _value;
		int _lineNumber;
	};
	
	class ASTIdentifierNode :public ASTExprNode {
		std::string _identifier;
		int _lineNumber;
	public:
		ASTIdentifierNode(std::string identifier , int lineNumber);
	};
	
	class ASTFunctionCallNode :public ASTExprNode {
		std::string _identifier;
		int _lineNumber;
		std::vector<ASTExprNode*>_parameters;
	public:
		ASTFunctionCallNode(std::string identifier,std::vector<ASTExprNode*>parameters, int lineNumber);
	};
	
	class ASTBinaryExprNode :public ASTExprNode {
		std::string _optor;
		int _lineNumber;
		ASTExprNode* _expr1;
		ASTExprNode* _expr2;
	public:
		ASTBinaryExprNode(std::string optor , ASTExprNode* expr1, ASTExprNode* expr2, int lineNumber);
	};
	
	class ASTUnaryExprNode :public ASTExprNode {
		std::string _optor;
		int _lineNumber;
		ASTExprNode* _expr;
		
	public:
		ASTUnaryExprNode(std::string optor, ASTExprNode * expr, int lineNumber);
	};
	
}

