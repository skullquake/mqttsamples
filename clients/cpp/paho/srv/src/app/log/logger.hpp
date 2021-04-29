#ifndef ha6e045e0a8d511eb8e1b270752065405
#define ha6e045e0a8d511eb8e1b270752065405
#include<string>
#include"plog/Log.h"
namespace app::log{
	class Logger{
		public:
			Logger();
			~Logger();
			void initialize(::std::string pLogFile);
		private:
	};
	extern Logger logger;
}
#endif
