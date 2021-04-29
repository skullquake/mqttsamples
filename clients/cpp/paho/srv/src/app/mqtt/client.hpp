#ifndef h3629a74ca86211eb9efca31684e63acf
#define h3629a74ca86211eb9efca31684e63acf
#include"mqtt/async_client.h"
namespace app::mqtt{
	class Client{
		public:
			Client();
			~Client();
		private:
			//::mqtt::async_client cli("A","B");
			::mqtt::async_client*cli;
	};
}
#endif
