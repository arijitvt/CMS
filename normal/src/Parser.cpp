#include <Parser.h>

Parser::Parser() {

	cout<<"This is parser"<<endl;
}

ExpAST::~ExpAST () {}

PostAST::PostAST() {
	cout<<"This is Post Command AST builder"<<endl;
}


RevokeAST::RevokeAST() {
	cout<<"This is the Revoke command AST builder "<<endl;
}
