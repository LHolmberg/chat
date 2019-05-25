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

struct gvars{
	int fd;
	int conn;
	char msg[100];
		char dest[100];
		char str[100];
}vars;


void print(GtkEntry *entry, void *optional_data){


	sprintf(vars.str, "client %d: ", vars.fd);
		strcpy (vars.msg, gtk_entry_get_text(GTK_ENTRY(entry)));
		strcpy(vars.dest, vars.str);
		strcat(vars.dest, vars.msg);
		send(vars.fd, vars.dest, strlen(vars.dest), 0);

}


int main(int argc, char *argv[]) {

			struct sockaddr_in serv;
			vars.fd = socket(AF_INET, SOCK_STREAM, 0);
		  serv.sin_family = AF_INET;
		  serv.sin_port = htons(8096);
		  inet_pton(AF_INET, "192.168.10.239", &serv.sin_addr); //This binds the client to localhost
		  connect(vars.fd, (struct sockaddr *)&serv, sizeof(serv)); //This connects the client to the server.

			gtk_init(&argc, &argv);

			GtkWidget *window, *entry;
			window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
			entry = gtk_entry_new();

			gtk_container_add(GTK_CONTAINER(window), entry);

			g_signal_connect(entry, "activate", G_CALLBACK(print), NULL);
			gtk_widget_show_all(window);
			gtk_window_set_default_size(GTK_WINDOW(window), 400, 100);
			gtk_window_set_resizable (GTK_WINDOW(window), FALSE);
			gtk_main();

}
