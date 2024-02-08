#include "../headers/Log.h"
#include <cstring> 

void Log::LogError(std::string e){
    std::string errnos = "\n";
    if (!_log_stream.is_open())
        {
            std::cerr << "Can not log: logfile is closed!" << std::endl;
            return;
        }
        if (errno){
            errnos += std::string(std::strerror(errno));
            errno = 0;
        }
    _log_stream << '[' << return_current_time_and_date() << " ] " << e << errnos << std::endl; 
}

void Log::InitLogStream(){
    try
    {
        _log_stream.open("Server.log");
    }
    catch(const std::exception& e)
    {
        _log_stream << e.what() << '\n';
    }   
}
