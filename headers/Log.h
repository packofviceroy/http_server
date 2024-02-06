#include <chrono>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include "Helpers.h"

struct Log{
    Log(): _log_file_name("error.log"){ InitLogStream();};
    Log(std::string file_name): _log_file_name(file_name){InitLogStream();};
    void LogError(std::string);


private:
        void InitLogStream();
        std::ofstream _log_stream;
        std::string _log_file_name;
};