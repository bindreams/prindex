#pragma once
#include "prinfo.hpp"
#include "get_prinfo.hpp"

namespace zh {

class prindex {
private:
	const prinfo* m_info;

public:
	// Construction
	prindex() = delete;
	prindex(const std::type_info& info);
	prindex(const prinfo& info);

	prindex(const prindex&) = default;
	prindex(prindex&&) = default;

	prindex& operator=(const prindex&) = default;
	prindex& operator=(prindex&&) = default;

	~prindex() = default;

	// Member functions
	const char* name() const;
	std::size_t hash_code() const;

	bool operator==(const prindex& rhs) const noexcept;
	bool operator!=(const prindex& rhs) const noexcept;
	bool operator< (const prindex& rhs) const noexcept;
	bool operator<=(const prindex& rhs) const noexcept;
	bool operator> (const prindex& rhs) const noexcept;
	bool operator>=(const prindex& rhs) const noexcept;
};

} // namespace zh

namespace std {

template<> struct hash<zh::prindex> {
	std::size_t operator()(const zh::prindex& obj) const {
		return obj.hash_code();
	}
};

} // namespace std

// Definitions =================================================================

namespace zh {

inline const char* prindex::name() const {
	return m_info->name();
}

inline std::size_t prindex::hash_code() const {
	return m_info->hash_code();
}

inline bool prindex::operator==(const prindex & rhs) const noexcept {
	return *m_info == *rhs.m_info;
}

inline bool prindex::operator!=(const prindex & rhs) const noexcept {
	return !operator==(rhs);
}

inline bool prindex::operator<(const prindex & rhs) const noexcept {
	return m_info->before(*rhs.m_info);
}

inline bool prindex::operator<=(const prindex & rhs) const noexcept {
	return !operator>(rhs);
}

inline bool prindex::operator>(const prindex & rhs) const noexcept {
	return rhs.operator< (*this);
}

inline bool prindex::operator>=(const prindex & rhs) const noexcept {
	return !operator<(rhs);
}

inline prindex::prindex(const std::type_info & info) :
	m_info(&detail::get_prinfo(std::type_index(info))) {
}

inline prindex::prindex(const prinfo & info) :
	m_info(&info) {
}

} // namespace zh