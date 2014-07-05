#ifndef ORDER_INFO_HH
#define ORDER_INFO_HH

#include <string>
#include <iostream>
#include <vector>
using namespace std;

#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/lockfree/queue.hpp>

#include <Commodity.h>

class OrderInfo {
	public:
		OrderInfo(int id,string did,string side,
				double price,vector<CommodityPtr> item_list);
		void insert_item_into_order(CommodityPtr item);		
		void insert_item_into_order(vector<CommodityPtr> item_list);
		bool remove_item_from_order(CommodityPtr item);
		bool remove_item_from_order(int amount);

		int get_order_id();
		string get_dealer_id();
		string get_commodity_side();
		double get_commodity_price();
		int get_commodity_list_size();
		string get_commodity_name();

		string to_string();

	private:
		int _order_id;
		string _dealer_id;
		string _side;
		double _price;
		boost::mutex _order_info_lock;
		vector<CommodityPtr> _commodity_list;
};


typedef boost::shared_ptr<OrderInfo> OrderInfoPtr;


#endif
