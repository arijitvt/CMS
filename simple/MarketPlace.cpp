#include <MarketPlace.h>


MarketPlace::MarketPlace() {

}

boost::shared_ptr<MarketPlace> MarketPlace::getMarketPlaceSingleton() {
        boost::lock_guard<boost::mutex>guard(mtx);
	if(singleObj == NULL) {
		singleObj = boost::shared_ptr<MarketPlace>(new MarketPlace);
	}
	return singleObj;
}                                            

boost::shared_ptr<MarketPlace> MarketPlace::singleObj = NULL;
boost::mutex MarketPlace::mtx;
