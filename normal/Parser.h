#ifndef PARSER_HH
#define PARSER_HH

#include <iostream>
#include <string>
using namespace std;

#include <Lexer.h>


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
	private:
		bool side;
		string commodityName;
		int amount;
		double price;		

};

class RevokeAST:public ExpAST {
	public:
		RevokeAST();

	private:
		bool side;
		int orderId;
};

class IntegerAST:public ExpAST {
	public:
		IntegerAST(int val);

	private:
		int value;
};


#endif
