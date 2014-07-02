#ifndef MARKET_PLACE_HH
#define MARKET_PLACE_HH

#include <iostream>
using namespace std;

#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_guard.hpp>
#include <boost/shared_ptr.hpp>


class MarketPlace {
	public:
		static boost::shared_ptr<MarketPlace> getMarketPlaceSingleton();
	private:
		MarketPlace();
		MarketPlace(MarketPlace const&); // Copy constructor overloaded
		void operator=(MarketPlace const&);// = operator overloaded

	private:
		static boost::shared_ptr<MarketPlace> singleObj;
		static boost::mutex mtx;
};

typedef boost::shared_ptr<MarketPlace> MarketPtr;

#endif

