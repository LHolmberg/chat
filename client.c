#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
	
	int netSock;
	netSock = socket(AF_INET, SOCK_STREAM,0);

	struct sockaddr_in server_adress;
	server_adress.sin_family = AF_INET;
	server_adress.sin_port = htons(9002);
	server_adress.sin_addr.s_addr = INADDR_ANY;

	int connectionStat = connect(netSock, (struct sockaddr *) &server_adress, sizeof(server_adress));

	if(connectionStat == -1)
		printf("error\n");
	
	char response[256];
	recv(netSock, &response, sizeof(response), 0);

	printf("Sent data: %s\n", response);

	close(netSock);

	return 0;
}	

		
