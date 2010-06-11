#pragma once

#include "../lib-cpp/RecordProvider.h"

class ZooKeeperRecordProvider : public RecordProvider
{
	public:
		ZooKeeperRecordProvider(const std::string& zone);
		~ZooKeeperRecordProvider();

		std::string aRecord(const std::string& zone) const;
		std::string aaaaRecord(const std::string& zone) const;
	private:
		std::string m_topZone;
};
