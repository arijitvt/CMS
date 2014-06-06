#include <Server.h>


Server::Server(io_service &ios):_acceptor(ios,tcp::endpoint(tcp::v4(),PORT)) {
	accept();
}

void Server::accept() {

}


Connection::Connection(io_service& ios):_socket(ios) {

}

shared_ptr<Connection> Connection::create(io_service &ios) {
	return pointer(new Connection(ios));
}

void Connection::start() {
	string msg = "Arijit Chattopadhyay";
	async_write(_socket,boost::asio::buffer(msg),boost::bind(&Connection::writeHandler,shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));

       // boost::asio::async_write(socket_, boost::asio::buffer(message_),
       // 		        boost::bind(&tcp_connection::handle_write, shared_from_this(),
       // 				          boost::asio::placeholders::error,
       // 					            boost::asio::placeholders::bytes_transferred));
}

void Connection::writeHandler(error_code &code, size_t dataTransferred) {

}
