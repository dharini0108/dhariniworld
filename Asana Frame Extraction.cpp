#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv\cv.h>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <iostream>
#include <stdarg.h>
#include <opencv2\videoio.hpp>
#include <stdlib.h>
#include <opencv2/highgui/highgui_c.h>
#include <opencv/cxcore.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Point Rectanglep1;
Point Rectanglep2;

int Rectanglep1x, Rectanglep1y, Rectanglep2x, Rectanglep2y; 
int startframenumber, perfectframenumber, endframenumber;
static int mouseEventCnt = 0;
Mat frame;
Mat startingframe;
Mat perfectframe;
Mat endframe;
char text[255];
char text1[255];
	
void mouseEvent(int evt, int x, int y, int flags, void* param) { // To get the co-ordinates of a point on a mouseclick

   if (evt == CV_EVENT_LBUTTONDOWN) {  // First point on the diagonal
      mouseEventCnt = mouseEventCnt + 1;
      if (mouseEventCnt%2 ==1) {
                 printf("%d %d\n", x, y);
		 Rectanglep1.x = x;
		 Rectanglep1.y = y;
		 Rectanglep1x = Rectanglep1.x;
		 Rectanglep1y = Rectanglep1.y;

		}
      if (mouseEventCnt%2 ==0) { // Second point on the diagonal
                 printf("\n%d %d\n", x, y);
		 Rectanglep2.x = x;
		 Rectanglep2.y = y;
		 Rectanglep2x = Rectanglep2.x;
		 Rectanglep2y = Rectanglep2.y;

		}
	}
}

int main(char argc, char**argv) {
	VideoCapture cap(argv[1]);                            // open the video file for reading
	if (!cap.isOpened())  {                              // if not success, exit program
		cout << "Cannot open the video file" << endl;
		return -1;
	}
	int dstWidth = frame.cols * 2;
	int dstHeight = frame.rows * 2;
	double fps = cap.get(CV_CAP_PROP_FPS);               //get the frames per seconds of the video
	cout << "Frame per seconds : " << fps << endl;
	namedWindow("MyVideo", CV_WINDOW_AUTOSIZE);           //create a window called "MyVideo"
	double NumberOfFrames = cap.get(CV_CAP_PROP_FRAME_COUNT);

	for (int i = 1; i <= NumberOfFrames; i++) {
		bool bSuccess = cap.read(frame);                  // read a new frame from video

		if (!bSuccess) {                                  //if not success, break loop
			cout << "Cannot read the frame from video file" << endl;
			break;
		}

		sprintf(text, " Frame Number:%d", (int)i);
		putText(frame, text, cvPoint(640, 30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 0), 1, CV_AA);
		imshow("MyVideo", frame);                         //show the frame in "MyVideo" window

		if ((waitKey(10) == 97) || (waitKey(10) == 65)) {           //Press 'a' or 'A' to get starting frame
			startingframe = frame;
			cout << "starting frame" << i << '\n';
			startframenumber = i;
			imshow("Starting frame", startingframe);
		}
		if ((waitKey(10) == 98) || (waitKey(10) == 66)) {            //Press 'b' or 'B' to get perfect frame
			perfectframe = frame;
			cout << "perfect frame :" << i << '\n';
			perfectframenumber = i;
			imshow("Perfect frame", perfectframe);
			cvSetMouseCallback("Perfect frame", mouseEvent, &perfectframe);
		}
		if (waitKey(10) == 102) {                                     //Press 'f' to get rectangle co-ordinates
			sprintf(text1, " Rect:%d %d , %d %d",Rectanglep1x,Rectanglep1y,Rectanglep2x,Rectanglep2y );
			putText(perfectframe, text1, cvPoint(600, 60), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 0), 1, CV_AA);
			imshow("Rect", perfectframe);
		}
		if ((waitKey(10) == 99) || (waitKey(10) == 67)) {             //Press 'c' or 'C' to get end frame
			cout << "end frame" << i << '\n';
			endframenumber = i;
			waitKey(0);
		}
		if ((waitKey(10) == 100) || (waitKey(10) == 68)) {             //Press 'd' or 'D' to move frames backward
			double frame2 = cap.get(CV_CAP_PROP_POS_FRAMES);
			cap.set(CV_CAP_PROP_POS_FRAMES, frame2 - 20);
			i = i - 20;
			continue;
		}
		if ((waitKey(10) == 101) || (waitKey(10) == 69)) {             //Press 'e' or 'E' to move frames forward
			double frame2 = cap.get(CV_CAP_PROP_POS_FRAMES);
			cap.set(CV_CAP_PROP_POS_FRAMES, frame2 + 20);
			i = i + 20;
			continue;
		}
		if (waitKey(10) == 103) {                                     //Press 'g' to get rectangle co-ordinates
			sprintf(text1, " Starting frame:%d, Perfectframe=%d, Endframe=%d ",startframenumber,perfectframenumber,endframenumber );
			putText(perfectframe, text1, cvPoint(300, 60), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 0), 1, CV_AA);
			sprintf(text1, " Rect:%d %d , %d %d", Rectanglep1x, Rectanglep1y, Rectanglep2x, Rectanglep2y);
			putText(perfectframe, text1, cvPoint(400, 30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 0), 1, CV_AA);
			imshow("Frame Numbers and Rectangle", perfectframe);
		}

		if (waitKey(10) == 27) {                                      // Press 'esc' to stop
			cout << "esc key is pressed by user" << endl;
			break;
		}
		waitKey(1000);
	}
	return 0;
}


