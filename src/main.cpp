#include "ZooKeeperRecordProvider.h"
#include "../lib-cpp/ZkDns.h"

RecordProvider* recordProviderFactory(const std::string& zone)
{
	return new ZooKeeperRecordProvider(zone);
}

int main(int argc, char** argv)
{
	RecordProvider::setFactory(&recordProviderFactory);
	ZkDns::start("0.0.0.0", 8080, "zk");
	return 0;
}
