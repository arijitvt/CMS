#include <iostream>
#include <string>

using namespace std;

#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>

#include <Server.h>
#include <Parser.h>
#include <MarketPlace.h>


void direct_parser_launch () {
	MarketPtr market = MarketPlace::getMarketPlaceSingleton();
	cout<<"cms>";
	Parser *p= new Parser(market);
	p->doParse();
	delete p;
}

void connect_to_multi_threaded_server() {

	boost::asio::io_service ios;
	tcp::resolver resolver(ios);
	tcp::resolver::query query(tcp::v4(),"localhost",
			boost::lexical_cast<string>(PORT).c_str());
	tcp::resolver::iterator itr = resolver.resolve(query);
	
	tcp::socket socket(ios);
	
	boost::asio::connect(socket,itr);

	string msg;
	cout<<"cms>";
	while(getline(cin,msg)) {
		boost::asio::write(socket,boost::asio::buffer(msg,msg.size()));
		char buf[1024] = {0};
		int size = socket.read_some(boost::asio::buffer(buf,1024)) ;
		cout<<buf<<endl;
		cout<<"cms>";
	}
}


int parse_prog_params(int argc, char **argv) {
	namespace po = boost::program_options;
	po::options_description desc("CMS application");
	desc.add_options()
		("help","This will print all the possible options")
		("test","This is test program");
	po::variables_map args;
	try {
		po::store(po::parse_command_line(argc,argv,desc),args);
		po::notify(args);
		if(args.count("help")) {
			cout<<"Help"<<endl;
		}else if(args.count("test")) {
                 	cout<<"This is test command"<<endl;
		}
	}catch(po::error &er) {
		cout<<er.what()<<endl;
	}catch(std::exception &ex) {
		cout<<ex.what()<<endl;
	}

	return 0;
}

int main(int argc, char **argv) {
//        parse_prog_params(argc,argv);
	connect_to_multi_threaded_server();
	return 0;
}
