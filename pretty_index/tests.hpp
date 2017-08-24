#pragma once
#include "pretty_index.hpp"

#include <chrono>
#include <iostream>
#include <string>
#include <map>
#include <thread>

namespace ch = std::chrono;

namespace nm {
struct A {};
struct B { virtual void foo() {}; };
struct D : B {};
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

	std::cout << "Timed prettyid()nm::A>()" << std::endl;
	std::cout << "    " << time << "ns" << std::endl << std::endl;
}

void time_ctor() {
	nm::D x;
	nm::B& ref = x;

	std::size_t N = 1000000;
	auto t1 = ch::steady_clock::now();
	for (std::size_t i = 0; i < N; i++) {
		////////////////////////////////////////////////////////////////////////////

		zhukov::pretty_index(typeid(std::map<std::string, nm::A>));

		////////////////////////////////////////////////////////////////////////////
	}
	auto t2 = ch::steady_clock::now();
	auto time = ch::duration_cast<ch::nanoseconds>(t2 - t1).count() / N;

	std::cout << "Timed zhukov::prettyid(ref)" << std::endl;
	std::cout << "    " << time << "ns" << std::endl << std::endl;
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

	std::cout << "Timed zhukov::pretty_index::name()" << std::endl;
	std::cout << "    " << time << "ns" << std::endl << std::endl;
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

	std::cout << "Timed zhukov::pretty_index::hash_code()" << std::endl;
	std::cout << "    " << x.hash_code() << std::endl;
	std::cout << "    " << time << "ns" << std::endl << std::endl;
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

	std::cout << "Timed zhukov::pretty_index::operator<()" << std::endl;
	std::cout << "    " << (x < y) << std::endl;
	std::cout << "    " << time << "ns" << std::endl << std::endl;
}

void time_norm_typeid() {
	std::size_t N = 1000000;
	auto t1 = ch::steady_clock::now();
	for (std::size_t i = 0; i < N; i++) {
		////////////////////////////////////////////////////////////////////////////

		typeid(nm::A);

		////////////////////////////////////////////////////////////////////////////
	}
	auto t2 = ch::steady_clock::now();
	auto time = ch::duration_cast<ch::nanoseconds>(t2 - t1).count() / N;

	std::cout << "Timed typeid(nm::A)" << std::endl;
	std::cout << "    " << typeid(nm::A).name() << std::endl;
	std::cout << "    " << time << "ns" << std::endl << std::endl;
}

void time_poly_typeid() {
	nm::D x;
	nm::B& ref = x;

	std::size_t N = 1000000;
	auto t1 = ch::steady_clock::now();
	for (std::size_t i = 0; i < N; i++) {
		////////////////////////////////////////////////////////////////////////////

		typeid(ref);

		////////////////////////////////////////////////////////////////////////////
	}
	auto t2 = ch::steady_clock::now();
	auto time = ch::duration_cast<ch::nanoseconds>(t2 - t1).count() / N;

	std::cout << "Timed typeid(ptr)" << std::endl;
	std::cout << "    " << typeid(ref).name() << std::endl;
	std::cout << "    " << time << "ns" << std::endl << std::endl;
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

	std::cout << "Timed std::type_index (typeid(std::map<std::string, nm::A>))" << std::endl;
	std::cout << "    " << std::type_index(typeid(std::map<std::string, nm::A>)).name() << std::endl;
	std::cout << "    " << time << "ns" << std::endl << std::endl;
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

	std::cout << "Timed std::type_index::name()" << std::endl;
	std::cout << "    " << x.name() << std::endl;
	std::cout << "    " << time << "ns" << std::endl << std::endl;
}

void test_all() {
	std::cout << "prettyid(std::string).name() =" << std::endl << prettyid(std::string).name() << std::endl << std::endl;
	std::cout << "prettyid(std::map<std::string, nm::A>).name() =" << std::endl << prettyid(std::map<std::string, nm::A>).name() << std::endl << std::endl;

	time_macro();
	time_ctor();
	time_name();
	time_hash();
	time_less();

	std::cout << "Measuring typeid" << std::endl << std::endl;

	time_norm_typeid();
	time_poly_typeid();
	time_type_index();
	time_type_index_name();

	/*for (auto&& it : zhukov::details::data_set) {
		std::cout << it.name << std::endl;
	}*/
}