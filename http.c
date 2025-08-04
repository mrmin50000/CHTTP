#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080 
#define BACKLOG 10

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Error of creating socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error of connection");
        exit(EXIT_FAILURE);
    }

    if(listen(server_fd, BACKLOG) < 0) {
        perror("Error listen()");
        exit(EXIT_FAILURE);
    }    

    printf("Server works on port: %d\n", PORT);

    while(1) {
        printf("\nWaiting of new connection...\n");

        client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if(client_fd < 0) {
            perror("Error accept()");
            continue;
        }

        printf("Client works: %s\n", inet_ntoa(client_addr.sin_addr));

        char buffer[1024] = {0};
        read(client_fd, buffer, sizeof(buffer) - 1);
        printf("Request:\n%s\n", buffer);

        close(client_fd);
    }

    close(server_fd);
    return 0;
}
