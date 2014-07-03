#ifndef COMMODITY_HH
#define COMMODITY_HH

#include <iostream>
#include <string>
using namespace std;

#include <boost/shared_ptr.hpp>

class Commodity {

	public:
		Commodity(string name,double price,bool b_o_s);
		string get_name();
		void set_name(string name);
		double get_price();
		void set_price(double price);
		bool is_buy();
		bool is_sell();

	private:
		string _name;
		double _price;
		bool _buy_or_sell; // 0 to buy 1 to sell

};


typedef boost::shared_ptr<Commodity> CommodityPtr;


#endif
