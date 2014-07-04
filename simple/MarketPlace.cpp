#include <MarketPlace.h>


MarketPlace::MarketPlace() {

}

boost::shared_ptr<MarketPlace> MarketPlace::getMarketPlaceSingleton() {
        boost::lock_guard<boost::mutex>guard(mtx);
	if(singleObj == NULL) {
		MarketPlace::init_commodity_store();
		singleObj = boost::shared_ptr<MarketPlace>(new MarketPlace);
	}
	return singleObj;
}


void MarketPlace::init_commodity_store() {                                                   
}

int MarketPlace::gen_order_id() {
	return 	++order_id;
}


/** 
 * All the public methods for buying and selling the properties
 */

OrderInfoPtr MarketPlace::sale_commodity(PostCommand command,string dealer_id) {
	assert(command.get_buy_or_sell() == "SELL");
	vector<CommodityPtr> coms;
	int o_id = gen_order_id();
	int amount = command.get_commodity_amount();
	vector<CommodityPtr> com_list;
	for(int i   = 0 ;  i < amount; ++i) {
		CommodityPtr commodity(new Commodity(
							command.get_commodity_name(),
								command.get_commodity_price(),true));

		//commodity_store.push_back(commodity);
		com_list.push_back(commodity);
	}

	boost::shared_ptr<OrderInfo> order(new OrderInfo(o_id,dealer_id,
				"SELL",command.get_commodity_price(),com_list));
	order_list.push_back(order);
	return order;
}


OrderInfoPtr MarketPlace::buy_commodity(PostCommand command,string dealer_id) {
	assert(command.get_buy_or_sell() == "BUY");
	vector<CommodityPtr> coms;
	int o_id = gen_order_id();
	int amount = command.get_commodity_amount();
	vector<CommodityPtr> com_list;
	for(int i   = 0 ;  i < amount; ++i) {
		CommodityPtr commodity(new Commodity(
							command.get_commodity_name(),
								command.get_commodity_price(),false));

		//commodity_store.push_back(commodity);
		com_list.push_back(commodity);
	}

	boost::shared_ptr<OrderInfo> order(new OrderInfo(o_id,dealer_id,
				"BUY",command.get_commodity_price(),com_list));
	order_list.push_back(order);
	return order;
}

OrderInfoPtr MarketPlace::cancel_order(int order_id,string dealer_id) {
	for(vector<OrderInfoPtr>::iterator itr = order_list.begin(); 
			itr != order_list.end(); ++itr) {
		OrderInfoPtr order = *itr;
		if(order->get_order_id() == order_id &&
				order->get_dealer_id() == dealer_id) {
			order_list.erase(itr);
			return order;
		} 
	}

	return NULL;

}




boost::shared_ptr<MarketPlace> MarketPlace::singleObj = NULL;
boost::mutex MarketPlace::mtx;
int MarketPlace::order_id = 0 ;
