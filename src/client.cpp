#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    //setup
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

    int connectStatus = connect(clientSocket, (struct sockaddr*)&serverAddress,
                  sizeof(serverAddress));

    if (connectStatus == -1) {
        printf("Error connecting...\n");
        close(clientSocket);
        return 1;
    }

    while (true) {
        std::cout << ">";

        std::string message;
        std::getline(std::cin, message);

        if (message == "exit") {
            break;
        }

        int sendStatus = send(clientSocket,  message.c_str(), message.size(), 0);

        std::cout<<sendStatus<<std::endl;

        char buffer[1024];
        
       ssize_t bytes = read(clientSocket, buffer, sizeof(buffer) - 1);
       if (bytes <= 0) {
         std::cout << "server closed connection\n";
         break;
       }

buffer[bytes] = '\0';

        std::cout<<"bytes recieved:" <<bytes<<std::endl;
        buffer[bytes] = '\0';

        std::string new_buffer = buffer;

        std::cout << new_buffer << "\n";
    }

    close(clientSocket);
    return 0;

 }
