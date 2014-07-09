#ifndef SESSION_H
#define SESSION_H

#include <iostream>
#include <string>

using namespace std;



#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

using boost::asio::ip::tcp;



#include <MarketPlace.h>
#include <Parser.h>

typedef boost::shared_ptr<boost::asio::io_service> ios_ptr;
 
class Session:public boost::enable_shared_from_this<Session> {
	public:
		Session(ios_ptr ios,MarketPtr market);
		~Session();
		void start();
		boost::shared_ptr<tcp::socket> get_socket();

	private: //Private methods
		void read_handler(const boost::system::error_code &ec, size_t data_transferred);
		void write_handler(const boost::system::error_code &ec,size_t data_transferred);
		void clear_buffer();

	private: //Private variables
		boost::shared_ptr<tcp::socket> _socket;
		ios_ptr _ios;
		enum {max_msg_len = 1024};
		char buf[max_msg_len];
		MarketPtr _market;

};

#endif
