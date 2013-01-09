#ifndef TRANSPARENCYEFFECT_H
#define TRANSPARENCYEFFECT_H

#include "Effect.h"

class TransparencyEffect :	public Effect
{
public:
	TransparencyEffect(void);
	virtual ~TransparencyEffect(void);
	virtual void setTool(ToolInterface *tool);
	virtual void initialize(int frameWidth, int frameHeight);
	virtual cv::Mat processFrame(cv::Mat input);
private:
	int frameWidth;
	int frameHeight;
	// Zählvariable, die hochgezählt wird
	int frameNumber;
	// Alpha-Kanal
	float alpha;
	// Pointer vom Typ ToolInterface
	ToolInterface *tool;
	cv::Mat firstFrame;
};

#endif

