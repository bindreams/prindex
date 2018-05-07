#pragma once
#include "prinfo.hpp"

class prindex {
private:
	const prinfo* m_info;

public:
	const char* name() const;
	std::size_t hash_code() const;

	bool operator==(const prindex& rhs) const noexcept;
	bool operator!=(const prindex& rhs) const noexcept;
	bool operator< (const prindex& rhs) const noexcept;
	bool operator<=(const prindex& rhs) const noexcept;
	bool operator> (const prindex& rhs) const noexcept;
	bool operator>=(const prindex& rhs) const noexcept;

	prindex() = delete;
	prindex(const std::type_info& info);
	prindex(const prinfo& info);
};

namespace std {

template<> struct hash<prindex> {
	std::size_t operator()(const prindex& obj) const {
		return obj.hash_code();
	}
};

} // namespace std