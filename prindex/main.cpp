#include <iostream>
#include <map>
#include <string>
#include "prid.hpp"
using namespace std;
using zh::prid;

namespace name_space {
class MyClass {};
}

template <class T>
struct TemplateStruct {};

class BadBaseClass {};
class BadDerivedClass : public BadBaseClass {};

struct GoodBaseClass { virtual ~GoodBaseClass() = default; };
struct GoodDerivedClass : public GoodBaseClass {};

#define TEST(string, ...) {\
	if (strcmp(PRID(__VA_ARGS__).name(), string) == 0) { \
		cout << "Passed: "; \
		cout << "tested " << #__VA_ARGS__ << ", got " << string << endl; \
	} \
	else { \
		cout << "Failed: "; \
		cout << "tested " << #__VA_ARGS__ << ", expected " << string << ", got " << PRID(__VA_ARGS__).name() << endl; \
	} \
}

int main() {
	cout << "Platform: ";
#ifdef __clang__
	cout << "clang" << endl;
#elif defined __GNUG__
	cout << "g++" << endl;
#elif defined _MSC_VER
	cout << "VC++" << endl;
#endif
	cout << endl;

	// Built-in types
	TEST("int", int);
	TEST("float", float);
	TEST("double", double);
	TEST("char", char);
	TEST("bool", bool);

	TEST("int*", int*);
	TEST("int**", int**);

	// Standard library
	TEST("std::basic_string<char, std::char_traits<char>, std::allocator<char> >", std::string);
	TEST("std::map<int, double, std::less<int>, std::allocator<std::pair<int const, double> > >", std::map<int, double>);

	// Weird Behaviour
	TEST("int", const int&);

	// Namespaces and templates
	TEST("name_space::MyClass", name_space::MyClass);
	TEST("TemplateStruct<int>", TemplateStruct<int>);
	TEST("TemplateStruct<TemplateStruct<int> >", TemplateStruct<TemplateStruct<int>>);
	TEST("bool", bool);

	// Variables
	int int_var = 42;
	name_space::MyClass class_var;
	TemplateStruct<double> template_var;
	BadBaseClass* non_polymorphic_var = new BadDerivedClass;
	GoodBaseClass* polymorphic_var = new GoodDerivedClass;

	TEST("int", int_var);
	TEST("name_space::MyClass", class_var);
	TEST("TemplateStruct<double>", template_var);
	TEST("BadBaseClass", *non_polymorphic_var);
	TEST("GoodDerivedClass", *polymorphic_var);
}