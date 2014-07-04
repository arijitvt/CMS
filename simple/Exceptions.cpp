#include <Exceptions.h>


CMSException::CMSException(string msg) 
	: _exception_msg(msg) {
	
}

const char* CMSException::what() const throw() {
	return _exception_msg.c_str();
}

