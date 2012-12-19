#include "LooperEffect.h"
#include <iostream>

using namespace std;
using namespace cv;

LooperEffect::LooperEffect(void)
{
	VideoEngine video;
	video.setTool(new Backgroundsubstraction());
}


LooperEffect::~LooperEffect(void)
{
}

void LooperEffect::loopInputCheck(int input){
	if(input == 'l')
		loopVideo();
	waitKey(30);
}

void LooperEffect::loopVideo(){

	cout << "---looping" << endl;
	char abfrage = '0';
	VideoCapture loopedVideo;
	loopedVideo.open("Video.avi");
	do{
		if(kbhit()){
			abfrage = getch();
			input = abfrage;
		}
		Mat videoFrame (frameHeight, frameWidth, CV_8UC3);
		if (loopedVideo.read(videoFrame) == false)
			break;
		showVideoFrame(videoFrame);
		waitKey(30);
	}while(abfrage != 'q');
}
void LooperEffect::showVideoFrame(const Mat&videoFrame){
	imshow("Video", videoFrame);
}
void LooperEffect::processFrame(const Mat&videoFrame, Mat& processedFrame){

}
void LooperEffect::showProcessedFrame(const Mat&processedFrame){
	imshow("Result", processedFrame);
}