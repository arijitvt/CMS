#include <MarketPlace.h>


MarketPlace::MarketPlace() {

}

MarketPlace* MarketPlace::getMarketPlaceSingleton() {
        boost::lock_guard<boost::mutex>guard(mtx);
	if(singleObj == NULL) {
		singleObj = new MarketPlace;
	}
	return singleObj;
}                                            

MarketPlace *MarketPlace::singleObj = NULL;
boost::mutex MarketPlace::mtx;
