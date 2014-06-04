#include <Lexer.h>

int GetToken() {
	int lastChar = ' ' ;
	while(isspace(lastChar)) {
		lastChar = getchar();
	}

	if(isalpha(lastChar)) {
		string identifierString;
		ss<<(char)lastChar;
		ss>>identifierString;
		cout<<"Identifier String is : "<<identifierString<<endl;
		while(isalnum(lastChar=getchar())) {
			identifierString+=lastChar;
		}
		if(isDealerIDToken(identifierString)) {
#ifdef DEBUG
			cout<<"Dealer token : "<<identifierString<<endl;
#endif
			return TOK_DEALER_ID;
		}else if(isCommodityToken(identifierString)) {
#ifdef DEBUG
			cout<<"Commodity Token "<<identifierString<<endl;
#endif
			return TOK_COMMODITY;
		}else if (isCommandToken(identifierString)) {
#ifdef DEBUG
      		cout<<"Command Token " << identifierString<<endl;
#endif
			return TOK_COMMAND;
		}else if(isSideToken(identifierString)) {
#ifdef DEBUG
			cout<<"Side Token " <<identifierString<<endl;
#endif
			return TOK_SIDE;
		}

	}

	else if(isdigit(lastChar)) {
		string numString;
		do{
			numString+=lastChar;
			lastChar=getchar();
		}while(isdigit(lastChar) || lastChar == '.');
		cout<<"Number String " <<numString<<endl;
	}
	return 0;
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
