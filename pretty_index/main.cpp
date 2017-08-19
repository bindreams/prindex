#include "tests.hpp"

int main() {
	cout << "prettyid(std::string).name() =" << endl << prettyid(std::string).name() << endl << endl;
	cout << "prettyid(std::map<std::string, nm::A>).name() =" << endl << prettyid(std::map<std::string, nm::A>).name() << endl << endl;

	time_macro();
	time_ctor();
	time_name();
	time_hash();
	time_less();

	cout << "Measuring typeid" << endl << endl;

	time_typeid();
	time_type_index();
	time_type_index_name();
}