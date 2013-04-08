#ifndef __client_h__
#define __client_h__

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define BUFFSIZE 80

bool server_connect (char *hostname, int portno);

bool server_send (double distance);

void server_disconnect();

#endif
