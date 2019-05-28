#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <pthread.h>

#define maxlength 100

typedef struct sock{
	int serverSock;
	int client;
	int connection;
	char msg[maxlength];
	struct sockaddr_in server;
	pthread_t thread1, thread2;
	int i1,i2;
  GtkWidget *window, *label;
}sock;
struct sock so;

void *MessageHandeler(void *arg){
	while(so.connection = accept(so.client, (struct sockaddr *)NULL, NULL)) {
		int i;
		if((i = fork()) == 0) {
  		while (recv(so.connection, so.msg, 100, 0)>0) {
			printf("%s\n", so.msg);
			so.msg[0] = '\0';
			memset(&so.msg[0], 0, sizeof(so.msg));
			}
		exit(0);
		}
	}
}

void *GraphicsHandeler(void *arg){
	gtk_main();
}

int main(int argc, char *argv[]){
	so.server.sin_family = AF_INET;
	so.server.sin_port = htons(3002);
	so.server.sin_addr.s_addr = INADDR_ANY;
	so.client = socket(AF_INET, SOCK_STREAM, 0);

	bind(so.client, (struct sockaddr *)&so.server, sizeof(so.server));
	listen(so.client, 5);

	gtk_init (&argc, &argv);

	so.window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(so.window), "Chat");
	gtk_window_set_default_size(GTK_WINDOW(so.window), 500, 200);

	so.label = gtk_label_new ("helloooo");
	gtk_container_add (GTK_CONTAINER (so.window), so.label);

	gtk_widget_show_all (so.window);

	so.i1 = pthread_create( &so.thread1, NULL, MessageHandeler, (void*) "thread 1");
	so.i2 = pthread_create( &so.thread2, NULL, GraphicsHandeler, (void*) "thread 2");

	pthread_join(so.thread1,NULL);
}
