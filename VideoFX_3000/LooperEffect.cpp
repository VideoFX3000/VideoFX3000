#include "LooperEffect.h"
#include <iostream>
#include "Backgroundsubstraction.h"
using namespace std;
using namespace cv;

LooperEffect::LooperEffect(void)
	: frameWidth(0)
	, frameHeight(0)
	, tool(0)
{
	setTool(new Backgroundsubstraction());
}


LooperEffect::~LooperEffect(void)
{
}

void LooperEffect::initialize(int frameWidth, int frameHeight){
	this->frameWidth = frameWidth;
	this->frameHeight = frameHeight;
}

void LooperEffect::loopInputCheck(int input){
	if(input == 'l')
		loopVideo();
	//waitKey(30);
}

Mat LooperEffect::processFrame(cv::Mat& processedFrame){
	processedFrame = tool->process(processedFrame);
	return processedFrame;
}

void LooperEffect::loopVideo(){

	cout << "---looping" << endl;
	char abfrage = '0';
	VideoCapture loopedVideo;
	loopedVideo.open("Video.avi");
	cout << loopedVideo.isOpened() << endl;// 1: das Video kann nicht geöffnet werden
	do{
		if(kbhit()){
			abfrage = getch();
			//input = abfrage;//ÜBERLEGUNG: den Wert müssten wir an die VideoEngine-Klasse zurückgeben (vermutlich zusätzliche Funktion "char getInput()";
		}
		Mat videoFrame (frameHeight, frameWidth, CV_8UC3);
		if (loopedVideo.read(videoFrame) == false)
			break;
		imshow("Video", videoFrame);
		waitKey(30);
	}while(abfrage != 'q');
}


void LooperEffect::setTool(ToolInterface *tool){
	this->tool = tool;
}