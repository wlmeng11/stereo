#ifndef __server_h__
#define __server_h__

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define BUFFSIZE 80

int server_start (int portno);

int server_accept ();

int server_close ();

#endif
