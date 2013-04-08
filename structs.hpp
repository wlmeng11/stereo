#ifndef __structs_hpp__
#define __structs_hpp__

#include <iostream>

struct arguments {
		// used as booleans to indicate presence of argument
		int gui;
		int write;
		int host;
		int port;
		int cam;
		int file;
		
		// these are defined by arguments
		char *hostname;
		int portno;
		int camera1, camera2;
		char *filename1, *filename2;
	};

#endif
