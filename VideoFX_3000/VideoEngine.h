#ifndef __VIDEOENGINE_H
#define __VIDEOENGINE_H
#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <conio.h> //für kbhit()
#include <stdlib.h>
#include "Effect.h"
//#include "ToolInterface.h"
//#include "Backgroundsubstraction.h"
#include "LooperEffect.h"
#include "DelayEffect.h"
#include "MagicCapEffect.h"
#include "GhostEffect.h"
#include "HighPassEffect.h"
#include "TransparencyEffect.h"

class VideoEngine
{
public:
	VideoEngine();
	virtual ~VideoEngine(void);
	void setEffect(Effect *effect);
	bool openVideo(const std::string& path, std::string effectType);
	char runVideo();
	//Grundlegende Verarbeitungsfunktionen
	void writeVideo(const cv::Mat& videoFrame);
	void stopVideo(const cv::Mat& videoFrame);
	//Anzeige-Funktionen
	void showVideoFrame(const cv::Mat& videoFrame);
	void showProcessedFrame(const cv::Mat&processedFrame);
	char loopInputCheck(char input, int delayTime);
	char loopVideo(int delayTime);
private:
	cv::VideoCapture videoCapture;
	int frameWidth;
	int frameHeight;
	int frameNumber;
	float frameRate;
	//std::string& videoCodec;
	char input;
	cv::VideoWriter videoWriter;
	bool writerCheck;
	bool recorderCheck;
	Effect *effect;
	int delayTime;
	int bufferSize;
	std::string loopRecordedVideoName;
	char loopRecordedVideoNameCounter;
	std::string effectType;
	VideoRingBuffer bufferLooper;
};

#endif