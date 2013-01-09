#ifndef GHOSTEFFECT_H
#define GHOSTEFFECT_H

#include "Effect.h"
#include "VideoRingBuffer.h"

// Die Klasse GhostEffect erzeugt einen "Nachblendeffekt" bei dem verz�gerte Frames ausblenden und einen "Schweif" bilden.
// Dabei kann der Nutzer den Bereich der verz�gerten Frames bestimmen und zus�tzlich wie viele Frames in diesem Bereich verwendet werden

class GhostEffect : public Effect
{
public:
	GhostEffect(void);
	virtual ~GhostEffect(void);
	// Grundlegende Methode um das notwendige Tool der Basisklasse ToolInterface zu definieren, welches verwendet werden soll
	virtual void setTool(ToolInterface *tool);
	// Methode um die Framebreite und -h�he sowie die Gr��e des Delays und des Buffers in der Klasse zuzuweisen
	virtual void initialize(int frameWidth, int frameHeight); // frameWidth und frameHeight werden aktuell noch nicht ben�tigt
	// Methode, in der die Verarbeitungen durchgef�hrt werden
	virtual cv::Mat processFrame(cv::Mat currentFrame);
private:
	int frameWidth;
	int frameHeight;
	// Z�hlvariable, die hochgez�hlt wird
	int frameNumber;
	// Gr��e des aktuellen Delayfensters
	int ghostWindow;
	// Gr��e des Abstandes der Frames zueinander
	int frameDistance;
	int numberOfDelayedFrames;
	// Pointer vom Typ ToolInterface
	ToolInterface *tool;
	// Variable vom Typ VideoRingBuffer um die Verarbeitungen in dieser Klasse durchf�hren zu k�nnen
	VideoRingBuffer buffer;
};
#endif



