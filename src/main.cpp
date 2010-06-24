#include "ZooKeeperRecordProvider.h"
#include "../lib-cpp/ZkDns.h"

#include <boost/program_options.hpp>

#include <iostream>
#include <fstream>
#include <string>

#include <unistd.h>

using namespace std;
namespace po = boost::program_options;

RecordProvider* recordProviderFactory(const std::string& zone)
{
	return new ZooKeeperRecordProvider(zone);
}

void start(int port)
{
	RecordProvider::setFactory(&recordProviderFactory);
	ZkDns::start("0.0.0.0", port, "zk");
}

int main(int argc, char** argv)
{
	po::options_description options("Allowed options");
	options.add_options()
		("help,h", "produce this message")
		("daemon,d", "run in the background")
		("port,p", po::value<int>(), "run on the specified port number (default 54)")
		("pid-file,P", po::value<string>(), "record the PID in the specified file")
	;
	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, options), vm);
	po::notify(vm);

	int port = 54;
	string pidFile;
	bool daemon = false;

	if(vm.count("help"))
	{
		cout << options << endl;
		return 1;
	}
	if(vm.count("daemon"))
	{
		daemon = true;
	}
	if(vm.count("port"))
	{
		port = vm["port"].as<int>();
	}
	if(vm.count("pid-file"))
	{
		pidFile = vm["pid-file"].as<string>();
	}

	if(!daemon)
	{
		start(port);
	}
	else
	{
		if(!fork())
		{
			if(!fork())
			{
				// Clean environment
				chdir("/");
				setsid();
				// Write a pid file
				if(!pidFile.empty());
				{
					ofstream out(pidFile.c_str());
					out << getpid() << endl;
				}
				// Run
				start(port);
			}
		}
	}
	return 0;
}
