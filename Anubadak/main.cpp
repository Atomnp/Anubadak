
#include <iostream>
#include "lexer/lexer.h"
#include "parser/parser.h"
#include <fstream>
#include<regex>

#include "visitor/senamticAnalysis.h"
#include "visitor/interpreter.h"
int main()
{

	
	/*ifstream& file;
	file.open("file.txt");*/
	/*
	SemanticScope semanticGlobalScope;
	InterpreterScope interpreterGlobalScope;
	std::cout << "Anubadak and Interpreter";
	std::cout << "\nCopyRight: 075BCT";
	std::cout << "\nType : #help if you need help";
	while (1)
	{
		std::string input_line;
		std::string program;
		std::cout << "\n>>>  ";
		std::getline(std::cin, input_line);
		// removes the leading and trailing spaces, regex is used .
		input_line = std::regex_replace(input_line, std::regex("^ +| +$"), "$1");

		if (input_line == "#help") {

			std::cout << "\n" << "Welcome to Anubadak Programming \n\n";

			std::cout << "Here are the guidelines for the command\n";

			std::cout << "" << ">>> #load TO load the program\n\n";
			std::cout << " #quit            Exits from the  REPL.\n\n";
			std::cout << " #clear           Clears the terminal window." << std::endl;
			std::cout << "OR simply start writing the code if u want to used REPL for interpreting ";
		}

		else if (input_line == "#clear")
		{
			std::cout << std::string(50, '\n');
		}
		else if (input_line == "#quit")
		{
			return 0;
		}
		else {
			program += input_line;

			unsigned int open_scopes = 0;
			open_scopes += std::count(input_line.begin(), input_line.end(), '{');
			open_scopes -= std::count(input_line.begin(), input_line.end(), '}');

			while (open_scopes) {
				std::cout << "... ";
				input_line.clear();
				getline(std::cin, input_line);

				open_scopes += std::count(input_line.begin(), input_line.end(), '{');
				open_scopes -= std::count(input_line.begin(), input_line.end(), '}');

				program += input_line + "\n";
			}

		}
		lexer::Lexer lexer(program);

		parser::ASTProgramNode* prog = nullptr;
		parser::Parser parser(&lexer);
		try {

		
			lexer::Lexer lexer(program);
			//---------------A
			std::cout << "lexing task completed \n";

			parser::Parser parser(&lexer);


			parser::ASTProgramNode* prog;

	
			try {
				prog = parser.parse_program();
			}

			catch (const std::exception & e) {

				try {
					
					if (program.back() == ';')
						program.pop_back();

				
					lexer::Lexer expr_lexer(program);
					parser = parser::Parser(&expr_lexer, 0);  
					prog = new parser::ASTProgramNode(
						std::vector<parser::ASTNode*>({ parser.parseExpression() }));
				}
				catch (const std::exception & expr_e) {

	
					throw std::runtime_error(e.what());
				}
			}
		
			// Generate XML
			//visitor::XMLVisitor xml_generator;
			//xml_generator.visit(prog);
			

		
			SemanticScope temp = semanticGlobalScope;
			SemanticAnalyser tempSemanticAnalyser(&temp);
			tempSemanticAnalyser.visit(prog);

	
			SemanticAnalyser semanticAnalyser(&semanticGlobalScope);  
			semanticAnalyser.visit(prog);

			Interpreter interpreter(&interpreterGlobalScope);
			interpreter.visit(prog);


		}


		catch (const std::exception & e) {
			std::cerr << e.what() << std::endl;
		}

	}
	return 0;
}


*/

std::ifstream inputFile;
inputFile.open("myprogram.txt");
std::string program;
std::string tempString;
while (std::getline(inputFile, tempString)) {
	program.append(tempString);
	program.append("\n");
}
if (DEBUG == true) {
	std::cout << "the program is  shown below ......" << std::endl;
	std::cout << program << std::endl;
}
//std::string program=
//	" //this is comment \n def func(x: int):int \n  {print(\" i m the function \");\nreturn 2*x;} \n var y: int=func(9); print(\"hello there \\n\");\n print(y);";
lexer::Lexer lexer(program);
if (DEBUG) {
	std::cout << "LENGTH OF TOKENS=" << lexer.tokens.size() << std::endl;
	for (size_t i = 0; i < lexer.tokens.size(); i++)
	{
		std::cout << "token = " << lexer.tokens[i].getVal() << " \t\t\t\t and   type =" << lexer.tokens[i].getType() << std::endl;
	}
}
parser::ASTProgramNode* prog = nullptr;
parser::Parser parser(&lexer);
try {

	prog = parser.parse_program();
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

