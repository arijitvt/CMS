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



/**
 * This class stores the information about the individual Order.
 */
class OrderInfo {
	public:
		/** Constructor for the OrderInfo class
		 * @param id , id of the order.
		 * @param side , whether to buy or sell order
		 * @param price , price of the Commodity
		 * @param item_list , list of the Commodities
		 */
		OrderInfo(int id,string did,string side,
				double price,vector<CommodityPtr> item_list);

		/**
		 * Insert single Commodity into the order
		 * @param item , ptr to the Commodity
		 */
		void insert_item_into_order(CommodityPtr item);		

		/**
		 * Insert multiple Commodities to the order
		 * @param item_list , list of the Commodities.
		 */		
		void insert_item_into_order(vector<CommodityPtr> item_list);

		/**
		 * Remove single item from the order list.
		 */
		bool remove_item_from_order(CommodityPtr item);
		/**
		 * Remove the number of the Commodities.
		 * @param amount, # of Commodities to be removed from the order.
		 */
		bool remove_item_from_order(int amount);

		/**
		 * Returns the id of the order.
		 */
		int get_order_id();
		/** Returns the dealer id information.
		 */
		string get_dealer_id();
		/** Returns the side i.e. to buy or sell 
		 * for the Order.
		 */
		string get_commodity_side();
		/** 
		 * Returns the price of the Commodity
		 */
		double get_commodity_price();
		/** Returns the commodity number in the order.
		 */
		int get_commodity_list_size();
		/**
		 * Returns the name of the Commodity.
		 */
		string get_commodity_name();
               /**
		* Returns the string representation of the Order information.
		*/
		string to_string();

	private:
		int _order_id;
		string _dealer_id;
		string _side;
		double _price;
		string _commodity_name;
		boost::mutex _order_info_lock;
		vector<CommodityPtr> _commodity_list;
};


typedef boost::shared_ptr<OrderInfo> OrderInfoPtr;


#endif
