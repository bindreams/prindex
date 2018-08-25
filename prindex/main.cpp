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

#define TEST_PRID(string, ...) {\
	if (strcmp(PRID(__VA_ARGS__).name(), string) == 0) { \
		cout << "Passed: "; \
		cout << "tested " << #__VA_ARGS__ << ", got " << string << endl; \
	} \
	else { \
		cout << "Failed: "; \
		cout << "tested " << #__VA_ARGS__ << ", expected " << string << ", got " << PRID(__VA_ARGS__).name() << endl; \
	} \
}

#define TEST(...) { \
	if (__VA_ARGS__) { \
		cout << "Passed: "; \
	} \
	else { \
		cout << "Failed: "; \
	} \
	cout << "tested " << #__VA_ARGS__ << endl; \
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

	// Equality and hash codes
	TEST(PRID(int) == PRID(int));
	TEST(PRIDX(int) == PRIDX(int));

	TEST(PRID(int) != PRID(double));
	TEST(PRIDX(int) != PRIDX(double));

	TEST(PRID(int).hash_code() == 3661752227);
	TEST(PRID(float).hash_code() == 3799042738);
	TEST(PRID(double).hash_code() == 3477808853);
	TEST(PRID(char).hash_code() == 158743409);
	TEST(PRID(bool).hash_code() == 3495105888);

	// Names
	// Built-in types
	TEST_PRID("int", int);
	TEST_PRID("float", float);
	TEST_PRID("double", double);
	TEST_PRID("char", char);
	TEST_PRID("bool", bool);

	TEST_PRID("int*", int*);
	TEST_PRID("int**", int**);

	// Standard library
	TEST_PRID("std::basic_string<char, std::char_traits<char>, std::allocator<char> >", std::string);
	TEST_PRID("std::map<int, double, std::less<int>, std::allocator<std::pair<int const, double> > >", std::map<int, double>);

	// Weird Behaviour
	TEST_PRID("int", const int&);

	// Namespaces and templates
	TEST_PRID("name_space::MyClass", name_space::MyClass);
	TEST_PRID("TemplateStruct<int>", TemplateStruct<int>);
	TEST_PRID("TemplateStruct<TemplateStruct<int> >", TemplateStruct<TemplateStruct<int>>);
	TEST_PRID("bool", bool);

	// Variables
	int int_var = 42;
	name_space::MyClass class_var;
	TemplateStruct<double> template_var;
	BadBaseClass* non_polymorphic_var = new BadDerivedClass;
	GoodBaseClass* polymorphic_var = new GoodDerivedClass;

	TEST_PRID("int", int_var);
	TEST_PRID("name_space::MyClass", class_var);
	TEST_PRID("TemplateStruct<double>", template_var);
	TEST_PRID("BadBaseClass", *non_polymorphic_var);
	TEST_PRID("GoodDerivedClass", *polymorphic_var);
}