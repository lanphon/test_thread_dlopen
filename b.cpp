#include "a.h"
#include<thread>
#include<chrono>
#include<dlfcn.h>
#include<iostream>

using namespace std;

using func_init = decltype(&init);


int main(int argc, char **argv)
{
    const char *name = "./liba.so";
    void *handle = dlopen(name, RTLD_NOW);;
    if (handle == nullptr)
    {
        std::cerr << dlerror() << std::endl;
    }
    func_init l_init;

#ifdef _MSC_VER
#define GetFunc(FUNC_NAME) l_##FUNC_NAME = (func_##FUNC_NAME)GetProcAddress(handle, #FUNC_NAME)
#else
#define GetFunc(FUNC_NAME) l_##FUNC_NAME = (func_##FUNC_NAME)dlsym(handle, #FUNC_NAME)
#endif

    GetFunc(init);

    if (!l_init
       )
    {
        std::cerr << "fail to load library" << std::endl;
    }


    l_init();

#undef GetFunc

    dlclose(handle);
}
