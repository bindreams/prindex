#pragma once
#include "get_prinfo.hpp"
#include "prinfo.hpp"
#include "prindex.hpp"

template <typename T>
inline const prinfo& prid() {
	return get_prinfo(typeid(T));
}

template <typename T>
inline const prinfo& prid(T&& obj) {
	return get_prinfo(typeid(std::forward<T>(obj)));
}

template <typename T>
inline prindex pridx() {
	return prindex(get_prinfo(typeid(T)));
}

template <typename T>
inline prindex pridx(T&& obj) {
	return prindex(get_prinfo(typeid(std::forward<T>(obj))));
}