
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

	visitor::SemanticScope semanticGlobalScope;

	visitor::InterpreterScope interpreterGlobalScope;
	std::cout << "Anubadak and Interpreter";
	std::cout << "\nCopyRight: ";
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

			unsigned int openScopes = 0;
			openScopes += std::count(input_line.begin(), input_line.end(), '{');
			openScopes -= std::count(input_line.begin(), input_line.end(), '}');

			while (openScopes) {
				std::cout << "... ";
				input_line.clear();
				getline(std::cin, input_line);

				openScopes += std::count(input_line.begin(), input_line.end(), '{');
				openScopes -= std::count(input_line.begin(), input_line.end(), '}');

				program += input_line + "\n";
			}

		}
		///
		
	


		try
		{
			lexer::Lexer lexer(program);
			//---------------A
			std::cout << "lexing task completed \n";
			parser::Parser parser(&lexer);


			parser::ASTProgramNode* prog;



			try {
				prog = parser.parse_program();
				try {
					visitor::SemanticScope temp = semanticGlobalScope;
					visitor::SemanticAnalyser tempSemanticAnalyser(&temp);
					tempSemanticAnalyser.visit(prog);


					visitor::SemanticAnalyser semanticAnalyser(&semanticGlobalScope);
					semanticAnalyser.visit(prog);

					try {
						visitor::Interpreter interpreter(&interpreterGlobalScope);
						interpreter.visit(prog);
					}
					catch (std::exception & exception)
					{
						throw;
					}

				}
				catch (std::exception & exception)
				{
					throw;
				}


			}

			catch (std::exception & exception)
			{
				throw;
			}
		}

		catch (std::exception & exception)
		{
			std::cerr << "error :" << exception.what() << std::endl;
		}


	}

	return 0;
}


