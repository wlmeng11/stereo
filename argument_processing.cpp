#include "argument_processing.hpp"

int ReadArgs(struct parameters *pars, int argc, char **argv) {
	*pars = { 0, 0, 0, 0, 0, 0, NULL, -1, -1, -1, NULL, NULL };

	for (int i = 1; i < argc; i++) {
		if ( (strcmp(argv[i], "-g") == 0) || 
				(strcmp(argv[i], "--gui") == 0) ) 
			pars->gui = 1;
		else if ( (strcmp(argv[i], "-w") == 0) ||
				(strcmp(argv[i], "--write") == 0) )
			pars->write = 1;
		else if ( (strcmp(argv[i], "-h") == 0) ||
				(strcmp(argv[i], "--host") == 0) ) {
			pars->host = 1;
			// pars-> hostname
			if (i + 1 <= argc - 1) {
				i++;
				pars->hostname = argv[i];
			}
			else {
				cerr << "Usage: -h <host IP>" << endl;
				exit(1);
			}
		}
		else if ( (strcmp(argv[i], "-p") == 0) ||
				(strcmp(argv[i], "--port") == 0)) {
			pars->port = 1;
			if (i + 1 <= argc -1) {
				i++;
				sscanf(argv[i], "%d", &pars->portno);
			}
			else {
				cerr << "Usage: -p <port number>" << endl;
				exit(1);
			}
		}
		else if ( (strcmp(argv[i], "-c") == 0) ||
				(strcmp(argv[i], "--cam") == 0) ) {
			pars->cam = 1;
			if (i + 2 <= argc - 1) {
				i++;
				sscanf(argv[i], "%d", &pars->camera1);
				i++;
				sscanf(argv[i], "%d", &pars->camera2);
			}
			else {
				cerr << "Usage: -c <camera 1> <camera 2>" << endl;
				exit(1);
			}
		}
		else if ( (strcmp(argv[i], "-f") == 0) ||
				(strcmp(argv[i], "--file") == 0) ) {
			pars->file = 1;
			if (i + 2 <= argc - 1) {
				i++;
				pars->filename1 = argv[i];
				i++;
				pars->filename2 = argv[i];
			}
			else {
				cerr << "Usage: -f <file 1> <file 2>" << endl;
				exit(1);
			}
		}
	}
}

int PrintHelp(struct parameters *pars, int argc, char **argv) {
	if (argc < 2) {
		cerr << "Usage: " << argv[0] << " <options>" << endl;
		// main help message
		return 1;
	}
	else if (pars->port && !pars->host) {
		cerr << "Please specify a hostname" << endl;
		return 1;
	}
	else if (!pars->port && pars->host) {
		cerr << "Please specify a portnumber" << endl;
		return 1;
	}
	else if ( (!pars->file && !pars->cam) ||
			(pars->file && pars->cam) ) {
		cerr << "Please specify either 2 cameras or 2 media files" << endl;
		return 1;
	}
	else
		return 0;
}

void PrintParams(struct parameters *pars) {
	// print what we got from the arguments
	if (pars->gui)
		cout << "Using GUI" << endl;
	if (pars->write)
		cout << "Writing to file" << endl;
	if (pars->host)
		cout << "Hostname: " << pars->hostname << endl;
	if (pars->port)
		cout << "Port number: " << pars->portno << endl;
	if (pars->cam)
		cout << "Using cameras: " << pars->camera1 << " " << pars->camera2 << endl;
	if (pars->file)
		cout << "Using files: " << pars->filename1 << " " << pars->filename2 << endl;
}
