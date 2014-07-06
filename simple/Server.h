#ifndef SERVER_H
#define SERVER_H


#include <Session.h>

#define PORT 7000





class Server {

	public:
		Server(ios_ptr ios,boost::shared_ptr<tcp::endpoint> ep);
		Server(ios_ptr ios,boost::shared_ptr<tcp::endpoint> ep,bool multi_threaded, int thread_count);
		
		void start_server() ;

	private:
		void accept_handler(const boost::system::error_code &ec,boost::shared_ptr<Session> session);

	private:
		ios_ptr _ios;
		boost::shared_ptr<tcp::acceptor> _acceptor;
		boost::thread_group worker_threads;
		boost::mutex lock;
		MarketPtr market;
		bool _multi_threaded;

};


#endif
