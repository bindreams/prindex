#include "prinfo.hpp"
#include "demangle.hpp"
#include "hash.hpp"

prinfo::prinfo(const std::type_index & index) :
	m_name(demangle(index.name())),
	m_hash_code(hash(m_name)) {
}

const char* prinfo::name() const {
	return m_name.c_str();
}

std::size_t prinfo::hash_code() const {
	return m_hash_code;
}

bool prinfo::operator==(const prinfo & rhs) const {
	return m_name == rhs.m_name;
}

bool prinfo::operator!=(const prinfo & rhs) const {
	return !operator==(rhs);
}

bool prinfo::before(const prinfo & other) const {
	return m_hash_code < other.m_hash_code;
}
