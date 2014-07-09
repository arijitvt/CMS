#include <Session.h>
#include <Exceptions.h>

Session::Session(ios_ptr ios,MarketPtr market) : _ios(ios),_socket(new tcp::socket(*ios)),_market(market) {
}

Session::~Session() {
	boost::system::error_code ec;
	_socket->shutdown( boost::asio::ip::tcp::socket::shutdown_both, ec );
	_socket->close( ec );
	if(ec) {
		cout<<"Error in closing socket"<<endl;
	}
}

void Session::start() {
	_socket->async_read_some(boost::asio::buffer(buf,max_msg_len),
			boost::bind(&Session::read_handler,shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
}

void Session::read_handler(const boost::system::error_code &ec, 
				size_t data_transferred) {
	if(!ec) {
		cout<<buf<<endl;
		Parser parser(_market);
		string msg ;
		try {
			msg= parser.doParse(buf);
		} catch(CMSException &ex) {
			msg = ex.what();
		}catch(exception &ex) {
			msg = "UNKNOWN EXCEPTION";
			cout<<ex.what()<<endl;
		}
		clear_buffer();
		if(msg.size() == 0) {
			msg = "Blank Result";
		}
		boost::asio::async_write(*_socket,boost::asio::buffer(msg,msg.size()),
				boost::bind(&Session::write_handler,shared_from_this(),
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
	}
}


void Session::write_handler(const boost::system::error_code &ec, 
				size_t data_transferred) {
	if(!ec) {
		start();
	}

}


boost::shared_ptr<tcp::socket>  Session::get_socket() {
	return _socket;
}


void Session::clear_buffer() {
	memset(buf,0,max_msg_len);
}

