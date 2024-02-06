#include "../headers/Server.h"
#include <sys/socket.h>
#include <arpa/inet.h>


Server::Server(uint16_t port = 43594): _port(port), _log_file_name("error.log"){
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
    
}


void Server::Listen(){

    sockaddr client addr;
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
    if (setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                 sizeof(opt)) < 0){
                    throw std::runtime_error("Failed to set socket.");
                 }
}


