// Fertig

#ifndef HIGHPASS_H
#define HIGHPASS_H

#include "ToolInterface.h"

// Diese Klasse f�hrt mit dem �bergebenen Mat-Objekt eine Kantenerkennung durch
// Die Kanten werden anhand hoher Frequenzen mit der Sobel-Funktion erkannt

class HighPass : public ToolInterface
{
public:
	HighPass(void);
	~HighPass(void);
	virtual cv::Mat process(cv::Mat& input, int delta);
private:
	// Schwellwert f�r Hochpass
	int delta;
};

#endif