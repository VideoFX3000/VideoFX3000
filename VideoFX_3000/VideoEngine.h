#ifndef __VIDEOENGINE_H
#define __VIDEOENGINE_H
#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <conio.h> //für kbhit()
#include <stdlib.h>
#include "ToolInterface.h"
#include "Backgroundsubstraction.h"
#include "LooperEffect.h"
#include "DelayEffect.h"
#include "MagicCapEffect.h"

class VideoEngine
{
public:
	VideoEngine();
	virtual ~VideoEngine(void);
	bool openVideo(const std::string& path, const char& effectType);
	void runVideo();
	//Grundlegende Verarbeitungsfunktionen
	void writeVideo(const cv::Mat& videoFrame);
	void stopVideo(const cv::Mat& videoFrame);
	//Anzeige-Funktionen
	void showVideoFrame(const cv::Mat& videoFrame);
	void showProcessedFrame(const cv::Mat&processedFrame);
private:
	cv::VideoCapture videoCapture;
	int frameWidth;
	int frameHeight;
	int frameNumber;
	float frameRate;
	int input;
	char effectType;
	cv::VideoWriter videoWriter;
	//ToolInterface* tool; //wird momentan erst in LooperEffect.h gebraucht
	bool writerCheck;
	bool firstCall;
	LooperEffect loop;
	DelayEffect delay;
	MagicCapEffect magic;
};

#endif