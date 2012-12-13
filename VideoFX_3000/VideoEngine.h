#ifndef __VIDEOENGINE_H
#define __VIDEOENGINE_H
#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <conio.h> //für kbhit()
//3Horst

class VideoEngine
{
public:
	VideoEngine();
	virtual ~VideoEngine(void);
	char getInput();
	bool openVideo(const std::string& path);
	void runVideo();
	//void writeVideo();
	virtual void showVideoFrame(const cv::Mat& videoFrame);
	virtual void processFrame(const cv::Mat& videoFrame, cv::Mat& processedFrame);
	virtual void showProcessedFrame(const cv::Mat&processedFrame);
protected:
	cv::VideoCapture videoCapture;
	int frameWidth;
	int frameHeight;
	int frameNumber;
	int frameRate;
	int input;
};

#endif