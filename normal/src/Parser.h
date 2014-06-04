#ifndef PARSER_HH
#define PARSER_HH

#include <iostream>
#include <string>
using namespace std;


class Parser {
	public:
		explicit Parser();

	private:
		string inputFileName;
		const string tokenRepo;

};

class ExpAST {
	public:
		virtual ~ExpAST();
};

class PostAST:public ExpAST {
	public:
		PostAST();

};

class RevokeAST:public ExpAST {
	public:
		RevokeAST();

	private:
		bool buyOrSell;

};


#endif
