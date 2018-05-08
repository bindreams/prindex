#pragma once
#include <string> // string
#include <cstddef> // size_t
#include <typeindex> // type_index

class prinfo {
private:
	std::string m_name;
	std::size_t m_hash_code;

	prinfo(const std::type_index& index);

public:
	// Construction
	prinfo() = delete;
	prinfo(const prinfo& other) = delete;
	prinfo(prinfo&& other) = default;

	prinfo& operator=(const prinfo& rhs) = delete;
	prinfo& operator=(prinfo&& rhs) = default;

	virtual ~prinfo() = default;

	// Member functions
	const char* name() const;
	std::size_t hash_code() const;

	bool operator==(const prinfo& rhs) const;
	bool operator!=(const prinfo& rhs) const;

	bool before(const prinfo& other) const;

	// Friends
	friend inline const prinfo& get_prinfo(const std::type_index& index);
};