#include <iostream>
#include <map>
#include "prid.hpp"

using zh::prid;

namespace name_space {
class MyClass {};
}

template <class T>
struct TemplateStruct {};

class BaseClass {};
class DerivedClass : public BaseClass {};

int main() {
	int int_var = 42;
	name_space::MyClass class_var;
	TemplateStruct<double> template_var;
	BaseClass* polymorphic_var = new DerivedClass;

	std::cout << prid(int_var).name() << std::endl; // 
	std::cout << prid(class_var).name() << std::endl; // 
	std::cout << prid(template_var).name() << std::endl; // 
	std::cout << prid(polymorphic_var).name() << std::endl; // 
	std::cout << typeid(polymorphic_var).name() << std::endl; // 

	//std::cout << "prid(std::string).name() =" << std::endl << prid(std::string).name() << std::endl << std::endl;
	//std::cout << "prid(std::map<std::string, nm::A>).name() =" << std::endl << prid(std::map<std::string, double>).name() << std::endl;
}