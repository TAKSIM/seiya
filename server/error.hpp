//error.hpp
#ifndef SERVER_ERROR_H
#define SERVER_ERROR_H

#include "configs.hpp"
#include <exception>
#include <sstream>
#include <boost/assert.hpp>
#include <boost/current_function.hpp>

class Error : public std::exception
{
protected:
	char* m_msg;

public:
	Error(const char* description,
		const char* file,
		long line,
		const char* functionName,
		const char* library,
		const char* internal_msg = "");

	~Error()
	{
		if (m_msg != NULL)
			free(m_msg);
	}

	const char* what() const throw();
};

#define SERVER_FAIL(message) \
	throw Error(message, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, "Server","");

#endif