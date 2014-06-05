#include <Parser.h>
#include <Lexer.h>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
using namespace boost;


#include <cassert>


void Parser::doParse() {
	while(1) {
		string s ;
		while(getline(cin,s)) {
			if(s == "STOP") 
				return;

			tokenizeLine(s);
			int tokenType = GetToken(tokenStore[0]);
			assert(tokenType == Tokens::TOK_DEALER_ID);
			tokenType = GetToken(tokenStore[1]);
			assert(tokenType == Tokens::TOK_COMMAND); 
			string token = GetCurrentToken();
			Command *command;
			if(token == "POST") {
				assert(tokenStore.size() == 6);
				//Get the Buy_Or_Sell Token
				tokenType= GetToken(tokenStore[2]);
				assert(tokenType == Tokens::TOK_SIDE);
                                string buyOrSell = GetCurrentToken();
				
				//Get the Commodity Name
				tokenType = GetToken(tokenStore[3]);
				assert(tokenType == Tokens::TOK_COMMODITY);
				string commodityName = GetCurrentToken();

				//Get the Amount of the Commodity
				tokenType = GetToken(tokenStore[4]);
				assert(tokenType == Tokens::TOK_INTEGER);
				int amount = boost::lexical_cast<int>(GetCurrentToken());

				//Get the Price
				tokenType = GetToken(tokenStore[5]);
				assert(tokenType = Tokens::TOK_DOUBLE);
				double price = boost::lexical_cast<double>(GetCurrentToken());

				command = new PostCommand(buyOrSell,commodityName,amount,price);
			
			}else if(token == "REVOKE") {
			
			}else if(token == "LIST") {
			
			}else if (token == "AGGRESS") {			
			
			}else {
				assert(0);
			}

                        command->execute();

#ifdef DEBUG
			for(auto tok : tokenStore) {
				GetToken(tok);
			}
#endif
		}
	}
}        

void Parser::tokenizeLine(string inputLine) {
	tokenStore.clear();
	char_separator<char> sep(" ");
	tokenizer<char_separator<char>> tokens(inputLine, sep);
	for(auto s : tokens) {
		tokenStore.push_back(s);
	}

	assert(tokenStore.size() >= 2);
}                                                                                                               
