#ifndef EFFECT_H
#define EFFECT_H

#include <opencv2/opencv.hpp>
#include "ToolInterface.h"
#include <iostream>
#include <conio.h> //f�r kbhit()

class Effect
{
public:
	virtual ~Effect(void){}
	virtual void setTool(ToolInterface* tool) = 0; //�BERLEGUNG: diese Funktion in VideoEngine.h eingliedern und auch aus den Unterklassen der Effekte entfernen
};

#endif
