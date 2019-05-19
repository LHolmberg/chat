#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char *argv[]){
    
    int serSock;
    serSock = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in server_adress;
    server_adress.sin_family = AF_INET;
    server_adress.sin_addr.s_addr = INADDR_ANY;
    server_adress.sin_port = 3002;
    
    bind(serSock, (struct sockaddr*) &server_adress, sizeof(server_adress));
    
    listen(serSock, 5);
    char msg[256];
    int client_socket;
    client_socket = accept(serSock, NULL,NULL);
    while(1){
        scanf("%s", msg);
        send(client_socket, msg, sizeof(msg),0);
    }
    
    close(serSock);
    
    return 0;
}
