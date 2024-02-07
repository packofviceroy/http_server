#include "../headers/Server.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>

Server::Server(uint16_t port): _port(port), _log_file_name("error.log")
                                            ,_running(false){
        try{
            CreateSocket();
            logger = new Log(_log_file_name);
        }
        catch(const std::exception& e)
        {
            logger->LogError(e.what());
            exit(-1);
        }
}


void Server::Start(){

    try{
        SetSocket();
        BindSocket();
        StartSockListen();
    }
    catch(const std::exception& e){
        logger->LogError(e.what());
        exit(-1);
    }

    _running = true;
    _listener_thread = std::thread(&Server::Listen, this);
    
}


void Server::Listen(){

    sockaddr client_addr;
    sockaddr_in client_address;
    socklen_t client_len = sizeof(client_address);
    int client_fd;
    int current_worker = 0;
    bool active = true;

    // accept new connections and distribute tasks to worker threads
    while (_running) {
      if (!active) {
        std::this_thread::sleep_for(std::chrono::microseconds(100));
      }
      client_fd = accept(_sockfd, (sockaddr *)&client_address, &client_len);
      if (client_fd < 0) {
        active = false;
        continue;
      }

        int ret = 0;
      char buffer[1024];
      ret = read(client_fd, &buffer, 1024);

      buffer[ret] = 0;
      active = true;
      std::cout << buffer;
    }
}

void Server::StartSockListen(){
    if (listen(_sockfd, __max_socket_queue)){
        throw std::runtime_error("Failed to start listening on port");
    }

}

void Server::CreateSocket(){

    _sockfd = socket(AF_INET,SOCK_STREAM,0);
    if ( _sockfd == -1)
        throw std::runtime_error("Failed to create socket.");
}


void Server::BindSocket(){
    sockaddr_in saddr;

    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    inet_pton(AF_INET, "0.0.0.0", &(saddr.sin_addr.s_addr));
    saddr.sin_port = htons(_port);

    if (bind(_sockfd, (sockaddr*)&saddr, sizeof(saddr)) < 0){
        throw std::runtime_error("Failed to bind socket.");
    }
}

void Server::SetSocket(){
    int opt = 1;
    int ret = 0;
    if (setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &opt,
                 sizeof(opt)) < 0){
                    throw std::runtime_error(std::string("Failed to set socket: ") + std::strerror(errno));
                 }
}


