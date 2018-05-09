#pragma once
#include "get_prinfo.hpp"
#include "prinfo.hpp"
#include "prindex.hpp"

#ifdef PRINDEX_WANT_MACROS

#define prid(...) \
detail::get_prinfo(typeid(__VA_ARGS__))

#define pridx(...) \
prindex(detail::get_prinfo(typeid(__VA_ARGS__)))

#else

template <typename T>
inline const prinfo& prid() {
	return detail::get_prinfo(typeid(T));
}

template <typename T>
inline const prinfo& prid(T&& obj) {
	return detail::get_prinfo(typeid(std::forward<T>(obj)));
}

template <typename T>
inline prindex pridx() {
	return prindex(detail::get_prinfo(typeid(T)));
}

template <typename T>
inline prindex pridx(T&& obj) {
	return prindex(detail::get_prinfo(typeid(std::forward<T>(obj))));
}

#endif // PRINDEX_NO_MACROS