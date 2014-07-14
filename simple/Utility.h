#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;


//const static string  base_option = "base";
//const static string  ext1_option = "ext1";
//const static string  ext2_option = "ext2";
//const static string  base_desc = "This will run the program without any of the extensions enabled. All communication will be done using stdin-stdout";
//const static string  ext1_desc = "This will run the program with single-threaded server client mode. Enter <ext1> <port_num>" ;
//const static string  ext2_desc = "This will run the program with multi-threaded server client mode. Enter <ext2> <port_num>";

const  char *base_option = "base";
const  char *ext1_option = "ext1";
const  char *ext2_option = "ext2";
const  char *base_desc 	 = "This will run the program without any of the extensions enabled. All communication will be done using stdin-stdout";
const  char *ext1_desc 	 = "This will run the program with single-threaded server client mode. Enter <ext1> <port_num>" ;
const  char *ext2_desc 	 = "This will run the program with multi-threaded server client mode. Enter <ext2> <port_num>";

enum {
	BASE = 0,
	EXT1,
	EXT2
};


class Utility {

	public:
		static string convert_double_to_string(double d, int precision = 2);
};

#endif
