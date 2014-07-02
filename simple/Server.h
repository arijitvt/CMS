#ifndef SERVER_H
#define SERVER_H


#include <iostream>
#include <string>

using namespace std;



#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>


using boost::asio::ip::tcp;


#define PORT 7000


typedef boost::shared_ptr<boost::asio::io_service> ios_ptr;

class Session:public boost::enable_shared_from_this<Session> {
	public:
		Session(ios_ptr ios);
		void start();
		boost::shared_ptr<tcp::socket> get_socket();

	private: //Private methods
		void read_handler(const boost::system::error_code &ec, size_t data_transferred);
		void write_handler(const boost::system::error_code &ec,size_t data_transferred);

	private: //Private variables
		boost::shared_ptr<tcp::socket> _socket;
		ios_ptr _ios;
		enum {max_msg_len = 1024};
		char buf[max_msg_len];

};


class Server {

	public:
		Server(ios_ptr ios,boost::shared_ptr<tcp::endpoint> ep);
		void start_server() ;

	private:
		void accept_handler(const boost::system::error_code &ec,boost::shared_ptr<Session> session);

	private:
		ios_ptr _ios;
		boost::shared_ptr<tcp::acceptor> _acceptor;

};


#endif
