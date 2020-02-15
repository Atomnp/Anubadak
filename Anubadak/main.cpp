#include <iostream>
#include "lexer.h"

int main()
{
	/*ifstream& file;
	file.open("file.txt");*/



	std::string program="int we 12 and 13 also 34 f";
	lexer:: Lexer lexer(program);
	std::cout << "LENGTH OF TOKENS=" << lexer.tokens.size() << std::endl;
	for (int i = 0; i < lexer.tokens.size(); i++)
	{
		std::cout << lexer.tokens[i].getVal() << ",  type ="<< lexer.tokens[i].getType() << std::endl;
		
	}



	return 0;
}