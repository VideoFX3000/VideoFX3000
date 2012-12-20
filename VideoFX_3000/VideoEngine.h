#ifndef __VIDEOENGINE_H
#define __VIDEOENGINE_H
#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <conio.h> //f�r kbhit()
#include "ToolInterface.h"
#include "LooperEffect.h"
#include "Backgroundsubstraction.h"

class VideoEngine
{
public:
	VideoEngine();
	virtual ~VideoEngine(void);
	bool openVideo(const std::string& path, const int& effectType);
	void runVideo();
	//Grundlegende Verarbeitungsfunktionen
	void writeVideo(const cv::Mat& videoFrame);
	void stopVideo(const cv::Mat& videoFrame);
	//Anzeige-Funktionen
	void showVideoFrame(const cv::Mat& videoFrame);
	void showProcessedFrame(const cv::Mat&processedFrame);
	//Ringbuffer-Funktionen
	void write(const cv::Mat& videoFrame);
	cv::Mat readWithDelay(int delay);
	void resize(int size);
public:
	cv::VideoCapture videoCapture;
	int frameWidth;
	int frameHeight;
	int frameNumber;
	float frameRate;
	int input;
	int effectType;
	cv::VideoWriter videoWriter;
	//ToolInterface* tool; //wird momentan erst in LooperEffect.h gebraucht
	bool writerCheck;
	bool firstCall;
	LooperEffect loop;
	//Ringbuffer-Funktionen
	std::vector<cv::Mat> buffer;
	int writeIndex;
	int size;
};

#endif