#pragma once
#include <string> // string
#include <cstddef> // size_t
#include <typeindex> // type_index
#include "demangle.hpp"
#include "hash.hpp"

class prinfo;

namespace detail {
inline const prinfo& get_prinfo(const std::type_index& index);
}

class prinfo {
private:
	std::string m_name;
	std::size_t m_hash_code;

	prinfo(const std::type_index& index);

public:
	// Construction
	prinfo() = delete;
	prinfo(const prinfo&) = delete;
	prinfo(prinfo&&) = default;

	prinfo& operator=(const prinfo&) = delete;
	prinfo& operator=(prinfo&&) = default;

	virtual ~prinfo() = default;

	// Member functions
	const char* name() const;
	std::size_t hash_code() const;

	bool operator==(const prinfo& rhs) const;
	bool operator!=(const prinfo& rhs) const;

	bool before(const prinfo& other) const;

	// Friends
	friend inline const prinfo& detail::get_prinfo(const std::type_index& index);
};

// Definitions =================================================================

inline prinfo::prinfo(const std::type_index & index) :
	m_name(demangle(index.name())),
	m_hash_code(hash(m_name)) {
}

inline const char* prinfo::name() const {
	return m_name.c_str();
}

inline std::size_t prinfo::hash_code() const {
	return m_hash_code;
}

inline bool prinfo::operator==(const prinfo & rhs) const {
	// The only strong equality is equality of names
	// But if hashes are different, so are names
	return m_hash_code == rhs.m_hash_code && m_name == rhs.m_name;
}

inline bool prinfo::operator!=(const prinfo & rhs) const {
	return !operator==(rhs);
}

inline bool prinfo::before(const prinfo & other) const {
	return m_hash_code < other.m_hash_code;
}
