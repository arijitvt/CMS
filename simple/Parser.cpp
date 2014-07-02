#include <Parser.h>
#include <Lexer.h>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
using namespace boost;


#include <cassert>

Parser::Parser(MarketPtr market):_market(market) {

}

string Parser::doParse(string command) {
	return parsing(command);
}

void Parser::doParse() {
	while(1) {
		string s ;
		while(getline(cin,s)) {
			parsing(s);
		}
	}	
}

string Parser::parsing(string input) {
		string s =input;
		if(s == "STOP") 
			return "";

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
			assert(tokenStore.size() == 3);
			//Get the order id
			tokenType = GetToken(tokenStore[2]);
			assert(tokenType == Tokens::TOK_INTEGER);
			int id = boost::lexical_cast<int>(GetCurrentToken());

			command = new RevokeCommand(id);


		}else if(token == "LIST") {
			assert(tokenStore.size() >= 2 && tokenStore.size() <= 4 && "Illegal tokens are supplied to the list command") ;
			switch(tokenStore.size()) {
				case 2 :
					command = new ListCommand;
					break;

				case 3:  
					tokenType = GetToken(tokenStore[2]) ;
					assert(tokenType == Tokens::TOK_COMMODITY && "Token is not commodity for the list command");
					command = new ListCommand(GetCurrentToken());
					break;

				case 4: {
						tokenType = GetToken(tokenStore[2]) ;
						assert(tokenType == Tokens::TOK_COMMODITY && "Token is not commodity for the list command");
						string commodityName = GetCurrentToken();

						tokenType = GetToken(tokenStore[3]);
						assert(tokenType == Tokens::TOK_DEALER_ID && "Token is not dealer id for the list command");
						string dealerId = GetCurrentToken();

						command = new ListCommand(commodityName,dealerId);
						break;
					}

				default:
					assert(0 && "Illegal tokens for List command");
			}

		}else if (token == "AGGRESS") {			
			vector<AggressCommand::APair> argList;
			assert(tokenStore.size()>= 4 && tokenStore.size()%2 == 0 && "Illegal tokens for Aggress command");
			for(int i  = 2 ; i < tokenStore.size() ; i+=2) {

				tokenType = GetToken(tokenStore[i]);
				assert(tokenType == TOK_INTEGER && "Invalid Token for Aggress command");
				int orderId = lexical_cast<int>(GetCurrentToken());

				tokenType = GetToken(tokenStore[i+1]);
				assert(tokenType == TOK_INTEGER && "Invalid Token for Aggress command");
				int amount = lexical_cast<int>(GetCurrentToken());

				AggressCommand::APair argPair= {orderId,amount};
				argList.push_back(argPair);
			}
			command = new AggressCommand(argList);

		}else {
			assert(0 && "Invalid Command");
		}



#ifdef DEBUG
		for(auto tok : tokenStore) {
			GetToken(tok);
		}
#endif


		return command->execute(_market);
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
