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
 
/**
 * This class is the implementation of the session object.
 * Every connection will create their own session object.
 */
class Session:public boost::enable_shared_from_this<Session> {
	public:
		/** Default constructor of the session object.
		 * @param ios , io_service pointer.
		 * @param market ,  singleton object of the MarketPlace.
		 */
		Session(ios_ptr ios,MarketPtr market);
		/**
		 * Standard destructor of the session object.
		 */
		~Session();
                /**
		 * This function starts the session and registers the \fn read_handler
		 */
		void start();
		/**
		 * Returns the socket.
		 */
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
