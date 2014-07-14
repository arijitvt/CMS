#include <iostream>
#include <string>
#include <cassert>

using namespace std;

#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>

#include <Server.h>
#include <Parser.h>
#include <MarketPlace.h>

#include <Utility.h>



int port = -1; 	///< This will hold the port number, when client is launched
		///<  in server-client mode(ext1 or ext2)
		///< This should be same as that of the server

                                                              
/**
 * This function launches the client in the base-mode. 
 * There is no server-client mode for this. See the base documentation 
 * for more information.
 */
void direct_parser_launch () {
	MarketPtr market = MarketPlace::getMarketPlaceSingleton();
	cout<<"cms>";
	Parser *p= new Parser(market);
	p->doParse();
	delete p;
}


/**
 * This is function will connect the client to the server.
 * For both mode(ext1 & ext2) the client call is same. Because
 * the client is abstracted from the server implementation.
 */
void connect_to_server() {
        assert(port >=0 && "PORT num is not proper");
	boost::asio::io_service ios;
	tcp::resolver resolver(ios);
	tcp::resolver::query query(tcp::v4(),"localhost",
			boost::lexical_cast<string>(port).c_str());
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

/**
 * This function will parse the user provided option and launches the client 
 * accordingly. All constant strings used here  are being declared at the 
 * Utility.h as the server is also using the same string. Use the Utility for 
 * all such constant declarations. 
 * @see Utility.h
 * @param argc contains the number of the argument that the user has passed.
 * @param argv contains the rest of the arguments passed by the user.
 */
int parse_prog_params(int argc, char **argv) {
	namespace po = boost::program_options;
	po::options_description desc("CMS application");
	desc.add_options()
		("help","produce help message")
		(base_option,base_desc)
		(ext1_option,po::value<int>(),ext1_desc)
		(ext2_option,po::value<int>(),ext2_desc);
	po::variables_map args;
	try {
		po::store(po::parse_command_line(argc,argv,desc),args);
		po::notify(args);
		if(args.count("help")) {
			cout<<desc<<endl;
			return -1;
		}else if(args.count(base_option)) {
			return BASE;
		}else if(args.count(ext1_option)) {
		        port =  args[ext1_option].as<int>();
			return EXT1;
		}else if(args.count(ext2_option)) {
		        port =  args[ext2_option].as<int>();
			return EXT2;
		}

	}catch(po::error &er) {
		cout<<er.what()<<endl;
	}catch(std::exception &ex) {
		cout<<ex.what()<<endl;
	}

	return -1;
}

/** Client Launcher Function
 * @param argc contains the number of the argument that the user has passed.
 * @param argv contains the rest of the arguments passed by the user.
 */

int main(int argc, char **argv) {
	int choice = parse_prog_params(argc,argv);
	switch (choice) {
		case BASE:
			direct_parser_launch();
			break;

		case EXT1:
		case EXT2:
			connect_to_server();
			break;

		default:
			cout<<"Invalid choice. Please use --help to get help"<<endl;
	}
	return 0;
}
