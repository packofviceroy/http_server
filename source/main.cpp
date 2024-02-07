#include <stdlib.h>
#include <iostream>
#include "../headers/Server.h"


int main(int argc, char* argv[]){
    Server server(4337U);
    server.Start();

    std::string command{};
    while (std::cin >> command , command != "1")
    {

    }
    return 0;
}