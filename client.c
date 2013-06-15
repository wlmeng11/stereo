#include "client.h"

int sockfd;
int n;
struct sockaddr_in serv_addr;
struct hostent *server;

char *readbuffer;

int server_connect (char *hostname, int portno) {
	printf("Connecting to: %s\n", hostname);

	return 0;
}

int server_send (double distance) {

	return 0;
}

int server_disconnect() {

	return 0;
}
