/*
 * This program will use stereoscopic vision
 * to calculate the distance between the cameras
 * and a given object, and send the distance over
 * the network to a server to accept it.
 */

#include "vision_includes.hpp"
#include "client.h"
#include "server.h"
#include "structs.hpp"
#include "argument_processing.hpp"

using namespace cv;
using namespace std;

int main(int argc, char **argv) {
	VideoCapture capture1, capture2;
	double rate1, rate2;

	float distance;

	struct parameters pars;
	ReadArgs(&pars, argc, argv);

	if (PrintHelp(&pars, argc, argv) ) {
		// user supplied arguments were invalid, so exit
		return 1;
	}
	PrintParams(&pars);
	
	// connect to server if specified
	if (!pars.host)
			cout << "Not connecting to a server" << endl;
	else {
		if ( server_connect(pars.hostname, pars.portno) ) {
			server_disconnect();
			cerr << "Couldn't connect to server" << endl;
			return 1;
		}
	}

	if (pars.cam) {
		capture1.open(pars.camera1);
		capture2.open(pars.camera2);
		rate1 = rate2 = 30; /* Framerate is hardcoded for now
							   because my webcam isn't reporting
							   the frame rate correctly. */
	}
	else if (pars.file) {
		capture1.open(pars.filename1);
		capture2.open(pars.filename2);
		rate1 = capture1.get(CV_CAP_PROP_FPS);
		rate2 = capture2.get(CV_CAP_PROP_FPS);
		if (rate1 != rate2) {
			cerr << "Mismatching framerates!" << endl;
			return 1;
		}
	}

	return 0;
}
