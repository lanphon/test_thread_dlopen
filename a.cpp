#include<thread>
#include<unistd.h>
#include<iostream>
#include "a.h"

class test_t
{
	public:
		test_t(){}
		static test_t& get_instance()
		{
			static test_t t;
			return t;
		}

		void process()
		{
		}

		void detach()
		{
			auto t = std::thread([]{
					auto& d = test_t::get_instance();
					while(true)
					{
					d.process();
					}
					});
			std::cout << t.get_id() << std::endl;
			t.detach();
		}
	private:
};

extern "C" void init()
{
    test_t::get_instance().detach();
}
