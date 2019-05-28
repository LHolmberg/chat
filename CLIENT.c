#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <string.h>
#include <gtk/gtk.h>
#include <pthread.h>

typedef struct gVars{
	int serverSock;
	char msg[100];
	char dest[100];
	char str[100];
	char username[10];
	char welcomeStorage[20];
	char welcomeUsername[10];
	GtkWidget *window, *entry, *grid, *instrLabel, *welcomeLabel;
}gVars;
struct gVars gv;

void print(GtkEntry *entry, void *optional_data){
	strcpy(gv.msg, gtk_entry_get_text(GTK_ENTRY(entry)));
	strcpy(gv.dest, gv.username);
	strcat(gv.dest, gv.msg);

	if(strlen(gv.dest) <= strlen(gv.username)){
		printf("YOU CAN NOT SEND AN EMPTY MESSAGE SIR!\n");
	}
	else{
		send(gv.serverSock, gv.dest, strlen(gv.dest), 0);
		gtk_entry_set_text (entry, "");
	}
}

int main(int argc, char *argv[]) {

	printf("Enter a username, sir: ");
	scanf("%s", gv.username);
	strcpy(gv.welcomeUsername, gv.username);
	strcat(gv.username, ": ");
	struct sockaddr_in server;

	gv.serverSock = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET;
	server.sin_port = htons(3002);
	inet_pton(AF_INET, "192.168.1.143", &server.sin_addr); // xxx.xxx.x.xxx = your computers ip
	connect(gv.serverSock, (struct sockaddr *)&server, sizeof(server));

	gtk_init(&argc, &argv);

	gv.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(gv.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_window_set_title (GTK_WINDOW (gv.window), gv.welcomeUsername);

	gv.grid = gtk_grid_new();
    	gtk_container_add(GTK_CONTAINER(gv.window), gv.grid);

	gv.entry = gtk_entry_new();
	g_signal_connect(gv.entry, "activate", G_CALLBACK(print), NULL);
	gtk_grid_attach(GTK_GRID(gv.grid), gv.entry, 1, 1, 4, 1);

	gv.instrLabel = gtk_label_new("Enter a msg: ");
	gtk_grid_attach(GTK_GRID(gv.grid), gv.instrLabel, 0, 1, 1, 1);

	strcpy(gv.welcomeStorage, "Welcome Mr ");
	strcat(gv.welcomeStorage, gv.welcomeUsername);

	gv.welcomeLabel = gtk_label_new(gv.welcomeStorage);
	gtk_grid_attach(GTK_GRID(gv.grid), gv.welcomeLabel, 0, 0, 1, 1);

	gtk_widget_show_all(gv.window);
	gtk_window_set_default_size(GTK_WINDOW(gv.window), 500, 150);
	gtk_window_set_resizable (GTK_WINDOW(gv.window), FALSE);

	gtk_main();
}
