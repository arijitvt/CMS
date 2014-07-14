#ifndef ERROR_MSG_H
#define ERROR_MSG_H


#include <string>
using namespace std;


/**
 * This class contains the strings for the error messages.
 */
class ErrorMsgs {
	public:
		static const string UN_AUTH; ///< Unauthorized message
		static const string UN_ORDER; ///<Unknown order message
		static const string UN_DEALER; ///< Unknown dealer message
		static const string UN_COMMODITY; ///< Unknown Commodity message
		static const string INVALID; ///< Invalid message
} ;




#endif
