// Fertig

#ifndef _BACKGROUNDSUBSTRACTION_H
#define _BACKGROUNDSUBSTRACTION_H

#include "ToolInterface.h"

// Diese Klasse erkennt die gr��te sich bewegende Fl�che und erstellt eine Bin�rmaske

class Backgroundsubstraction : public ToolInterface //bedeutet: ToolInterface ist die Basisklasse von Backgroundsub
{
public:
	Backgroundsubstraction(void);
	virtual~Backgroundsubstraction(void);
	virtual cv::Mat process(cv::Mat& input, int delta);
private:
	cv::Mat firstFrame;
	int frameNumber;
};

#endif