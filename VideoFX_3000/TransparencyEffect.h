#ifndef TRANSPARENCYEFFECT_H
#define TRANSPARENCYEFFECT_H

#include "Effect.h"

// Stellt ein bewegtes Objekt mit veränderbarem Alphakanal dar.
// Der Nutzer kann mit einem Regler den Alphawert des bewegten Objekts ändern

class TransparencyEffect :	public Effect
{
public:
	TransparencyEffect(void);
	virtual ~TransparencyEffect(void);
	virtual void setTool(ToolInterface *tool);
	virtual void initialize(int frameWidth, int frameHeight);
	virtual cv::Mat processFrame(cv::Mat input);
private:
	// Zählvariable, die hochgezählt wird
	int frameNumber;
	// Alpha-Kanal
	float alpha;
	// Pointer vom Typ ToolInterface
	ToolInterface *tool;
	cv::Mat firstFrame;
};

#endif

