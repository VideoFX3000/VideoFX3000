//Fertig

#ifndef HIGHPASSEFFECT_H
#define HIGHPASSEFFECT_H
#include "Effect.h"

// Diese Klasse verwendet die in HighPass definierte Funktion
// zur Erkennung von Kanten durch Analyse der Frequenzen im Bild

class HighPassEffect : public Effect
{
public:
	HighPassEffect(void);
	virtual ~HighPassEffect(void);
	// Grundlegende Methode um das notwendige Tool der Basisklasse ToolInterface zu definieren, welches verwendet werden soll
	virtual void setTool(ToolInterface *tool);
	// Methode um die Framebreite und -höhe sowie die Größe des Delays und des Buffers in der Klasse zuzuweisen
	virtual void initialize(int frameWidth, int frameHeight); // frameWidth und frameHeight werden aktuell noch nicht benötigt
	// Methode, in der die Verarbeitungen durchgeführt werden
	virtual cv::Mat processFrame(cv::Mat currentFrame);
private:
	// Pointer vom Typ ToolInterface
	ToolInterface *tool;
	int delta;
};
#endif
