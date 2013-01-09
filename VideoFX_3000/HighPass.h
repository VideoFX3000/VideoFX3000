#ifndef HIGHPASS_H
#define HIGHPASS_H

#include "ToolInterface.h"

class HighPass : public ToolInterface
{
public:
	HighPass(void);
	~HighPass(void);
	virtual cv::Mat process(cv::Mat& input, int delta);
private:
	// Schwellwert für Hochpass
	int delta;
};

#endif