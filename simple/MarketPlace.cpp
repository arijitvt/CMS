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

//int MarketPlace::sell_commodity(string commodity_name,double commodity_price,int amount) {
int MarketPlace::sale_commodity(PostCommand command) {
	assert(command.get_buy_or_sell() == "SELL");
	vector<CommodityPtr> coms;
	int o_id = gen_order_id();
	int amount = command.get_commodity_amount();
	vector<CommodityPtr> com_list;
	for(int i   = 0 ;  i < amount; ++i) {
		CommodityPtr commodity(new Commodity(
							command.get_commodity_name(),
								command.get_commodity_price(),true));

		commodity_store.push_back(commodity);
		com_list.push_back(commodity);
	}

	boost::shared_ptr<OrderInfo> order(new OrderInfo(o_id,"",com_list));
	order_list.push_back(order);
	return o_id;
}


int MarketPlace::buy_commodity(PostCommand command) {

	assert(command.get_buy_or_sell() == "BUY");
	vector<CommodityPtr> coms;
	int o_id = gen_order_id();
	int amount = command.get_commodity_amount();
	vector<CommodityPtr> com_list;
	for(int i   = 0 ;  i < amount; ++i) {
		CommodityPtr commodity(new Commodity(
							command.get_commodity_name(),
								command.get_commodity_price(),false));

		commodity_store.push_back(commodity);
		com_list.push_back(commodity);
	}

	boost::shared_ptr<OrderInfo> order(new OrderInfo(o_id,"",com_list));
	order_list.push_back(order);
	return o_id;
}




boost::shared_ptr<MarketPlace> MarketPlace::singleObj = NULL;
boost::mutex MarketPlace::mtx;
int MarketPlace::order_id = 0 ;
