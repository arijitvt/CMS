#include <Server.h>


int main() {
	try {
		ios_ptr ios(new boost::asio::io_service);
		boost::shared_ptr<tcp::endpoint> ep(new tcp::endpoint(tcp::v4(),PORT));
		Server server(ios,ep);
		server.start_server();
		ios->run();
	
	}catch(exception &ex) {
		cout<<ex.what()<<endl;
	}
}
