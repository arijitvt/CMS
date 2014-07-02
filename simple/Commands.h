#ifndef COMMANDS_HH
#define COMMANDS_HH


#include <iostream>
#include <string>
#include <vector>
#include <cstdarg>
using namespace std;

#include <MarketPlace.h>



class Command {

	protected:
		string success_string;
		string failure_string;

	public:	
		Command(string suc_string,string fail_string);
		virtual ~Command();
		virtual string execute(MarketPtr market) = 0;
};

class PostCommand:public Command {
	public:
		explicit PostCommand(string,string,int ,double);
		string execute(MarketPtr market);

	private:
		string buyOrSell;
		string commodityName;
		int commodityAmount;
		double commodityPrice;

};

class RevokeCommand:public Command {
  	public:
		explicit RevokeCommand(int id);
		string execute(MarketPtr market);

	private:
		int orderId;
};


class ListCommand:public Command {
	public:
		ListCommand();
		ListCommand(string);
		ListCommand(string,string);
		string execute(MarketPtr market);

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
		string execute(MarketPtr market);


	private:

		vector<APair> apairList;

};

#endif
