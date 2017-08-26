#pragma once
#include "pretty_index.hpp"

#include <chrono>
#include <iostream>
#include <string>
#include <map>
#include <thread>

namespace ch = std::chrono;
using namespace zhukov;

namespace nm {
struct A {};
struct B { virtual ~B() = default; };
struct D : B {};
}

void time_print(const std::string& msg, const long long& time) {
	std::string str_time = std::to_string(time);
	str_time += "ns";

	std::cout << msg;
	if (msg.length() + str_time.length() > 80-1-1) std::cout << std::endl << std::string(80-1-str_time.length(), ' ');
	else std::cout << std::string(80-1 - msg.length() - str_time.length(), ' ');
	std::cout << str_time << std::endl;
}

#define TIME(times, ...) { \
	std::size_t TIME_N = times; \
	auto TIME_t1 = ch::steady_clock::now(); \
	for (std::size_t i = 0; i < TIME_N; i++) { \
		__VA_ARGS__; \
	} \
	\
	auto TIME_t2 = ch::steady_clock::now(); \
	auto TIME_time = ch::duration_cast<ch::nanoseconds>(TIME_t2 - TIME_t1).count() / TIME_N; \
	\
	std::string TIME_msg = "Timed "; \
	TIME_msg += #__VA_ARGS__; \
	time_print(TIME_msg, TIME_time); \
}

#if defined (__GNUC__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wunused-value"
#endif

void test_all() {
	std::cout << "prettyid(std::string).name() =" << std::endl << prettyid<std::string>().name() << std::endl << std::endl;
	std::cout << "prettyid(std::map<std::string, nm::A>).name() =" << std::endl << prettyid<std::map<std::string, nm::A>>().name() << std::endl;

	const std::size_t N = 1000000;

	auto prettyindex_a = prettyid<std::map<std::string, nm::A>>();
	auto prettyindex_b = prettyid<std::map<std::string, nm::B>>();

	auto& typeinfo_a = typeid(std::map<std::string, nm::A>);
	auto& typeinfo_b = typeid(std::map<std::string, nm::B>);

	auto typeindex_a = std::type_index(typeid(std::map<std::string, nm::A>));
	auto typeindex_b = std::type_index(typeid(std::map<std::string, nm::B>));

	nm::D poly_var;
	nm::B& polymorphic_reference = poly_var;

	auto x = prettyid(polymorphic_reference);
	auto y = x;
	x.~pretty_index();
	std::cout << y.name() << "\n";

	std::cout << std::endl << "Measuring zhukov::pretty_index:" << std::endl;

	TIME(N, prettyid<nm::A>());
	TIME(N, prettyid(polymorphic_reference));
	TIME(N, prettyindex_a.name());
	TIME(N, prettyindex_a.hash_code());
	TIME(N, prettyindex_a == prettyindex_b);
	TIME(N, prettyindex_a < prettyindex_b);
	TIME(N, prettyindex_a.before(prettyindex_b));

	std::cout << std::endl << "Measuring std::type_info:" << std::endl;

	TIME(N, typeid(nm::A));
	TIME(N, typeid(polymorphic_reference));
	TIME(N, typeinfo_a.name());
	TIME(N, typeinfo_a.hash_code());
	TIME(N, typeinfo_a == typeinfo_b);
	TIME(N, typeinfo_a.before(typeinfo_b));

	std::cout << std::endl << "Measuring std::type_index:" << std::endl;

	//TIME(N, std::type_index(typeinfo_a));
	TIME(N, typeindex_a.name());
	TIME(N, typeindex_a.hash_code());
	TIME(N, typeindex_a == typeindex_b);
	TIME(N, typeindex_a < typeindex_b);
}

#if defined (__GNUC__)
#	pragma clang diagnostic pop
#endif