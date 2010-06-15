#include "RecordProvider.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

extern "C"
{
	#include "../lib-c/recordprovider.h"
}

// Initialize factory as null
RecordProvider::Factory RecordProvider::m_factory = 0;

// *********************
// ***** C <=> C++ *****
// *********************

RecordProvider* handleToRecordProvider(void* handle)
{
	assert(handle);
	RecordProvider* recordProvider = static_cast<RecordProvider*>(handle);
	return recordProvider;
}

void* rp_initialize(const char* zone)
{
	assert(RecordProvider::factory());
	return (*RecordProvider::factory())(std::string(zone));
}

int rp_shutdown(void* handle)
{
	delete handleToRecordProvider(handle);
}

const char* rp_get_a_record(void* handle, const char* zone)
{
	const std::string result = handleToRecordProvider(handle)->aRecord(std::string(zone));
	if(result.empty())
	{
		return 0;
	}
	const size_t size = result.size() + 1; // null byte

	char* out = static_cast<char*>(malloc(size));
	::bzero(out, size);
	::memcpy(out, result.data(), size);
	return out;
}

// **********************************************
// ***** RecordProvider C++ Implementation ******
// **********************************************

RecordProvider::Factory RecordProvider::factory()
{
	return m_factory;
}

void RecordProvider::setFactory(Factory factory)
{
	m_factory = factory;
}

RecordProvider::RecordProvider()
{
}

RecordProvider::~RecordProvider()
{
}
