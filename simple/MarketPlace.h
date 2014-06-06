#ifndef MARKET_PLACE_HH
#define MARKET_PLACE_HH

#include <iostream>
using namespace std;

#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_guard.hpp>


class MarketPlace {
	public:
		static MarketPlace* getMarketPlaceSingleton();
	private:
		MarketPlace();
		MarketPlace(MarketPlace const&); // Copy constructor overloaded
		void operator=(MarketPlace const&);// = operator overloaded

	private:
		static MarketPlace *singleObj;
		static boost::mutex mtx;
};

#endif

