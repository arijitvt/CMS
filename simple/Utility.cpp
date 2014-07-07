#include <Utility.h>


string Utility::convert_double_to_string(double d , int precision) {
	stringstream stream;
	stream<<setprecision(precision)<<fixed<<d;
	return stream.str();
}
