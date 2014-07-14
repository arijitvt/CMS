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

/** This is the implementation of the Parser.
 */

class Parser {
	public:
		/**
		 * Default constructor of the Parser.
		 * @param market , is the single object of the MarketPlace.
		 */
		Parser(MarketPtr market);
		/** 
		 * This function does the parsing for the base mode operation.
		 */
		void doParse() ;
		/**
		 * This function does the parsing the ext1 and ext2 mode.
		 * @param command , is the name of the command.
		 */
		string doParse(string command);
                                                                          

	private:
		/**
		 * Does the actual parsing work.
		 */
		string parsing(string input,bool client_only=true);
		/**
		 * tokenize the line, sent to it.
		 */
		void tokenizeLine(string);

	private: //These are the private variables
		vector<string> tokenStore;
		MarketPtr _market;

};

#endif
