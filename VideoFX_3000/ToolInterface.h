#ifndef TOOLINTERFACE_H
#define TOOLINTERFACE_H

#include <opencv2/opencv.hpp>

class ToolInterface
{
public:
	virtual ~ToolInterface(void){};
	virtual cv::Mat process(cv::Mat& input) = 0;
};

#endif
