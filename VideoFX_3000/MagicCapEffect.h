// Fertig

#ifndef MAGICCAPEFFECT_H
#define MAGICCAPEFFECT_H

#include "Effect.h"

// Benutzt die process-Funktion aus der Klasse Backgroundsubstraction, um eine Bin�rmaske zu erstellen
// Schneidet das bewegte Objekt aus dem Video aus
// Der Nutzer kann das Objekt mit R-, G-, B-Reglern einf�rben

class MagicCapEffect : public Effect
{
public:
	MagicCapEffect(void);
	virtual ~MagicCapEffect(void);
	virtual void setTool(ToolInterface *tool);
	virtual void initialize(int frameWidth, int frameHeight);
	virtual cv::Mat processFrame(cv::Mat input);
private:
	// Z�hlvariable, die hochgez�hlt wird
	int frameNumber;
	// Pointer vom Typ ToolInterface
	ToolInterface *tool;
	cv::Mat firstFrame;
	// Werte aus der Trackbar
	int capIntensityR;
	int capIntensityG;
	int capIntensityB;
	int capIntensityRGB;
};

#endif

