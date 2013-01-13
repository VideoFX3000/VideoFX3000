#ifndef LOOPEREFFECT_H
#define LOOPEREFFECT_H

#include "Effect.h"

// Diese Klasse wird ben�tigt, um einen Loop ohne eine Bildbearbeitung mit dem urspr�nglichen
// Video durchf�hren zu k�nnen.

class LooperEffect : public Effect
{
public:
	LooperEffect(void);
	virtual ~LooperEffect(void);
	virtual void setTool(ToolInterface *tool);// f�hrt keine Operationen durch
	virtual void initialize(int frameWidth, int frameHeight); // f�hrt keine Operationen durch
	virtual cv::Mat processFrame(cv::Mat videoFrame); // f�hrt keine Operationen durch
};

#endif



