#include <Commodity.h>

Commodity::Commodity(string name,double price,bool b_o_s)
	: _name(name), _price(price),_buy_or_sell(b_o_s) {

}

string Commodity::get_name() {
	return _name;
}

void Commodity::set_name(string name) {
	_name = name;
}

double Commodity::get_price() {
	return _price;
}

void Commodity::set_price(double price) {
	_price = price;
}

bool Commodity::is_buy() {
	if(!_buy_or_sell) return true;
	return false;
}

bool Commodity::is_sell() {
	if(_buy_or_sell) return true;
	return false;
}
