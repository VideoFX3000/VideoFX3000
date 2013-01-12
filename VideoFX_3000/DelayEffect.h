// FERTIG

#ifndef DELAYEFFECT_H
#define DELAYEFFECT_H

#include "Effect.h"
#include "VideoRingBuffer.h"

// Die Klasse DelayEffect dient dazu im Zusammenwirken mit der Klasse VideoRingBuffer Frames zeitversetzt
// auszulesen und definierte Bereiche in das aktuelle Frame einzufügen, sodass ein Nachzieheffekt entsteht.

// Die Größe des aktuellen Delayfensters kann bis zur Größe MAX_DELAY_WINDOW per
// Benutzereingabe angepasst werden, außerdem kann auch der Abstand der Frames zueinander (also die Anzahl der
// verzögerten Frames) variiert werden.

class DelayEffect :	public Effect
{
public:
	DelayEffect(void);
	virtual ~DelayEffect(void);
	// Grundlegende Methode um das notwendige Tool der Basisklasse ToolInterface zu definieren, welches
	// verwendet werden soll
	virtual void setTool(ToolInterface *tool);
	// Methode um die Framebreite und -höhe sowie die Größe des Delays und des Buffers in der Klasse
	// zuzuweisen
	virtual void initialize(int frameWidth, int frameHeight); // führt keine Operationen mit frameWidth
	// und frameHeight durch, Parameter sind aber notwendig
	// Methode, in der die Verarbeitungen durchgeführt werden
	virtual cv::Mat processFrame(cv::Mat currentFrame);
private:
	// Zählvariable, die hochgezählt wird
	int frameNumber;
	// Größe des aktuellen Delayfensters
	int delayWindow;
	// Größe des Abstandes der Frames zueinander
	int frameDistance;
	int numberOfDelayedFrames;
	// Pointer vom Typ ToolInterface
	ToolInterface *tool;
	// Variable vom Typ VideoRingBuffer um die Verarbeitungen in dieser Klasse durchführen zu können
	VideoRingBuffer buffer;
};

#endif

