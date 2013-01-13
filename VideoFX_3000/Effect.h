#ifndef EFFECT_H
#define EFFECT_H

#include <opencv2/opencv.hpp>
#include "ToolInterface.h"
#include <iostream>
#include <conio.h> //f�r kbhit()

// Die Klasse "Effect" (Abstrakte Klasse (=nur virtuelle Methoden), deshalb kein Konstruktor) dient als Schnittstelle zwischen
// der Klasse "ToolInterface" und den einzelnen Effekten, z. B. wird f�r den Effekt "DelayEffect" das Tool "Backgroundsubstraction"
// verwendet. Da es sich um eine abstrakte Klasse handelt wird keine weitere .cpp-Datei f�r die Methodenimplementation ben�tigt.

// Effect ist Basisklasse aller Effekte.

class Effect
{
public:
	virtual ~Effect(void){}
	// abstrakte Methode, die von der gleichnamigen Methode der Unterklasse aufgerufen und �berschrieben wird. Dort wird das
	// jeweilige Tool, das vom Effekt verwendet werden soll gesetzt.
	virtual void setTool(ToolInterface* tool) = 0;
	// abstrakte Methode, die von der gleichnamigen Methode der Unterklasse aufgerufen und �berschrieben wird.
	virtual void initialize(int frameWidth, int frameHeight) = 0;
	// abstrakte Methode, die von der gleichnamigen Methode der Unterklasse aufgerufen und �berschrieben wird.
	virtual cv::Mat processFrame(cv::Mat currentFrame) = 0;
};

#endif
