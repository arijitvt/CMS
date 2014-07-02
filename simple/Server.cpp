#include <Server.h>
                                                                                                                                                            
Session::Session(ios_ptr ios,MarketPtr market) : _ios(ios),_socket(new tcp::socket(*ios)),_market(market) {
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
		parser.doParse(buf);
		string msg = "Arijit Chattopadhyay";
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


//----------------------------------------------------------------------------------------------------

Server::Server(ios_ptr ios, boost::shared_ptr<tcp::endpoint> ep) :_ios(ios) ,
			_acceptor(new tcp::acceptor(*_ios,*ep)) {
				market = MarketPlace::getMarketPlaceSingleton();
				start_server();
}


void Server::start_server() {
	boost::shared_ptr<Session>  session(new Session(_ios,market));
 	_acceptor->async_accept(*session->get_socket(),
			boost::bind(&Server::accept_handler,this,
				boost::asio::placeholders::error,session));
}


void Server::accept_handler(const boost::system::error_code &ec,boost::shared_ptr<Session> session) {
	cout<<"Accepting connect"<<endl;
	if(!ec) {
		session->start();
	}
	start_server();
}


//----------------------------------------------------------------------------------------------------
