#include <iostream>
#include "lexer/lexer.h"
#include "parser/parser.h"

#include "visitor/senamticAnalysis.h"

int main()
{
	/*ifstream& file;
	file.open("file.txt");*/



	std::string program=
		" def func1():int{ return 5;}";
	lexer:: Lexer lexer(program);
	std::cout << "LENGTH OF TOKENS=" << lexer.tokens.size() << std::endl;
	for (size_t i = 0; i < lexer.tokens.size(); i++)
	{
		std::cout << "token = "<<lexer.tokens[i].getVal() << " \t\t\t\t and   type ="<< lexer.tokens[i].getType() << std::endl;
		
	}
	parser::ASTProgramNode* prog = nullptr;
	parser::Parser parser(&lexer);
	try {
		
		prog=parser.parse_program();

	}
	catch (std::exception & exception)
	{
		std::cerr << "error :" << exception.what() << std::endl;
	}
	try {
		SemanticAnalyser semantic;
		semantic.visit(prog);
	}
	catch (std::exception & e) {
		std::cerr << "ERROR:: semantic analysisis error occured  description:: " << e.what() << std::endl;
	}
	
	return 0;
}