/*
 * This program will use stereoscopic vision
 * to calculate the distance between the cameras
 * and a given object, and send the distance over
 * the network to a server to accept it.
 */

#include "vision_includes.hpp"
#include "client.h"
#include "structs.hpp"
#include "argument_processing.hpp"

using namespace cv;
using namespace std;

int main(int argc, char **argv) {
	VideoCapture capture1, capture2;
	double rate1, rate2;

	float distance;

	struct arguments arg;
	arg = readArgs(argc, argv);

	if (argc < 2) {
		cerr << "Usage: " << argv[0] << " <options>" << endl;
		return 1;
	}
	else if (arg.port == 1 && arg.host == 0) {
		cerr << "Please specify a hostname" << endl;
		return 1;
	}
	else if (arg.port == 0 && arg.host == 1) {
		cerr << "Please specify a portnumber" << endl;
		return 1;
	}
	else if ( (arg.file == 0 && arg.cam == 0) ||
			(arg.file == 1 && arg.cam == 1) ) {
		cerr << "Please specify either 2 cameras or 2 media files" << endl;
		return 1;
	}

	// printf what we got from the arguments
	if (arg.gui)
		cout << "Using GUI" << endl;
	if (arg.write)
		cout << "Writing to file" << endl;
	if (arg.host)
		cout << "Hostname: " << arg.hostname << endl;
	if (arg.port)
		cout << "Port number: " << arg.portno << endl;
	if (arg.cam)
		cout << "Using cameras: " << arg.camera1 << arg.camera2 << endl;
	if (arg.file)
		cout << "Using files: " << arg.filename1 << arg.filename2 << endl;
	
	// connect to server if specified
	if (arg.host == 0)
			cout << "Not connecting to a server" << endl;
	else {
		if ( server_connect(arg.hostname, arg.portno) ) {
			server_disconnect();
			cerr << "Couldn't connect to server" << endl;
			return 1;
		}
	}

	if (arg.cam) {
		capture1.open(arg.camera1);
		capture2.open(arg.camera2);
		rate1 = rate2 = 30; /* Framerate is hardcoded for now
							   because my webcam isn't reporting
							   the frame rate correctly. */
	}
	else if (arg.file) {
		capture1.open(arg.filename1);
		capture2.open(arg.filename2);
		rate1 = capture1.get(CV_CAP_PROP_FPS);
		rate2 = capture2.get(CV_CAP_PROP_FPS);
		if (rate1 != rate2) {
			cerr << "Mismatching framerates!" << endl;
			return 1;
		}
	}

	return 0;
}
