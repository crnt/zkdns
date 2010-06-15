/*
 * Copyright (c) 2010, Mendeley Limited <copyright@mendeley.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#include "ZooKeeperRecordProvider.h"

#include "ZooKeeper.h"

#include <boost/foreach.hpp>

#include <iostream>
using namespace std;

ZooKeeperRecordProvider::ZooKeeperRecordProvider(const std::string& zone)
: RecordProvider()
{
{
	cout << __FUNCTION__ << this << endl;
	std::string currentZone;
	BOOST_FOREACH(char ch, zone)
	{
		if(ch == '.')
		{
			if(!currentZone.empty())
			{
				m_topZone.push_back(currentZone);
				currentZone = std::string();
			}
		}
		else
		{
			currentZone.push_back(ch);
		}
	}
	if(!currentZone.empty())
	{
		m_topZone.push_back(currentZone);
	}
}
	m_zk = new ZooKeeper();
}

std::vector<std::string> ZooKeeperRecordProvider::splitZone(const std::string& zone)
{
	std::vector<std::string> result;
	int offset = 0;
	while(offset < zone.size() && zone[offset] != 0)
	{
		char length = zone[offset];
		const std::string part(&zone.data()[++offset], length);
		result.push_back(part);
		offset += length;
	}
	return result;
}

ZooKeeperRecordProvider::~ZooKeeperRecordProvider()
{
	delete m_zk;
}

std::string ZooKeeperRecordProvider::aRecord(const std::string& zone) const
{
	std::vector<std::string> parts = splitZone(zone);
	///@todo: check last parts == zone
	// Skip off the top zone
	std::string path;
	for(int i = (parts.size() - m_topZone.size()) - 1; i >= 0; --i)
	{
		path.append("/" + parts[i]);
	}

	std::string result;
	try
	{
		result = m_zk->value(path);
	}
	catch(ZooKeeper::RuntimeError e)
	{
		cerr << "Caught ZooKeeper error: " << e.what() << endl;
		return std::string();
	}

	// Split off if there's a colon (port number)
	std::string ip;
	BOOST_FOREACH(const char ch, result)
	{
		if(ch == ':')
		{
			break;
		}
		ip.push_back(ch);
	}

	return ip;
}

std::string ZooKeeperRecordProvider::aaaaRecord(const std::string& zone) const
{
	return "::1";
}
