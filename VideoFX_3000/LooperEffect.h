// FERTIG

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
	// Grundlegende Methode um das notwendige Tool der Basisklasse ToolInterface zu definieren, welches
	// verwendet werden soll
	virtual void setTool(ToolInterface *tool);
	virtual void initialize(int frameWidth, int frameHeight); // f�hrt keine Operationen durch
	virtual cv::Mat processFrame(cv::Mat videoFrame); // f�hrt keine Operationen durch
};

#endif



