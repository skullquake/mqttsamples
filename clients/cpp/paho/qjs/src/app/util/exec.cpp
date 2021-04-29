#include<cstdlib>
#include<cstdio>
#include<memory>
#include<string>
#define BUFSZ 128
std::string exec(std::string scmd) {
    scmd.append(" 2>&1");
    const char*cmd=scmd.c_str();
    std::array<char,BUFSZ>buffer;
    std::string result;
    std::unique_ptr<FILE,decltype(&pclose)>pipe(popen(cmd,"r"),pclose);
    if(!pipe){
        throw std::runtime_error("error: popen() failure");
    }
    while(fgets(buffer.data(),buffer.size(),pipe.get())!=nullptr){
        result+=buffer.data();
    }
    return result;
}
