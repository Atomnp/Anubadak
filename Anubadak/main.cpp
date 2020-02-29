#include <iostream>
#include "lexer/lexer.h"
#include "parser/parser.h"
#include <fstream>

#include "visitor/senamticAnalysis.h"
#include "visitor/interpreter.h"

int main()
{
	/*ifstream& file;
	file.open("file.txt");*/

	std::ifstream inputFile;
	inputFile.open("myprogram.txt");
	std::string program;
	std::string tempString;
	while (std::getline(inputFile, tempString)) {
		program.append(tempString);
		program.append("\n");
	}

	std::cout << program << std::endl;

	//std::string program=
	//	" //this is comment \n def func(x: int):int \n  {print(\" i m the function \");\nreturn 2*x;} \n var y: int=func(9); print(\"hello there \\n\");\n print(y);";
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
	
	try {
		Interpreter interpreter;
		interpreter.visit(prog);
	}
	catch (std::exception & e) {
		std::cerr << "interprete ERROR:" << e.what() << std::endl;
	}

	return 0;
}