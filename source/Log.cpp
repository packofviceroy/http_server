#include "../headers/Log.h"

void Log::LogError(std::string e){
    if (!_log_stream.is_open())
        {
            std::cerr << "Can not log: logfile is closed!" << std::endl;
            return;
        }
    _log_stream << '[' << return_current_time_and_date() << " ] " << e << std::endl; 
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
