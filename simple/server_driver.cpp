#include <iostream>
using namespace std;

#include  <Server.h>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/program_options.hpp>

#include <Utility.h>




void launch_single_threaded_server(int port_num) {
	try {
		ios_ptr ios(new boost::asio::io_service);
		boost::shared_ptr<tcp::endpoint> ep(new tcp::endpoint(tcp::v4(),port_num));
		Server server(ios,ep);
		ios->run();

	}catch(exception &ex) {
		cout<<ex.what()<<endl;
	}

}

void launch_multi_threaded_server(int port_num) {
	try {
		ios_ptr ios(new boost::asio::io_service);
		boost::shared_ptr<tcp::endpoint> ep(new tcp::endpoint(tcp::v4(),port_num));
		Server server(ios,ep,true);
	}catch(exception &ex) {
		cout<<ex.what()<<endl;
	}
}

 

int parse_program_option(int argc,char **argv) {

	namespace po = boost::program_options;
	po::options_description desc("CMS Application Server");
	desc.add_options()
		("help","Produce Server help message")
		(ext1_option,po::value<int>(),ext1_desc)
		(ext2_option,po::value<int>(),ext2_desc);


	po::variables_map args;
	int port = -1;
	try {
		po::store(po::parse_command_line(argc,argv,desc),args);
		po::notify(args);
		if(args.count("help")) {
			cout<<desc<<endl;
			return -1;
		}else if(args.count(ext1_option)) {
			port =  args[ext1_option].as<int>();
			launch_single_threaded_server(port);
		}else if(args.count(ext2_option)) {
			port =  args[ext2_option].as<int>();
			launch_multi_threaded_server(port);
		}else {
			cout<<"Invalid choice. Please use --help to get the help option"<<endl;
		}

	}catch(po::error &er) {
		cout<<er.what()<<endl;
	}catch(std::exception &ex) {
		cout<<ex.what()<<endl;
	}

	return 0;
}


int main(int argc, char **argv) {
	parse_program_option(argc,argv);
	return 0;
}
