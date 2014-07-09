#ifndef PARSER_HH
#define PARSER_HH


#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

#include <Lexer.h>
#include <Commands.h>
#include <Exceptions.h>

class Parser {
	public:
		Parser(MarketPtr market);
		void doParse() ;
		string doParse(string command);


	private:
		string parsing(string input,bool client_only=true);
		void tokenizeLine(string);

	private: //These are the private variables
		vector<string> tokenStore;
		MarketPtr _market;

};

#endif
