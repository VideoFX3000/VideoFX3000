#ifndef __VIDEOENGINE_H
#define __VIDEOENGINE_H
#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <conio.h> //für kbhit()


class VideoEngine
{
public:
	VideoEngine();
	virtual ~VideoEngine(void);
	char getInput();
	bool openVideo(const std::string& path, const int& effectType);
	void runVideo();
	void writeVideo(const cv::Mat& videoFrame);
	void stopVideo(const cv::Mat& videoFrame);
	void loopVideo();
	virtual void showVideoFrame(const cv::Mat& videoFrame);
	virtual void processFrame(const cv::Mat& videoFrame, cv::Mat& processedFrame);
	virtual void showProcessedFrame(const cv::Mat&processedFrame);
	//Ringbuffer-Funktionen
	void write(const cv::Mat& videoFrame);
	cv::Mat readWithDelay(int delay);
	void resize(int size);
protected:
	cv::VideoCapture videoCapture;
	int frameWidth;
	int frameHeight;
	int frameNumber;
	int frameRate;
	int input;
	int effectType;
	cv::VideoWriter videoWriter;
	bool writerCheck;
	bool firstCall;
	//Ringbuffer-Funktionen
	std::vector<cv::Mat> buffer;
	int writeIndex;
	int size;
};

#endif