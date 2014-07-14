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

static const  char *base_option = "base";
static const  char *ext1_option = "ext1";
static const  char *ext2_option = "ext2";
static const  char *base_desc 	 = "This will run the program without any of the extensions enabled. All communication will be done using stdin-stdout";
static const  char *ext1_desc 	 = "This will run the program with single-threaded server client mode. Enter <ext1> <port_num>" ;
static const  char *ext2_desc 	 = "This will run the program with multi-threaded server client mode. Enter <ext2> <port_num>";

enum {
	BASE = 0,
	EXT1,
	EXT2
};

/**
 * This class implments generic utility functions.
 * Preferably all the member functions should be static .
 */
class Utility {

	public:
		/**
		 * This function convert double to string with the precision.
		 * Standard boost lexical_cast does not have the control over the precision.
		 * @param d , input double number
		 * @param precision ,  set the precision level. Default value is 2.
		 */
		static string convert_double_to_string(double d, int precision = 2);
};

#endif
