#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    int netsock;
    netsock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int stat = connect(netsock, (struct sockaddr *) &server_address, sizeof(server_address));

    if(stat == -1)
        printf("error");

    char respo[256];

    recv(netsock, &respo, sizeof(respo), 0);

    printf("Server: %s\n", respo);

    close(netsock);

    return 0;
}
