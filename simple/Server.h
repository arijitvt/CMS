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

//  : public boost::enable_shared_from_this<tcp_connection>

class Connection:public boost::enable_shared_from_this<Connection> {
	public:
		typedef shared_ptr<Connection> pointer;
		static pointer create(boost::asio::io_service &ios) ;
		void start();
		tcp::socket& getSocket();

        private:
        	tcp::socket _socket;

	private:
                Connection(io_service& _ios);
		void writeHandler(const error_code&, size_t);
};

class Server {
	public:
		Server(io_service& ios);

	private:
		void accept();
		void serverWriteHandler(Connection::pointer,const error_code&);

	private:
		ip::tcp::acceptor _acceptor;
		static const int PORT = 7000;

};



#endif
