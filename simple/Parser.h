#ifndef PARSER_HH
#define PARSER_HH


#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

#include <Lexer.h>
#include <Commands.h>


class Parser {
	public:
		void doParse() ;

	private:
		void tokenizeLine(string);

	private: //These are the private variables
		vector<string> tokenStore;

};

#endif
