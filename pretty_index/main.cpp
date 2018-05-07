#include <iostream>
#include <map>
#include "prid.hpp"

int main() {
	std::cout << "prid(std::string).name() =" << std::endl << prid<std::string>().name() << std::endl << std::endl;
	std::cout << "prid(std::map<std::string, nm::A>).name() =" << std::endl << prid<std::map<std::string, double>>().name() << std::endl;
}