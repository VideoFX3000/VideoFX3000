// Fertig

#ifndef HIGHPASS_H
#define HIGHPASS_H

#include "ToolInterface.h"

// Diese Klasse führt mit dem übergebenen Mat-Objekt eine Kantenerkennung durch
// Die Kanten werden anhand hoher Frequenzen mit der Sobel-Funktion erkannt

class HighPass : public ToolInterface
{
public:
	HighPass(void);
	~HighPass(void);
	virtual cv::Mat process(cv::Mat& input, int delta);
private:
	// Schwellwert für Hochpass
	int delta;
};

#endif