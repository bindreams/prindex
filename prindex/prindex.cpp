#include "prindex.hpp"
#include "prid.hpp"

const char* prindex::name() const {
	return m_info->name();
}

std::size_t prindex::hash_code() const {
	return m_info->hash_code();
}

bool prindex::operator==(const prindex & rhs) const noexcept {
	return *m_info == *rhs.m_info;
}

bool prindex::operator!=(const prindex & rhs) const noexcept {
	return !operator==(rhs);
}

bool prindex::operator<(const prindex & rhs) const noexcept {
	return m_info->before(*rhs.m_info);
}

bool prindex::operator<=(const prindex & rhs) const noexcept {
	return !operator>(rhs);
}

bool prindex::operator>(const prindex & rhs) const noexcept {
	return rhs.operator< (*this);
}

bool prindex::operator>=(const prindex & rhs) const noexcept {
	return !operator<(rhs);
}

prindex::prindex(const std::type_info & info) :
	m_info(&get_prinfo(std::type_index(info))) {
}

prindex::prindex(const prinfo & info) :
	m_info (&info) {
}
