#include "argument_processing.hpp"

struct arguments readArgs(int argc, char **argv) {
	struct arguments arg;

	arg.gui = 0;
	arg.write = 0;
	arg.host = 0;
	arg.port = 0;
	arg.cam = 0;
	arg.file = 0;
	arg.hostname = NULL;
	arg.portno = -1;
	arg.camera1 = -1;
	arg.camera2 = -1;
	arg.filename1 = NULL;
	arg.filename2 = NULL;

	for (int i = 1; i < argc; i++) {
		if ( (strcmp(argv[i], "-g") == 0) || 
				(strcmp(argv[i], "--gui") == 0) ) 
			arg.gui = 1;
		else if ( (strcmp(argv[i], "-w") == 0) ||
				(strcmp(argv[i], "--write") == 0) )
			arg.write = 1;
		else if ( (strcmp(argv[i], "-h") == 0) ||
				(strcmp(argv[i], "--host") == 0) ) {
			arg.host = 1;
			// parse hostname
			if (i + 1 <= argc - 1) {
				i++;
				arg.hostname = argv[i];
			}
			else
				cerr << "Usage: -h <host IP>" << endl;
		}
		else if ( (strcmp(argv[i], "-p") == 0) ||
				(strcmp(argv[i], "--port") == 0)) {
			arg.port = 1;
			if (i + 1 <= argc -1) {
				i++;
				sscanf(argv[i], "%d", &arg.portno);
				//portno = atoi(argv[i]);
			}
			else
				cerr << "Usage: -p <port number>" << endl;
		}
	
		else if ( (strcmp(argv[i], "-c") == 0) ||
				(strcmp(argv[i], "--cam") == 0) ) {
			arg.cam = 1;
			if (i + 1 <= argc - 1) {
				i++;
				arg.camera1 = atoi(argv[i]);
				i++;
				arg.camera2 = atoi(argv[i]);
			}
		}
		else if ( (strcmp(argv[i], "-f") == 0) ||
				(strcmp(argv[i], "--file") == 0) ) {
			arg.file = 1;
			if (i + 1 <= argc - 1) {
				i++;
				arg.filename1 = argv[i];
				i++;
				arg.filename2 = argv[i];
			}
		}
	}

	return arg;
}
