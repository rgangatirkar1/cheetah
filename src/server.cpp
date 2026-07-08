#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {

    //create server socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    //server setup
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    listen(serverSocket, 5);

    while (true) {
    int client = accept(serverSocket, nullptr, nullptr);
    if (client < 0) continue;

    std::cout << "Client connected" << std::endl;

    char buffer[1024];
    while (true) {
        ssize_t bytes = recv(client, buffer, sizeof(buffer) - 1, 0);

        if (bytes <= 0) { 
            std::cout << "Client disconnected" << std::endl;
            break; 
        }

        buffer[bytes] = '\0';
        std::cout << "Buffer: " << buffer << std::endl;

        std::string response = "ACK: " + std::string(buffer) + "\n";
        write(client, response.c_str(), response.size());
    }
     close(client); // Close only after the client is done
    }

    close(serverSocket);
    return 0;
}
