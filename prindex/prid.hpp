#pragma once
#include "get_prinfo.hpp"
#include "prinfo.hpp"
#include "prindex.hpp"

namespace zh {

template <class T>
inline const prinfo& prid() {
	return detail::get_prinfo(typeid(T));
}

template <class T>
inline const prinfo& prid(T&& obj) {
	return detail::get_prinfo(typeid(std::forward<T>(obj)));
}

template <class T>
inline prindex pridx() {
	return prindex(detail::get_prinfo(typeid(T)));
}

template <class T>
inline prindex pridx(T&& obj) {
	return prindex(detail::get_prinfo(typeid(std::forward<T>(obj))));
}

} // namespace zh

#define PRID(...) \
zh::detail::get_prinfo(typeid(__VA_ARGS__))

#define PRIDX(...) \
zh::prindex(zh::detail::get_prinfo(typeid(__VA_ARGS__)))