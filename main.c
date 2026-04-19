#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080

char* read_file(const char* filename, long *size) {
    FILE* f = fopen(filename, "rb");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    *size = ftell(f);
    fseek(f, 0, SEEK_SET);

    char* string = malloc(*size + 1);
    if (string) {
        fread(string, *size, 1, f);
        string[*size] = 0;
    }
    fclose(f);
    return string;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    
    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Lumina Professional Online at port %d\n", PORT);

    while(1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            continue; // Don't kill the server, just wait for next client
        }
        
        char buffer[1024] = {0};
        int valread = read(new_socket, buffer, 1024);
        
        if (valread > 0) {
            long html_size = 0;
            char* html_content = read_file("index.html", &html_size);
            
            if (html_content) {
                char *header = "HTTP/1.1 200 OK\nContent-Type: text/html\nConnection: close\n\n";
                write(new_socket, header, strlen(header));
                write(new_socket, html_content, html_size);
                free(html_content);
            }
        }
        close(new_socket);
    }
    return 0;
}