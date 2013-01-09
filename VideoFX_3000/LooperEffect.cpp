#include "LooperEffect.h"
#include <iostream>
using namespace std;
using namespace cv;

LooperEffect::LooperEffect(void)
	: frameWidth(0)
	, frameHeight(0)
	, tool(0)
{
}

LooperEffect::~LooperEffect(void)
{
}

void LooperEffect::setTool(ToolInterface *tool){
}

void LooperEffect::initialize(int frameWidth, int frameHeight){
}

Mat LooperEffect::processFrame(Mat processedFrame){
	return processedFrame;
}