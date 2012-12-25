#ifndef DELAYEFFECT_H
#define DELAYEFFECT_H

#include "Effect.h"
#include "VideoRingBuffer.h"

// Die Klasse DelayEffect dient dazu im Zusammenwirken mit der Klasse VideoRingBuffer Frames zeitversetzt
// auszulesen und definierte Bereiche in das aktuelle Frame einzufügen, sodass ein Nachzieheffekt entsteht.

// Später ist auch angedacht, die Größe des aktuellen Delayfensters bis zu der Größe MAX_DELAY_WINDOW per
// Benutzereingabe anzupassen, außerdem soll auch der Abstand der Frames zueinander (also die Anzahl der
// verzögerten Frames) variabel sein.

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
	void initialize(int frameWidth, int frameHeight); // frameWidth und frameHeight werden aktuell noch nicht benötigt
	// Methode, in der die Verarbeitungen durchgeführt werden
	cv::Mat processFrame(cv::Mat currentFrame);
	//void process(float* input, float*output, int numberOfSamples);
private:
	int frameWidth;
	int frameHeight;
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

