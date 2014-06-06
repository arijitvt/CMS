#ifndef LEXER_HH
#define LEXER_HH


#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>
#include <array>
using namespace std;


typedef enum {

	TOK_INTEGER,
	TOK_DOUBLE,
	TOK_DEALER_ID,
	TOK_COMMODITY,
	TOK_COMMAND,
	TOK_SIDE

}Tokens;

static array<string,10> DEALER_ID_TOKENS 	= {"DB","JPM","UBS","RBC","BARX","MS","CITI","BOFA","RBS","HSBC"};
static array<string,5>  COMMODITY_TOKENS 	= {"GOLD","SILV","PORK","OIL","RICE"};
static array<string,4>  COMMAND_TOKENS 		= {"POST","REVOKE","LIST","AGGRESS"};
static array<string,2>  SIDE_TOKENS 		= {"BUY","SELL"};

static stringstream ss;
static string currentToken;

/**
 * Internal Functions
 */
bool isDealerIDToken(string token) ;
bool isCommodityToken(string token) ;
bool isCommandToken(string token);
bool isSideToken(string token);
  

/**
 * Api
 */
int GetToken(string token);
string GetCurrentToken();


#endif
