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

ZooKeeperRecordProvider::ZooKeeperRecordProvider(const std::string& zone)
: RecordProvider()
{
	m_topZone = zone;
	m_zk = new ZooKeeper();
}

ZooKeeperRecordProvider::~ZooKeeperRecordProvider()
{
	delete m_zk;
}

std::string ZooKeeperRecordProvider::aRecord(const std::string& zone) const
{
	return "127.0.0.1";
}

std::string ZooKeeperRecordProvider::aaaaRecord(const std::string& zone) const
{
	return "::1";
}
