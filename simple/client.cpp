#include <iostream>
#include <string>

using namespace std;

#include <boost/lexical_cast.hpp>

#include <Server.h>


int main() {
	boost::asio::io_service ios;
	tcp::resolver resolver(ios);
	tcp::resolver::query query(tcp::v4(),"localhost","7000");
	tcp::resolver::iterator itr = resolver.resolve(query);
	
	tcp::socket socket(ios);
	
	boost::asio::connect(socket,itr);

	string msg="This is the test message";
	boost::asio::write(socket,boost::asio::buffer(msg,msg.size()));


	char buf[1024] = {0};
	int size = socket.read_some(boost::asio::buffer(buf,1024)) ;
	cout<<"Size : " <<size<<endl;
	cout<<buf<<endl;


	return 0;
}