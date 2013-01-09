#ifndef GHOSTEFFECT_H
#define GHOSTEFFECT_H

#include "Effect.h"
#include "VideoRingBuffer.h"

// Die Klasse GhostEffect erzeugt einen "Nachblendeffekt" bei dem verzögerte Frames ausblenden und einen "Schweif" bilden.
// Dabei kann der Nutzer den Bereich der verzögerten Frames bestimmen und zusätzlich wie viele Frames in diesem Bereich verwendet werden

class GhostEffect : public Effect
{
public:
	GhostEffect(void);
	virtual ~GhostEffect(void);
	// Grundlegende Methode um das notwendige Tool der Basisklasse ToolInterface zu definieren, welches verwendet werden soll
	virtual void setTool(ToolInterface *tool);
	// Methode um die Framebreite und -höhe sowie die Größe des Delays und des Buffers in der Klasse zuzuweisen
	virtual void initialize(int frameWidth, int frameHeight); // frameWidth und frameHeight werden aktuell noch nicht benötigt
	// Methode, in der die Verarbeitungen durchgeführt werden
	virtual cv::Mat processFrame(cv::Mat currentFrame);
private:
	int frameWidth;
	int frameHeight;
	// Zählvariable, die hochgezählt wird
	int frameNumber;
	// Größe des aktuellen Delayfensters
	int ghostWindow;
	// Größe des Abstandes der Frames zueinander
	int frameDistance;
	int numberOfDelayedFrames;
	// Pointer vom Typ ToolInterface
	ToolInterface *tool;
	// Variable vom Typ VideoRingBuffer um die Verarbeitungen in dieser Klasse durchführen zu können
	VideoRingBuffer buffer;
};
#endif



