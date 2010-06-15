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
#pragma once

#include <stdexcept>
#include <string>

typedef struct _zhandle zhandle_t;

class ZooKeeper
{
	public:
		class RuntimeError: public std::runtime_error { public: RuntimeError(const std::string& s) : std::runtime_error(s) {}; };
		class LogicError: public std::logic_error { public: LogicError(const std::string& s) : std::logic_error(s) {}; };
		class NoSuchNodeError: public RuntimeError { public: NoSuchNodeError() : RuntimeError("ZooKeeper::NoSuchNodeError") {} };
		class NodeExistsError: public RuntimeError { public: NodeExistsError() : RuntimeError("ZooKeeper::NodeExistsError") {} }; // Create call
		class PermissionsError: public RuntimeError { public: PermissionsError() : RuntimeError("ZooKeeper::PermissionsError") {} };
		class BadArgumentsError: public LogicError { public: BadArgumentsError() : LogicError("ZooKeeper::BadArgumentsError") {} };
		class BadStateError: public RuntimeError { public: BadStateError() : RuntimeError("ZooKeeper::BadStateError") {} };
		class MarshallingError : public RuntimeError { public: MarshallingError() : RuntimeError("ZooKeeper::MarshallingError") {} };

		ZooKeeper();
		~ZooKeeper();
		enum EphemeralMode
		{
			IsEphemeral,
			IsNotEphemeral
		};
		enum SequenceMode
		{
			IsSequence,
			IsNotSequence
		};

		std::string value(const std::string& path);
		void setValue(const std::string& path, const std::string& value);
		// Does not neccessarily return the same path, especially if
		// IsSequence is set.
		std::string createNode(const std::string& path, const std::string& value = std::string(), EphemeralMode ephemeralMode = IsNotEphemeral, SequenceMode sequenceMode = IsNotSequence);
		void deleteNode(const std::string& path);
	private:
		zhandle_t* m_zk;

		static void watcher(
			zhandle_t* handle,
			int type,
			int state,
			const char* path,
			void* watcherContext
		);
};
