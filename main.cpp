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

void CombineImages (const Mat &left, const Mat &right, Mat &combined); // combines left and right images into one big image

int main(int argc, char **argv) {
	VideoCapture capture1, capture2;
	double rate1, rate2;

	//float distance;

	struct parameters pars;

	if (ReadArgs(&pars, argc, argv) ) {
		// command line usage error
		return EX_USAGE;
	}
	if (PrintHelp(&pars, argc, argv) ) {
		return EX_USAGE;
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

	if (!capture1.isOpened()) {
		cerr << "Failed to open capture 1" << endl;
		return EX_NOINPUT;
	}
	else if (!capture2.isOpened()) {
		cerr << "Failed to open capture 2" << endl;
		//return EX_NOINPUT;
	}

	cout << "Left framerate: " << rate1 << endl;
	cout << "Right framerate: " << rate2 << endl;

	Mat left, right;
	Mat combined;

	int delay = 1000/rate1;

	for(int i = 0;;i++) { // use i to count frames
		if (!capture1.read(left) ) break;
		else if (!capture2.read(right) ) break;

		CombineImages(left, right, combined);

		if (pars.gui) {
			imshow("Left", left);
			//imshow("Right", right);
			//imshow("Combined frames", combined);
		}

		if (capture1.get(CV_CAP_PROP_FRAME_COUNT) == 1)
			// individual image instead of sequential stream
			waitKey(0);
		else if (waitKey(delay)>=0) break; // wait for delay until next frame or break if keystroke
	}

	return 0;
}

// this needs to go in a class in another file eventually
void CombineImages (const Mat &left, const Mat &right, Mat &combined) {
	cout << "Left height: " << left.rows << endl;
	cout << "Left width: " << left.cols << endl;
	cout << "Right height: " << right.rows << endl;
	cout << "Right width: " << right.cols << endl;
	//combined image doesn't exist yet
	cout << "Combined height: " << combined.rows << endl;
	cout << "Combined width: " << combined.cols << endl;

	Mat imageROI; // region of interest
}
