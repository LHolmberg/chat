#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <gtk/gtk.h>

#define maxlength 100

int main(int argc, char *argv[]){

	struct sockaddr_in server;
	int client;
	int connection;
	char msg[maxlength];

	server.sin_family = AF_INET;
	server.sin_port = htons(3002);
	server.sin_addr.s_addr = INADDR_ANY;
	client = socket(AF_INET, SOCK_STREAM, 0);

	bind(client, (struct sockaddr *)&server, sizeof(server));
	listen(client, 5);

	while(connection = accept(client, (struct sockaddr *)NULL, NULL)) {
	    int i;
	    if((i = fork()) == 0) {
	        while (recv(connection, msg, 100, 0)>0) {
	            printf("%s\n", msg);
	 	    msg[0] = '\0';
	            memset(&msg[0], 0, sizeof(msg));
	        }
	        exit(0);

	    }

	}
}
