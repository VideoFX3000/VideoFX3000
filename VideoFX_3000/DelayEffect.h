// FERTIG

#ifndef DELAYEFFECT_H
#define DELAYEFFECT_H

#include "Effect.h"
#include "VideoRingBuffer.h"

// Die Klasse DelayEffect dient dazu im Zusammenwirken mit der Klasse VideoRingBuffer Frames zeitversetzt
// auszulesen und definierte Bereiche in das aktuelle Frame einzuf�gen, sodass ein Nachzieheffekt entsteht.

// Die Gr��e des aktuellen Delayfensters kann bis zur Gr��e MAX_DELAY_WINDOW per
// Benutzereingabe angepasst werden, au�erdem kann auch der Abstand der Frames zueinander (also die Anzahl der
// verz�gerten Frames) variiert werden.

class DelayEffect :	public Effect
{
public:
	DelayEffect(void);
	virtual ~DelayEffect(void);
	// Grundlegende Methode um das notwendige Tool der Basisklasse ToolInterface zu definieren, welches
	// verwendet werden soll
	virtual void setTool(ToolInterface *tool);
	// Methode um die Framebreite und -h�he sowie die Gr��e des Delays und des Buffers in der Klasse
	// zuzuweisen
	virtual void initialize(int frameWidth, int frameHeight); // f�hrt keine Operationen mit frameWidth
	// und frameHeight durch, Parameter sind aber notwendig
	// Methode, in der die Verarbeitungen durchgef�hrt werden
	virtual cv::Mat processFrame(cv::Mat currentFrame);
private:
	// Z�hlvariable, die hochgez�hlt wird
	int frameNumber;
	// Gr��e des aktuellen Delayfensters
	int delayWindow;
	// Gr��e des Abstandes der Frames zueinander
	int frameDistance;
	int numberOfDelayedFrames;
	// Pointer vom Typ ToolInterface
	ToolInterface *tool;
	// Variable vom Typ VideoRingBuffer um die Verarbeitungen in dieser Klasse durchf�hren zu k�nnen
	VideoRingBuffer buffer;
};

#endif

