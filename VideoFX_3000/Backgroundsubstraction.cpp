#include "Backgroundsubstraction.h"
#include <vector>
using namespace cv;
using namespace std;

Backgroundsubstraction::Backgroundsubstraction(void){
	namedWindow("Video");
	namedWindow("Result");
	namedWindow("First");
	namedWindow("Gray");
	namedWindow("Diff");
	namedWindow("Trafo");
}

Backgroundsubstraction::~Backgroundsubstraction(void){
	destroyAllWindows();
}
void Backgroundsubstraction::showVideoFrame(const cv::Mat& videoFrame){
	imshow("Video", videoFrame);
}
void Backgroundsubstraction::processFrame(const cv::Mat& videoFrame, cv::Mat& processedFrame){
	Mat grayFrame (frameHeight, frameWidth, CV_16UC1);
	Mat originalGray;

	cvtColor(videoFrame, grayFrame, CV_BGR2GRAY);
		
	grayFrame.copyTo(originalGray);
	
	if (frameNumber % 5 == 0)
	{
		grayFrame.copyTo(firstFrame);
	}	

	if (frameNumber < 6)
	{
		grayFrame.copyTo(processedFrame);
	}
	else
	{
//		grayFrame = firstFrame - grayFrame;
		absdiff(grayFrame, firstFrame, grayFrame);

		int thresh = getTrackbarPos("Thresh", "Video");
		threshold(grayFrame, processedFrame, thresh, 255, THRESH_BINARY);
		imshow("Diff", grayFrame);
	}

	medianBlur(processedFrame, processedFrame, 3);
	// Opening (entfernt Rauschen im Hintergrund / schließt Löcher im Hintergrund) --> erode, dilate
	// Closing (schließt Löcher im Vordergrund) --> dilate, erode
//	erode(processedFrame, processedFrame, Mat(3, 3, CV_8UC1));
	dilate(processedFrame, processedFrame, Mat(3, 3, CV_16UC1));
	erode(processedFrame, processedFrame, Mat(3, 3, CV_16UC1));

	Mat copyOfFrame;

	vector<vector<Point> > contours;
	processedFrame.copyTo(copyOfFrame);
	findContours(copyOfFrame, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	
	int area;
	int maxArea = 0;
	int maxAreaIndex = 0;

	for(int indexOfRegion = 0; indexOfRegion < contours.size(); indexOfRegion++)
	{
		vector<Point> contour = contours[indexOfRegion];
		area = contourArea(contour);

		if(area > maxArea)
		{
			maxArea = area;
			maxAreaIndex = indexOfRegion;
		}

	}

	for(int indexOfRegion = 0; indexOfRegion < contours.size(); indexOfRegion++)
	{
		if(indexOfRegion == maxAreaIndex)
		{
			drawContours(processedFrame, contours, indexOfRegion, 255, CV_FILLED);
		}
		else
		{
			drawContours(processedFrame, contours, indexOfRegion, 0, CV_FILLED);
		}

	}

	imshow("Gray", originalGray);
	
}
void Backgroundsubstraction::showProcessedFrame(const cv::Mat&processedFrame){
	imshow("Result", processedFrame);
	if(frameNumber > 4)
	imshow("First", firstFrame);
}
