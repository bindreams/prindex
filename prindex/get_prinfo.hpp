#pragma once
#include <unordered_map> // unordered_map
#include <typeindex> // type_index
#include "prinfo.hpp"

namespace zh {
namespace detail {

static std::unordered_map<std::type_index, prinfo> types;

inline const prinfo& get_prinfo(const std::type_index& index) {
	auto got = types.find(index);

	if (got == types.end()) {
		got = types.emplace(std::make_pair(index, prinfo(index))).first;
	}

	return got->second;
}

} // namespace detail
} // namespace zh