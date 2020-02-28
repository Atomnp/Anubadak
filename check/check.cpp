#include <iostream>
#include <map>

int main()
{
	std::multimap<std::string, std::tuple<int, float>>signature;
	signature.insert = std::make_tuple<int, float>(1, 1.00);
}