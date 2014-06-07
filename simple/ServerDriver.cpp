#include <Server.h>

int main() {
	io_service io;
	Server s(io);
	io.run();
	return 0;
}
