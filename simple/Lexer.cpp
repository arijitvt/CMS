#include <Lexer.h>
#include <boost/lexical_cast.hpp>


int GetToken(string token) {
	currentToken = token;
	try {
		int num = boost::lexical_cast<int>(token);
		return TOK_INTEGER;
	}
	catch(...) {
		try {
			double d = boost::lexical_cast<double>(token);
			return TOK_DOUBLE;
		}
		catch(...) {
			if(isDealerIDToken(token)) {
				return TOK_DEALER_ID;
			}else if(isCommodityToken(token)) {
				return TOK_COMMODITY;
			}else if(isCommandToken(token)) {
				return TOK_COMMAND;				
			}else if(isSideToken(token)) {
				return TOK_SIDE;
			}
		}
	}
	return -1;
}

string GetCurrentToken() {
	return currentToken;
}

bool isDealerIDToken(string token) {
	for(auto it = DEALER_ID_TOKENS.begin(); it != DEALER_ID_TOKENS.end(); ++it) {
		if(token == *it) {
			return true;
		}
	}

	return false;
}

bool isCommodityToken(string token) {
	for(auto it = COMMODITY_TOKENS.begin(); it != COMMODITY_TOKENS.end(); ++it) {
		if(token == *it) {
			return true;
		}
	}
	return false;
}

bool isCommandToken(string token) {
	for(auto it = COMMAND_TOKENS.begin(); it != COMMAND_TOKENS.end(); ++it) {
		if(*it == token) {
			return true;
		}
	}
	return false;
}

bool isSideToken(string token) {
        for(auto it = SIDE_TOKENS.begin(); it != SIDE_TOKENS.end(); ++it) {
		if(*it == token) {
			return true;
		}
	}
	return false;
}
