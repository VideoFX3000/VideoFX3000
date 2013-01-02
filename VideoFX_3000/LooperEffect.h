#ifndef LOOPEREFFECT_H
#define LOOPEREFFECT_H

#include "Effect.h"

class LooperEffect : public Effect
{
public:
	LooperEffect(void);
	virtual ~LooperEffect(void);
	void loopInputCheck(int input);
	void loopVideo();
	//cv::Mat processFrame(cv::Mat& videoFrame); //Funktion dient nur zum Testen wie process in BackSub aufgerufen werden kann.
	virtual void setTool(ToolInterface *tool);
	void initialize(int frameWidth, int frameHeight); //ÜBERLEGUNG: Funktion dient pro Effekt (unterschiedliche Übergabeparameter) dazu die notwendigen Parameter des Videos zu erfassen (cols, rows, fps, etc.)
private:
	int frameWidth;
	int frameHeight;
	ToolInterface *tool;
};

#endif



