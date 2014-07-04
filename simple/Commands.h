#ifndef COMMANDS_HH
#define COMMANDS_HH


#include <iostream>
#include <string>
#include <vector>
#include <cstdarg>
using namespace std;

#include <MarketPlace.h>

class MarketPlace;
typedef boost::shared_ptr<MarketPlace> MarketPtr;

class Command {

	protected:
		string success_string;
		string failure_string;

	public:	
		Command(string suc_string,string fail_string);
		virtual ~Command();
		virtual string execute(MarketPtr market,string dealer_id) = 0;
};

class PostCommand:public Command {
	public:
		explicit PostCommand(string,string,int ,double);
		virtual string execute(MarketPtr market,string dealer_id);


		string get_buy_or_sell();
		string get_commodity_name();
		int get_commodity_amount();
		double get_commodity_price();

	private:
		string buyOrSell;
		string commodityName;
		int commodityAmount;
		double commodityPrice;

};

class RevokeCommand:public Command {
  	public:
		explicit RevokeCommand(int id);
		virtual string execute(MarketPtr market,string dealer_id);

	private:                                                            
		int orderId;
};


class CheckCommand: public Command {
	public:
		explicit CheckCommand(int id);
		string execute(MarketPtr market, string dealer_id);

	private:
		int _order_id;
};


class ListCommand:public Command {
	public:
		ListCommand();
		ListCommand(string);
		ListCommand(string,string);
		string execute(MarketPtr market,string dealer_id);

	private:
		string commodityName;
		string filter_dealer_id;

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
		string execute(MarketPtr market,string dealer_id);


	private:

		vector<APair> apairList;

};

#endif
