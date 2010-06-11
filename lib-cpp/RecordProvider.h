#pragma once

#include <string>

/// Abstract interface for a C++ record provider.
class RecordProvider
{
	public:
		typedef RecordProvider*(*Factory)(const std::string& zone);

		virtual ~RecordProvider();
		virtual std::string aRecord(const std::string& zone) const = 0;
		virtual std::string aaaaRecord(const std::string& zone) const = 0;

		static Factory factory();
		static void setFactory(Factory);
	protected:
		RecordProvider();
	private:
		static Factory m_factory;
};
