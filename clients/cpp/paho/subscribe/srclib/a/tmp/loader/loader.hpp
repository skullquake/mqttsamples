#ifndef he0a41d2a8a2f11eb95562fc05d13f1c0
#define he0a41d2a8a2f11eb95562fc05d13f1c0
class Loader{
	public:
		Loader();
		~Loader();
		std::string getDSOPath();
	private:
		std::string dsopath;
	};
#endif
