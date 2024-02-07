#ifndef _SERVER_H_
#define _SERVER_H_

#include <inttypes.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <string>
#include <cstring>

#include "Log.h"

struct Server{

    Server(uint16_t port = 43594);
    ~Server() = default;

    void Start();


private:
        static const int __max_socket_queue = 1000;


        void CreateSocket();
        void SetSocket();
        void BindSocket();
        void StartSockListen();
        void Listen();

        Log* logger;
        int _sockfd;
        uint16_t _port;
        std::string _log_file_name;
        std::chrono::time_point<std::chrono::system_clock> _start_time;
        std::thread _listener_thread;
        bool _running;

};


#endif