#ifndef MARKET_PLACE_HH
#define MARKET_PLACE_HH

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_guard.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/atomic.hpp>


#include <Commodity.h>
#include <Commands.h>
#include <OrderInfo.h>
#include <Exceptions.h>
#include <ErrorMsgs.h>

class PostCommand;
class OrderInfo;

typedef boost::shared_ptr<OrderInfo> OrderInfoPtr;

/**
 * This is the central class which holds all the functionalities of the Market Place.
 * @see Parser and Commands, which call the various api of this class to do the transaction.
 * There only one instation of this class should be there in the system.
 * So the implementation follows a standard design implementation paradigm.
 */

class MarketPlace {
	public:
		/**
		 * Returs the single object of the Marketplace.
		 * This implementation is thread safe.
		 */
		static boost::shared_ptr<MarketPlace> getMarketPlaceSingleton();		
		/**
		 * Call this api if you want to sell the Commodity.
		 * @param command , is poperly populated Command object.
		 * @param delear_id , holds the name of the dealer doing the transaction.
		 */
		OrderInfoPtr sale_commodity(PostCommand command,string dealer_id);
		/**
		 * Call this api if you want to buy the Commodity.
		 * @param command , is a poperly populated Commoand Object.
		 * @param dealer_id , is the name of the dealer doing the transaction.
		 */
		OrderInfoPtr buy_commodity(PostCommand command,string dealer_id);
		/**
		 * Call this api to cancel the Order.
		 * @param order_id , holds the id of the order.
		 * @param dealer_id , is the name of the dealer doing the transaction.
		 */
		OrderInfoPtr cancel_order(int order_id,string dealer_id);
		/**
		 * Checks the status of the order.
		 * It throws CMSException if an illegal access is being done.
		 * @param order_id , id the order.
		 * @param dealer_id , holds the name of the dealer who has created the transaction. 
		 * So that we can catch the illegal execution.
		 */
		OrderInfoPtr check_order(int order_id,string dealer_id);
		/**
		 * The the list of the order currently present in the system.
		 */
		vector<OrderInfoPtr> get_order_list();
                /**
		 * This function does the aggression.
		 * @param order_id , id information of the order.
		 * @param amount , # of the Commodity should take part in the transaction.
		 */
		OrderInfoPtr aggress_order(int order_id,int amount);

	private:
		/**
		 * Default constructor.
		 * Private for singleton.
		 */
		MarketPlace();
		/**
		 * Copy constructor overloaded for singleton.
		 */
		MarketPlace(MarketPlace const&); 
		/** Operator overloaded for singleton implementation.
		 */
		void operator=(MarketPlace const&);

		static void init_commodity_store();
		static int gen_order_id();

	private:
		static boost::shared_ptr<MarketPlace> singleObj;
		static boost::mutex mtx;
		static int order_id;
		//boost::atomic_int order_id;

		//vector<CommodityPtr> commodity_store;
		vector<OrderInfoPtr> order_list;
};

typedef boost::shared_ptr<MarketPlace> MarketPtr;

#endif

