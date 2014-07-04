#ifndef EXCEPTIONS_HH
#define EXCEPTIONS_HH



#include <string>
#include <exception>
using namespace std;


class CMSException:public exception {
	public:
		CMSException(string msg);
		virtual const char* what() const throw();

	private:
		string _exception_msg;
};

#endif
