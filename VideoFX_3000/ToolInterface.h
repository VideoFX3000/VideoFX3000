#ifndef TOOLINTERFACE_H
#define TOOLINTERFACE_H

#include "VideoEngine.h"

class ToolInterface
{
public:
	ToolInterface(void);
	virtual ~ToolInterface(void);
	virtual cv::Mat process(cv::Mat& input) = 0;
};

#endif
