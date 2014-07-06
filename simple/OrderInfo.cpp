#include <OrderInfo.h>


OrderInfo::OrderInfo(int  id, string did, string side,double price,
		vector<CommodityPtr> item_list) 
	:_order_id(id),_dealer_id(did),_price(price), 
	_commodity_name((*item_list.begin())->get_name()),
	_side(side),
		_commodity_list(item_list.begin(), item_list.end()) {
	
}

void OrderInfo::insert_item_into_order(CommodityPtr item) {
	_order_info_lock.lock();
	_commodity_list.push_back(item);
	_order_info_lock.unlock();
}

void OrderInfo::insert_item_into_order(vector<CommodityPtr> item_list) {
	for(auto item : item_list) {
		_order_info_lock.lock();
		_commodity_list.push_back(item);
		_order_info_lock.unlock();
	}
}

bool OrderInfo::remove_item_from_order(CommodityPtr item) {
	for(vector<CommodityPtr>::iterator itr = _commodity_list.begin();
			itr != _commodity_list.end(); ++itr) {
		if(*itr == item) {
		        _order_info_lock.lock();
			_commodity_list.erase(itr);
			_order_info_lock.unlock();
     			return true;
		}
	}


	return false;
}       

bool OrderInfo::remove_item_from_order(int amount) {
	if( _commodity_list.size() < amount)                                        
		return false;
	size_t sz = _commodity_list.size();
	_order_info_lock.lock();
	_commodity_list.resize(_commodity_list.size()-amount);
	_order_info_lock.unlock();

	//int i = 0;
	//for( vector<CommodityPtr>::iterator itr = _commodity_list.begin();
	//		i < amount && itr != _commodity_list.end() ; ++i,++itr) {
	//	//_commodity_list.pop();
	//	_commodity_list.erase(itr);
	//	cout<<"Count :"<<i<<endl;
	//}
}

int OrderInfo::get_order_id() {
	return _order_id;
}

string OrderInfo::get_dealer_id() {
	return _dealer_id;
}

int OrderInfo::get_commodity_list_size() {                          
	return _commodity_list.size();
}

string OrderInfo::get_commodity_side() {
	return _side;
}

double OrderInfo::get_commodity_price() {
	return _price;
}

string OrderInfo::get_commodity_name() {
//	return _commodity_list[0]->get_name();
	return _commodity_name;
}

string OrderInfo::to_string() {
	//_order_info_lock.lock();
	string output = boost::lexical_cast<string>(_order_id)+
			" "+
			_dealer_id+
			" "+
			_side+
			" "+
			_commodity_name+
			//_commodity_list[0]->get_name()+
			" "+
			boost::lexical_cast<string>(_commodity_list.size())+
			" "+
			boost::lexical_cast<string>(_commodity_list[0]->get_price());
	//_order_info_lock.unlock();
	return output;
}
