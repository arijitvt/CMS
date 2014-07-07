#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;


class Utility {

	public:
		static string convert_double_to_string(double d, int precision = 2);
};

#endif
