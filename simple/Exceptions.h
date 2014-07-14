#ifndef EXCEPTIONS_HH
#define EXCEPTIONS_HH



#include <string>
#include <exception>
using namespace std;

/**
 * This class implements the exception
 * for the CMS application.
 */
class CMSException:public exception {
	public:
		/**
		 * Constructor for the Exceptions.
		 * @param msg holds the message to be thrown to the system.
		 */
		CMSException(string msg);
		/**
		 * virtual what implementation of base exception class.
		 */
		virtual const char* what() const throw();

	private:
		string _exception_msg;
};

#endif
