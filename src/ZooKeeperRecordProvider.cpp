#include "ZooKeeperRecordProvider.h"

ZooKeeperRecordProvider::ZooKeeperRecordProvider(const std::string& zone)
: RecordProvider()
{
	m_topZone = zone;
}

ZooKeeperRecordProvider::~ZooKeeperRecordProvider()
{
}

std::string ZooKeeperRecordProvider::aRecord(const std::string& zone) const
{
	return "127.0.0.1";
}

std::string ZooKeeperRecordProvider::aaaaRecord(const std::string& zone) const
{
	return "::1";
}
