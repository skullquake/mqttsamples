#ifndef hdb136258a82f11eb8ad5f7863beaad98
#define hdb136258a82f11eb8ad5f7863beaad98
#include<string>
namespace app::config{
	class Config{
		public:
			Config();
			~Config();
			void set_mqttHost(std::string);
			void set_mqttPort(int);
			void set_mqttTopic(std::string);
			void set_mqttClientID(std::string);
			void set_logFile(std::string);
			void set_httpHost(std::string);
			void set_httpPort(int);
			void set_httpLogLevel(std::string);
			void set_httpConcurrency(int);
			std::string get_mqttHost();
			int get_mqttPort();
			std::string get_mqttTopic();
			std::string get_mqttClientID();
			std::string get_logFile();
			std::string get_httpHost();
			int get_httpConcurrency();
			int get_httpPort();
			std::string get_httpLogLevel();
			void loadJson(std::string pPath);
			void writeJson(std::string pPath);
		private:
			std::string mMqttHost;
			int mMqttPort;
			std::string mMqttTopic;
			std::string mMqttClientID;
			std::string mLogFile;
			std::string mHttpHost;
			int mHttpPort;
			std::string mHttpLogLevel;
			int mHttpConcurrency;
	};
	extern Config config;
}
#endif
