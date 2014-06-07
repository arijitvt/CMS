#include <Server.h>

//This test function is the test code.
//void test(const boost::system::error_code &code, size_t dataTransferred) {
void test(const boost::system::error_code &code) {

}

Server::Server(io_service &ios):_acceptor(ios,tcp::endpoint(tcp::v4(),PORT)) {
	accept();
}

void Server::accept() {
	Connection::pointer new_connection = Connection::create(_acceptor.get_io_service());
	_acceptor.async_accept(new_connection->getSocket(),
			bind(&Server::serverWriteHandler,this,new_connection,boost::asio::placeholders::error));
}

void Server::serverWriteHandler(Connection::pointer connection,const error_code &code) {
	if(!code) {
		cout<<"Inside "<<endl;
		connection->start();
	}
	accept();
}


Connection::Connection(io_service& ios):_socket(ios) {

}

shared_ptr<Connection> Connection::create(io_service &ios) {
	return pointer(new Connection(ios));
}

void Connection::start() {
	string msg = "Arijit Chattopadhyay";
	boost::asio::async_write(_socket,boost::asio::buffer(msg),
	boost::bind(&Connection::writeHandler,
			shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void Connection::writeHandler(const boost::system::error_code &code, size_t dataTransferred) {
	cout<<"Byte tranferred "<<dataTransferred<<endl;
}

tcp::socket& Connection::getSocket() {
	return _socket;
}
