#ifndef SERVER_H
#define SERVER_H


#include <Session.h>

#define PORT 7000

/** 
 * This is the Server class.
 */
class Server {

	public:
		/**                
		 * This server constructor should be called when the server has 
		 * to be launched in the  single threaded mode.
		 * @param ios , io_service shared pointer.
		 * @param ep , endpoint shared pointer.
		 */
		Server(ios_ptr ios,boost::shared_ptr<tcp::endpoint> ep);
		/**
		 * This server constructor has to be called when it is needed to
		 * launch the server in the multi-threaded mode. By default it will
		 * create 10 threades in the pool.
		 * @param ios , io_service shared pointer.
		 * @param ep , endpoint shared pointer.
		 * @param thread_count ,  this denotes the number of the thread pool should
		 * be present in the system. By default this value is 10.
		 */
		Server(ios_ptr ios,boost::shared_ptr<tcp::endpoint> ep,bool multi_threaded, int thread_count= 10);

		/**
		 * Destructor of the server.
		 */
		~Server();

		/** This method will actually start the server by creating a new session.
		 * Thus every thread will get a new session for them, listening to the same port.
		 */
		void start_server() ;

	private:

		/** This function will get called once the sever accepts a  new connection from the client.
		 * This will inialize the session and session will eventually calls the parser,which will make
		 * the interpreter to execute the commands.
		 */
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
