#ifndef COMMANDS_HH
#define COMMANDS_HH


#include <iostream>
#include <string>
#include <vector>
#include <cstdarg>
using namespace std;

#include <MarketPlace.h>



class Command {

	public:	
		virtual ~Command();
		virtual int execute(MarketPtr market) = 0;
};

class PostCommand:public Command {
	public:
		explicit PostCommand(string,string,int ,double);
		int execute(MarketPtr market);

	private:
		string buyOrSell;
		string commodityName;
		int commodityAmount;
		double commodityPrice;
};

class RevokeCommand:public Command {
  	public:
		explicit RevokeCommand(int id);
		int execute(MarketPtr market);

	private:
		int orderId;
};


class ListCommand:public Command {
	public:
		ListCommand();
		ListCommand(string);
		ListCommand(string,string);
		int execute(MarketPtr market);

	private:
		string commodityName;
		string dealerId;

};

class AggressCommand:public Command {
	public:
		struct APair{
			int orderId;
			int amount;
		} ;
		typedef struct APair APair;

	public:
		AggressCommand(int numOfArgs,...);
		AggressCommand(vector<APair> apArg);
		int execute(MarketPtr market);


	private:

		vector<APair> apairList;

};

#endif
