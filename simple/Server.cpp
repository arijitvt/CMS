#include <Server.h>
#include <Exceptions.h>
                                                                                                                                                            
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
		string msg ;
		try {
			msg= parser.doParse(buf);
		} catch(CMSException &ex) {
			msg = ex.what();
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

//----------------------------------------------------------------------------------------------------

Server::Server(ios_ptr ios, boost::shared_ptr<tcp::endpoint> ep) :_ios(ios) ,
			_acceptor(new tcp::acceptor(*_ios,*ep)) ,
			_multi_threaded(false) {
				market = MarketPlace::getMarketPlaceSingleton();
				start_server();
}


Server::Server(ios_ptr ios,boost::shared_ptr<tcp::endpoint> ep,bool multi_threaded, int thread_count = 10) {
	if(!multi_threaded) {
		//No Need to create multiple threads
		Server(ios, ep);
	}else {
		for(int  i = 0 ; i < thread_count; ++i) {
			//Every thread will get their own session
			worker_threads.create_thread(boost::bind(&Server::start_server,this));
		}
		worker_threads.join_all();
	}
}


void Server::start_server() {
	boost::shared_ptr<Session>  session(new Session(_ios,market));
 	_acceptor->async_accept(*session->get_socket(),
			boost::bind(&Server::accept_handler,this,
				boost::asio::placeholders::error,session));
	if(_multi_threaded)
		_ios->run();
}


void Server::accept_handler(const boost::system::error_code &ec,boost::shared_ptr<Session> session) {
	cout<<"Accepting connection"<<endl;
	if(!ec) {
		session->start();
	}
	start_server();
}


//----------------------------------------------------------------------------------------------------
