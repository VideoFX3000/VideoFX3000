#ifndef LOOPEREFFECT_H
#define LOOPEREFFECT_H

#include "Effect.h"

// Diese Klasse wird benötigt, um einen Loop ohne eine Bildbearbeitung mit dem ursprünglichen
// Video durchführen zu können.

class LooperEffect : public Effect
{
public:
	LooperEffect(void);
	virtual ~LooperEffect(void);
	virtual void setTool(ToolInterface *tool);// führt keine Operationen durch
	virtual void initialize(int frameWidth, int frameHeight); // führt keine Operationen durch
	virtual cv::Mat processFrame(cv::Mat videoFrame); // führt keine Operationen durch
};

#endif



