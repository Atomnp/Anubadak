
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
	SemanticScope semanticGlobalScope;
	InterpreterScope interpreterGlobalScope;
	std::cout << "Anubadak and Interpreter";
	std::cout << "\nCopyRight: 075BCT";
	std::cout << "\nType : #help if you need help";
	while (1)
	{
		std::string input_line;
		std::string program;
		bool expr = false;
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

			// Tokenise and initialise parser
			lexer::Lexer lexer(program);
			//---------------A
			std::cout << "lexing task completed \n";

			parser::Parser parser(&lexer);


			parser::ASTProgramNode* prog;

			// Try to parse as program
			try {
				prog = parser.parse_program();
			}

			// Catch by trying to parse as expression
			catch (const std::exception & e) {

				try {
					// If expression ends with ';', get rid of it
					if (program.back() == ';')
						program.pop_back();

					// Parse again, create program node manually
					lexer::Lexer expr_lexer(program);
					parser = parser::Parser(&expr_lexer, 0);  // do not consume first token
					prog = new parser::ASTProgramNode(
						std::vector<parser::ASTNode*>({ parser.parseExpression() }));

					expr = true;
				}
				catch (const std::exception & expr_e) {

					// Throw original error
					throw std::runtime_error(e.what());
				}
			}
			/*
			// Generate XML
			visitor::XMLVisitor xml_generator;
			xml_generator.visit(prog);
			*/

		
			SemanticScope temp = semanticGlobalScope;
			SemanticAnalyser tempSemanticAnalyser(&temp);
			tempSemanticAnalyser.visit(prog);

			// If this succeeds, perform semantic analysis modifying global scope
			SemanticAnalyser semanticAnalyser(&semanticGlobalScope);
			semanticAnalyser.visit(prog);

			// Interpreter
			Interpreter interpreter(&interpreterGlobalScope);
			interpreter.visit(prog);


		}

		

		// Catch exception and print error
		catch (const std::exception & e) {
			std::cerr << e.what() << std::endl;
		}

	}
	return 0;
}

