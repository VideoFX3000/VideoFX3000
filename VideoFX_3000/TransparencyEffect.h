// Fertig

#ifndef TRANSPARENCYEFFECT_H
#define TRANSPARENCYEFFECT_H

#include "Effect.h"

// Benutzt die process-Funktion aus der Klasse Backgroundsubstraction, um eine Bin�rmaske zu erstellen
// Der Nutzer kann mit einem Regler den Alphawert des bewegten Objekts �ndern

class TransparencyEffect :	public Effect
{
public:
	TransparencyEffect(void);
	virtual ~TransparencyEffect(void);
	virtual void setTool(ToolInterface *tool);
	virtual void initialize(int frameWidth, int frameHeight);
	virtual cv::Mat processFrame(cv::Mat input);
private:
	// Z�hlvariable, die hochgez�hlt wird
	int frameNumber;
	// Alpha-Kanal
	float alpha;
	// Pointer vom Typ ToolInterface
	ToolInterface *tool;
	cv::Mat firstFrame;
};

#endif

