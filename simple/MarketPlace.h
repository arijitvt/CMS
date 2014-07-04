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


#include <Commodity.h>
#include <Commands.h>
#include <OrderInfo.h>

class PostCommand;
class OrderInfo;

typedef boost::shared_ptr<OrderInfo> OrderInfoPtr;

class MarketPlace {
	public:
		static boost::shared_ptr<MarketPlace> getMarketPlaceSingleton();		
		OrderInfoPtr sale_commodity(PostCommand command,string dealer_id);
		OrderInfoPtr buy_commodity(PostCommand command,string dealer_id);
		OrderInfoPtr cancel_order(int order_id,string dealer_id);
		OrderInfoPtr check_order(int order_id,string dealer_id);

		vector<OrderInfoPtr> get_order_list();

		OrderInfoPtr aggress_order(int order_id,int amount);

	private:
		MarketPlace();
		MarketPlace(MarketPlace const&); // Copy constructor overloaded
		void operator=(MarketPlace const&);// = operator overloaded

		static void init_commodity_store();
		static int gen_order_id();

	private:
		static boost::shared_ptr<MarketPlace> singleObj;
		static boost::mutex mtx;
		static int order_id;

		//vector<CommodityPtr> commodity_store;
		vector<OrderInfoPtr> order_list;
};

typedef boost::shared_ptr<MarketPlace> MarketPtr;

#endif

