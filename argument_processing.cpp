#include "argument_processing.hpp"

struct arguments readArgs(int argc, char **argv) {
	struct arguments arg = { 0, 0, 0, 0, 0, 0, NULL, -1, -1, -1, NULL, NULL };

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
			else {
				cerr << "Usage: -h <host IP>" << endl;
				exit(1);
			}
		}
		else if ( (strcmp(argv[i], "-p") == 0) ||
				(strcmp(argv[i], "--port") == 0)) {
			arg.port = 1;
			if (i + 1 <= argc -1) {
				i++;
				sscanf(argv[i], "%d", &arg.portno);
			}
			else {
				cerr << "Usage: -p <port number>" << endl;
				exit(1);
			}
		}
		else if ( (strcmp(argv[i], "-c") == 0) ||
				(strcmp(argv[i], "--cam") == 0) ) {
			arg.cam = 1;
			if (i + 2 <= argc - 1) {
				i++;
				sscanf(argv[i], "%d", &arg.camera1);
				i++;
				sscanf(argv[i], "%d", &arg.camera2);
			}
			else {
				cerr << "Usage: -c <camera 1> <camera 2>" << endl;
				exit(1);
			}
		}
		else if ( (strcmp(argv[i], "-f") == 0) ||
				(strcmp(argv[i], "--file") == 0) ) {
			arg.file = 1;
			if (i + 2 <= argc - 1) {
				i++;
				arg.filename1 = argv[i];
				i++;
				arg.filename2 = argv[i];
			}
			else {
				cerr << "Usage: -f <file 1> <file 2>" << endl;
				exit(1);
			}
		}
	}

	return arg;
}
