#ifndef MAGICCAPEFFECT_H
#define MAGICCAPEFFECT_H

#include "Effect.h"

class MagicCapEffect : public Effect
{
public:
	MagicCapEffect(void);
	virtual ~MagicCapEffect(void);
	virtual void setTool(ToolInterface *tool);
	virtual void initialize(int frameWidth, int frameHeight);
	virtual cv::Mat processFrame(cv::Mat input);
private:
	int frameWidth;
	int frameHeight;
	// Zählvariable, die hochgezählt wird
	int frameNumber;
	// Pointer vom Typ ToolInterface
	ToolInterface *tool;
	cv::Mat firstFrame;
	int capIntensityR;
	int capIntensityG;
	int capIntensityB;
	float capIntensityAlpha;
};

#endif

