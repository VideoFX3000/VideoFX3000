#ifndef LOOPEREFFECT_H
#define LOOPEREFFECT_H

#include "VideoEngine.h"

class LooperEffect : public VideoEngine
{
public:
	LooperEffect(void);
	~LooperEffect(void);
	void loopInputCheck(int input);
	void loopVideo();
	virtual void showVideoFrame(const cv::Mat& videoFrame);
	virtual void processFrame(const cv::Mat& videoFrame, cv::Mat& processedFrame);
	virtual void showProcessedFrame(const cv::Mat&processedFrame);
};

#endif



