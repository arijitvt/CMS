#ifndef SERVER_HH
#define SERVER_HH


#include <iostream>
#include <cstdlib>
using namespace std;

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>

using namespace boost::asio;
using boost::system::error_code;
using boost::system::system_error;
using boost::asio::ip::tcp;

class Server {
	public:
		Server(io_service& ios);

	private:
		void accept();

	private:
		ip::tcp::acceptor _acceptor;
		static const int PORT = 7000;

};


//class tcp_connection
//  : public boost::enable_shared_from_this<tcp_connection>

class Connection:public boost::enable_shared_from_this<Connection> {
	public:
		typedef shared_ptr<Connection> pointer;
		static pointer create(boost::asio::io_service &ios) ;
		void start();

        private:
        	tcp::socket _socket;

	private:
                Connection(io_service& _ios);
		void writeHandler(error_code&, size_t);
};


#endif
