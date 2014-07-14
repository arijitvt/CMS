#ifndef COMMANDS_HH
#define COMMANDS_HH


#include <iostream>
#include <string>
#include <vector>
#include <cstdarg>
using namespace std;

#include <MarketPlace.h>
#include <Exceptions.h>
#include <ErrorMsgs.h>

//Forward declaration
class MarketPlace;

/*! \var MarketPtr
 *  \brief This is the shared pointer for the Marketplace for automatic garbage collection.
 */
typedef boost::shared_ptr<MarketPlace> MarketPtr;

/** The Base class for all the diffent types of commands.
 *  All Respective command should extend this and implement the 
 *  execute function.
 */
class Command {

	protected:
		string success_string; ///< This string will contain the success info for the execute function
		string failure_string; ///< This string will contain the failure info fot the execute function

	public:	
		/** The basic constructor
		 */
		Command(string suc_string,string fail_string);
		/** The empty virtual destructor. This should be there
		 * to destroy an obj being deleted by other types extened class obj.
		 */
		virtual ~Command();
		/**  A pure virtual function for all the commands.
		 */
		virtual string execute(MarketPtr market,string dealer_id) = 0;
};

/** Post command implementation classs
 */
class PostCommand:public Command {
	public:
		/**
		 * Post command constructor.
		 * @param side  holds the string BUY/SELL
		 * @param cName holds the Commodity Name
		 * @param amt holds the amount of the commodity to be traded.
		 * @param prc holds the price at which the commodity will be traded.
		 */
		explicit PostCommand(string side, string cName,int amt,double prc);
		/**
		 * Implementation of the virtual execute function
		 * @param market holds the singleton object of MarketPlace
		 * @param dealer_id holds the Dealer Id string.
		 */
		virtual string execute(MarketPtr market,string dealer_id);
	

		/**
		 * Returns the side of the Commodity side
		 */
		string get_buy_or_sell();
		/**
		 * Returns the Commodity name
		 */
		string get_commodity_name();
		/**
		 * Return the Commodity amount
		 */
		int get_commodity_amount();
		/**
		 * Returns the Commodity Price
		 */
		double get_commodity_price();

	private:
		string buyOrSell;
		string commodityName;
		int commodityAmount;
		double commodityPrice;

};

class RevokeCommand:public Command {
  	public:
		/** Revoke command constructor.
		 * @param id holds the id of the order to be revoked
		 */
		explicit RevokeCommand(int id);
		/** Implementation of the virtual execute function
		 */
		virtual string execute(MarketPtr market,string dealer_id);

	private:                                                            
		int orderId;
};


class CheckCommand: public Command {
	public:
		/** Constructor for the Check command.
		 * @param id holds the id of the order, for which the customer
		 * is enquiring.
		 */
		explicit CheckCommand(int id);
		/** Implementation of the execute function.
		 */
		string execute(MarketPtr market, string dealer_id);

	private:
		int _order_id;
};


class ListCommand:public Command {
	public:
		/** 
		 * List command default constructor without any filter
		 */
		ListCommand();
		/**
		 * List Command with Commodity Name filter
		 */
		ListCommand(string);
		/**
		 * List Command with Commodity Name and Dealer Id filter
		 */
		ListCommand(string,string);
		/**
		 * Implementation of the execute function.
		 */
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
		/**
		 * Aggress Command constructor with variable argument approach
		 */
		AggressCommand(int numOfArgs,...);
		/**
		 * Aggress Command constructor with variable argument approach using vector
		 */
		AggressCommand(vector<APair> apArg);
		/**
		 * Standard implementation of the execute function
		 */
		string execute(MarketPtr market,string dealer_id);


	private:

		vector<APair> apairList;

};

#endif
