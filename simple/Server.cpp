#include <Server.h>
#include <Exceptions.h>
                                                                                                                                                            
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
