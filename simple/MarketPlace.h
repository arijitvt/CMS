#ifndef MARKET_PLACE_HH
#define MARKET_PLACE_HH

#include <iostream>
#include <map>
#include <vector>
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
		int sale_commodity(PostCommand command);
		int buy_commodity(PostCommand command);
		int cancel_order(int order_id);

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

		vector<CommodityPtr> commodity_store;
		vector<OrderInfoPtr> order_list;
};

typedef boost::shared_ptr<MarketPlace> MarketPtr;

#endif

