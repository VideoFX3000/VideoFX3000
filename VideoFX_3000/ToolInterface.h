#ifndef TOOLINTERFACE_H
#define TOOLINTERFACE_H

#include <opencv2/opencv.hpp>

// Die Klasse "ToolInterface" (Abstrakte Klasse (=nur virtuelle Methoden), deshalb kein Konstruktor) dient als Schnittstelle
// zwischen der Klasse "Effect" und den grundlegenden Funktionalitäten (Tools), die vom jeweiligen Effekt verwendet werden,
// z. B. wird für den Effekt "DelayEffect" das Tool "Backgroundsubstraction" verwendet. Da es sich bei "ToolInterface" um eine
// abstrakte Klasse handelt wird keine weitere .cpp-Datei für die Methodenimplementation benötigt.

// ToolInterface ist Basisklasse aller Tools.

class ToolInterface
{
public:
	virtual ~ToolInterface(void){};
	// abstrakte Methode, die von der gleichnamigen Methode der Unterklasse aufgerufen und überschrieben wird
	virtual cv::Mat process(cv::Mat& input, int delta) = 0;
};

#endif
