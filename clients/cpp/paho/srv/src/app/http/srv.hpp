#ifndef h1dd4a1cca85f11ebb69fb7231029222f
#define h1dd4a1cca85f11ebb69fb7231029222f
#include"crow/crow.h"
#include"crow/crow/mustache.h"

namespace app::http{
	class Server{
		public:
			Server();
			~Server();
			void run();
		private:
			//::crow::App</*MW*/>mApp;
			::crow::SimpleApp mApp;
	};
}
#endif

