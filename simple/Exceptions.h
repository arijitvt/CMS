#ifndef EXCEPTIONS_HH
#define EXCEPTIONS_HH



#include <string>
using namespace std;


class Exception {
	public:
		Exception(string msg);

	private:
		string _exception_msg;
};

#endif
