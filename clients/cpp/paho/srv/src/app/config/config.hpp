#ifndef hdb136258a82f11eb8ad5f7863beaad98
#define hdb136258a82f11eb8ad5f7863beaad98
#include<string>
namespace app::config{
	class Config{
		public:
			Config();
			~Config();
			void set_host(std::string);
			void set_port(int);
			void set_topic(std::string);
			void set_clientID(std::string);
			void set_logfile(std::string);
			std::string get_host();
			int get_port();
			std::string get_topic();
			std::string get_clientID();
			std::string get_logfile();
			void loadJson(std::string pPath);
			void writeJson(std::string pPath);
		private:
			std::string mHost;
			int mPort;
			std::string mTopic;
			std::string mClientID;
			std::string mLogFile;
	};
	extern Config config;
}
#endif
