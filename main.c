#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    // Raw HTTP response - this is the "infrastructure" layer
    char *response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<h1>Lumina Server Online</h1><p>Running on C infrastructure.</p>";

    // 1. Create socket (AF_INET = IPv4, SOCK_STREAM = TCP)
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 2. Set address and port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // 3. Bind the socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // 4. Start listening
    if (listen(server_fd, 10) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Lumina is waiting for a connection on port %d...\n", PORT);

    while(1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }
        
        char buffer[1024] = {0};
        read(new_socket, buffer, 1024);
        printf("Request Received:\n%s\n", buffer);
        
        write(new_socket, response, strlen(response));
        close(new_socket);
    }
    return 0;
}