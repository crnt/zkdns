#include "ZkDns.h"

extern "C"
{
	#include "../lib-c/clib.h"
}

void ZkDns::start(const char* address, int port, const char* zone)
{
	zkdns_start(address, port, zone);
}
