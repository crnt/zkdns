/*
 * Copyright (c) 2010, Fred Emmott <mail@fredemmott.co.uk>
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
#include "ZooKeeper.h"

#include <zookeeper.h>

void ZooKeeper::watcher(
	zhandle_t* handle,
	int type,
	int state,
	const char* path,
	void* watcherContext
)
{
}

ZooKeeper::ZooKeeper()
{
	///@todo use clientid
	m_zk = zookeeper_init("localhost:2181", watcher, 30000, 0, this, 0);
}

std::string ZooKeeper::value(const std::string& path)
{
	char buffer[1024];
	int length = sizeof(buffer);
	const int result = zoo_get(m_zk, path.c_str(), 0, buffer, &length, 0);
	switch(result)
	{
		case ZOK:
			return std::string(buffer, length);
		case ZNONODE:
			throw NoSuchNodeError();
		case ZNOAUTH:
			throw PermissionsError();
		case ZBADARGUMENTS:
			throw BadArgumentsError();
		case ZINVALIDSTATE:
			throw BadStateError();
		case ZMARSHALLINGERROR:
			throw MarshallingError();
		default:
			throw LogicError("Unknown ZooKeeper Response");
	}
}

void ZooKeeper::setValue(const std::string& path, const std::string& value)
{
	const int result = zoo_set(m_zk, path.c_str(), value.data(), value.size(), -1);
	switch(result)
	{
		case ZOK:
			return;
		case ZNONODE:
			throw NoSuchNodeError();
		case ZNOAUTH:
			throw PermissionsError();
		case ZBADVERSION:
			throw LogicError("Version error reported when -1 given as version");
		case ZINVALIDSTATE:
			throw BadStateError();
		case ZMARSHALLINGERROR:
			throw MarshallingError();
		default:
			throw LogicError("Unknown ZooKeeper response");
	}
}

std::string ZooKeeper::createNode(const std::string& path, const std::string& value, EphemeralMode ephemeralMode, SequenceMode sequenceMode)
{
	int createFlags = 0;
	if(ephemeralMode == IsEphemeral)
	{
		createFlags |= ZOO_EPHEMERAL;
	}
	if(sequenceMode == IsSequence)
	{
		createFlags |= ZOO_SEQUENCE;
	}
	char buffer[1024];
	const int result = zoo_create(m_zk, path.c_str(), value.data(), value.size(), &ZOO_OPEN_ACL_UNSAFE, createFlags, buffer, sizeof(buffer));
	switch(result)
	{
		case ZOK:
			return std::string(buffer);
		case ZNONODE:
			throw NoSuchNodeError();
		case ZNODEEXISTS:
			throw NodeExistsError();
		case ZNOAUTH:
			throw PermissionsError();
		case ZNOCHILDRENFOREPHEMERALS:
			throw LogicError("Ephemeral nodes can not have children.");
		case ZBADARGUMENTS:
			throw BadArgumentsError();
		case ZINVALIDSTATE:
			throw BadStateError();
		case ZMARSHALLINGERROR:
			throw MarshallingError();
		default:
			throw LogicError("Unknown ZooKeeper response");
	}
}

ZooKeeper::~ZooKeeper()
{
	zookeeper_close(m_zk);
}
