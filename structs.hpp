#ifndef __structs_hpp__
#define __structs_hpp__

#include <iostream>

struct parameters {
		// used as booleans to indicate presence of a parameter
		int gui;
		int write;
		int host;
		int port;
		int cam;
		int file;
		
		// these are defined by user-supplied arguments
		char *hostname;
		int portno;
		int camera1, camera2;
		char *filename1, *filename2;
	};

#endif
