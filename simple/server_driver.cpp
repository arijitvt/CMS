#include <iostream>
using namespace std;

//#include <boost/asio.hpp>
//#include <boost/shared_ptr.hpp>
//using boost::asio::ip::tcp;
//
//typedef boost::shared_ptr<boost::asio::io_service> ios_ptr;
//

#include  <Server.h>

int main() {
	try {
		ios_ptr ios(new boost::asio::io_service);
		boost::shared_ptr<tcp::endpoint> ep(new tcp::endpoint(tcp::v4(),PORT));
		Server server(ios,ep);
		ios->run();
	
	}catch(exception &ex) {
		cout<<ex.what()<<endl;
	}
}
