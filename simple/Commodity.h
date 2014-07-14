#ifndef COMMODITY_HH
#define COMMODITY_HH

#include <iostream>
#include <string>
using namespace std;

#include <boost/shared_ptr.hpp>

/**
 *  Commodity class holds the information 
 *  about the commodity
 */

class Commodity {

	public:
		/**
		 * Commodity Constructor
		 * @param name holds the name
		 * @param price holds the price
		 * @param b_o_s holds the boolean value if the commodity is to buy or to sell.
		 * This value is false to buy and true for sell
		 */
		Commodity(string name,double price,bool b_o_s);
		/**
		 * Returns Commodity Name.
		 */
		string get_name();
		/**
		 * Sets the Commodity Name.
		 */
		void set_name(string name);
		/**
		 * Returns the price of the Commodity
		 */
		double get_price();
		/**
		 * Sets the Commodity price.
		 */
		void set_price(double price);
		/**
		 * Returns true if the Commodity is to buy
		 */
		bool is_buy();
		/**
		 * Returns true if the Commodity is to sell
		 */
		bool is_sell();

	private:
		string _name;
		double _price;
		bool _buy_or_sell; // 0 to buy 1 to sell

};


typedef boost::shared_ptr<Commodity> CommodityPtr;


#endif
