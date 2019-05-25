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
	struct sockaddr_in serv;
	int fd;
	int conn;
  	char msg[maxlength];

  	serv.sin_family = AF_INET;
  	serv.sin_port = 3002;
  	serv.sin_addr.s_addr = INADDR_ANY;
  	fd = socket(AF_INET, SOCK_STREAM, 0);

	bind(fd, (struct sockaddr *)&serv, sizeof(serv));
	listen(fd,5);

	while(conn = accept(fd, (struct sockaddr *)NULL, NULL)) {
    		int pid;
    		if((pid = fork()) == 0) {
        		while (recv(conn, msg, 100, 0)>0) {
            			printf("%s\n", msg);
	    			msg[0] = '\0';
	    			memset(&msg[0], 0, sizeof(msg));
        }
        exit(0);
    }
		gtk_main ();
}
}
