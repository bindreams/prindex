#pragma once
#include "pretty_index.hpp"

#include <chrono>
#include <iostream>
#include <string>
#include <map>
#include <thread>

using namespace std;
using namespace std::chrono_literals;
namespace ch = std::chrono;

namespace nm {
class A {};
class B {};
}

void time_macro() {
	std::size_t N = 1000000;
	auto t1 = ch::steady_clock::now();
	for (std::size_t i = 0; i < N; i++) {
		////////////////////////////////////////////////////////////////////////////

		prettyid(std::map<std::string, nm::A>);

		////////////////////////////////////////////////////////////////////////////
	}
	auto t2 = ch::steady_clock::now();
	auto time = ch::duration_cast<ch::nanoseconds>(t2 - t1).count() / N;

	cout << "Timed prettyid(std::map<std::string, nm::A>)" << endl;
	cout << "    " << time << "ns" << endl << endl;
}

void time_ctor() {
	std::size_t N = 1000000;
	auto t1 = ch::steady_clock::now();
	for (std::size_t i = 0; i < N; i++) {
		////////////////////////////////////////////////////////////////////////////

		zhukov::pretty_index(typeid(std::map<std::string, nm::A>));

		////////////////////////////////////////////////////////////////////////////
	}
	auto t2 = ch::steady_clock::now();
	auto time = ch::duration_cast<ch::nanoseconds>(t2 - t1).count() / N;

	cout << "Timed zhukov::pretty_index(typeid(std::map<std::string, nm::A>))" << endl;
	cout << "    " << time << "ns" << endl << endl;
}

void time_name() {
	auto x = prettyid(std::map<std::string, nm::A>);

	std::size_t N = 1000000;
	auto t1 = ch::steady_clock::now();
	for (std::size_t i = 0; i < N; i++) {
		////////////////////////////////////////////////////////////////////////////

		x.name();

		////////////////////////////////////////////////////////////////////////////
	}
	auto t2 = ch::steady_clock::now();
	auto time = ch::duration_cast<ch::nanoseconds>(t2 - t1).count() / N;

	cout << "Timed zhukov::pretty_index::name()" << endl;
	cout << "    " << time << "ns" << endl << endl;
}

void time_hash() {
	auto x = prettyid(std::map<std::string, nm::A>);

	std::size_t N = 1000000;
	auto t1 = ch::steady_clock::now();
	for (std::size_t i = 0; i < N; i++) {
		////////////////////////////////////////////////////////////////////////////

		x.hash_code();

		////////////////////////////////////////////////////////////////////////////
	}
	auto t2 = ch::steady_clock::now();
	auto time = ch::duration_cast<ch::nanoseconds>(t2 - t1).count() / N;

	cout << "Timed zhukov::pretty_index::hash_code()" << endl;
	cout << "    " << x.hash_code() << endl;
	cout << "    " << time << "ns" << endl << endl;
}

void time_less() {
	auto x = prettyid(std::map<std::string, nm::A>);
	auto y = prettyid(std::map<std::string, nm::B>);

	std::size_t N = 1000000;
	auto t1 = ch::steady_clock::now();
	for (std::size_t i = 0; i < N; i++) {
		////////////////////////////////////////////////////////////////////////////

		x < y;

		////////////////////////////////////////////////////////////////////////////
	}
	auto t2 = ch::steady_clock::now();
	auto time = ch::duration_cast<ch::nanoseconds>(t2 - t1).count() / N;

	cout << "Timed zhukov::pretty_index::operator<()" << endl;
	cout << "    " << (x < y) << endl;
	cout << "    " << time << "ns" << endl << endl;
}

void time_typeid() {
	std::size_t N = 1000000;
	auto t1 = ch::steady_clock::now();
	for (std::size_t i = 0; i < N; i++) {
		////////////////////////////////////////////////////////////////////////////

		typeid(std::map<std::string, nm::A>);

		////////////////////////////////////////////////////////////////////////////
	}
	auto t2 = ch::steady_clock::now();
	auto time = ch::duration_cast<ch::nanoseconds>(t2 - t1).count() / N;

	cout << "Timed typeid(std::map<std::string, nm::A>)" << endl;
	cout << "    " << typeid(std::map<std::string, nm::A>).name() << endl;
	cout << "    " << time << "ns" << endl << endl;
}

void time_type_index() {
	std::size_t N = 1000000;
	auto t1 = ch::steady_clock::now();
	for (std::size_t i = 0; i < N; i++) {
		////////////////////////////////////////////////////////////////////////////

		std::type_index(typeid(std::map<std::string, nm::A>));

		////////////////////////////////////////////////////////////////////////////
	}
	auto t2 = ch::steady_clock::now();
	auto time = ch::duration_cast<ch::nanoseconds>(t2 - t1).count() / N;

	cout << "Timed std::type_index (typeid(std::map<std::string, nm::A>))" << endl;
	cout << "    " << std::type_index(typeid(std::map<std::string, nm::A>)).name() << endl;
	cout << "    " << time << "ns" << endl << endl;
}

void time_type_index_name() {
	auto x = std::type_index(typeid(std::map<std::string, nm::A>));

	std::size_t N = 1000000;
	auto t1 = ch::steady_clock::now();
	for (std::size_t i = 0; i < N; i++) {
		////////////////////////////////////////////////////////////////////////////

		x.name();

		////////////////////////////////////////////////////////////////////////////
	}
	auto t2 = ch::steady_clock::now();
	auto time = ch::duration_cast<ch::nanoseconds>(t2 - t1).count() / N;

	cout << "Timed std::type_index::name()" << endl;
	cout << "    " << x.name() << endl;
	cout << "    " << time << "ns" << endl << endl;
}

void test_all() {
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