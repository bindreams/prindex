#pragma once
#include <cstring> // strlen
#include <string> // string

#include <ciso646> // lib check macro
#ifdef _LIBCPP_VERSION
#	include <cxxabi.h> // abi::__cxa_demangle
#   include <cstdlib> // free
//	Using LLVM libc++
#elif __GLIBCXX__ // Note: only version 6.1 or newer define this in ciso646
#	include <cxxabi.h> // abi::__cxa_demangle
#   include <cstdlib> // free
//	Using GNU libstdc++
#elif _CPPLIB_VER // Note: used by Visual Studio

#else
#	error prindex: unsupported standard library detected. Supported libraries are: LLVM libc++, GNU libstdc++, Dinkumware STL
#endif

inline std::string demangle(const char* name) {
	std::string str(name);

	auto cut = [&str](const char* what) {
		std::size_t len = strlen(what);

		auto i = str.find(what);
		while (i != std::string::npos) {
			str.erase(i, len);
			i = str.find(what, i);
		}
	};

	auto replace = [&str](const char* source, const char* target) {
		std::size_t source_len = strlen(source);
		std::size_t target_len = strlen(target);

		auto i = str.find(source);
		while (i != std::string::npos) {
			// string::replace can only work if target is not bigger than source
			if (target_len > source_len) {
				// If target is bigger, shift the rest of the string to the right
				str.replace(
					i + target_len, 
					std::string::npos, 
					str.substr(i + source_len, std::string::npos));
				str.replace(i, target_len, target);
			}
			else {
				str.replace(i, source_len, target);
			}

			i += target_len;
			i = str.find(source, i);
		}
	};

#if defined (_CPPLIB_VER)

	cut("class ");
	cut("struct ");
	replace(" ,", ",");
	replace(",", ", ");

#elif defined(_LIBCPP_VERSION)

	int status = 0;
	char* demangled = abi::__cxa_demangle(name, nullptr, nullptr, &status);
	if (status != 0) {
		std::free(demangled);
		throw std::runtime_error("prindex: abi::__cxa_demangle failed");
	}

	str = demangled;
	std::free(demangled);

#elif defined (__GLIBCXX__)

	int status = 0;
	char* demangled = abi::__cxa_demangle(name, nullptr, nullptr, &status);
	if (status != 0) {
		std::free(demangled);
		throw std::runtime_error("prindex: abi::__cxa_demangle failed");
	}

	str = demangled;
	std::free(demangled);

#endif

	return str;
}