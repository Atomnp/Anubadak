#include <iostream>
#include "lexer/lexer.h"
#include "parser/parser.h"

int main()
{
	/*ifstream& file;
	file.open("file.txt");*/



	std::string program="def funcName(): nt {var x:int =0;}";
	lexer:: Lexer lexer(program);
	std::cout << "LENGTH OF TOKENS=" << lexer.tokens.size() << std::endl;
	for (size_t i = 0; i < lexer.tokens.size(); i++)
	{
		std::cout << "token = "<<lexer.tokens[i].getVal() << " \t\t\t\t and   type ="<< lexer.tokens[i].getType() << std::endl;
		
	}
	parser::Parser parser(&lexer);
	try {
		
		parser.parse_program();

	}
	catch (std::exception & exception)
	{
		std::cerr << "error :" << exception.what() << std::endl;
	}
	
	return 0;
}