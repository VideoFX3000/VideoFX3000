// Fertig

#ifndef MAGICCAPEFFECT_H
#define MAGICCAPEFFECT_H

#include "Effect.h"

// Benutzt die process-Funktion aus der Klasse Backgroundsubstraction, um eine Binärmaske zu erstellen
// Schneidet das bewegte Objekt aus dem Video aus
// Der Nutzer kann das Objekt mit R-, G-, B-Reglern einfärben

class MagicCapEffect : public Effect
{
public:
	MagicCapEffect(void);
	virtual ~MagicCapEffect(void);
	virtual void setTool(ToolInterface *tool);
	virtual void initialize(int frameWidth, int frameHeight);
	virtual cv::Mat processFrame(cv::Mat input);
private:
	// Zählvariable, die hochgezählt wird
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

