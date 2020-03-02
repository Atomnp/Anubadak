#include <iostream>
#include <fstream>
#include <string>
int main()
{
	std::ifstream inputFile;
	inputFile.open("myprogram.txt");
	std::string myProgram;
	std::string tempString;
	while (std::getline(inputFile, tempString)) {
		myProgram.append(tempString);
		myProgram.append("\n");
	}
	std::cout << myProgram;

	return 0;
}