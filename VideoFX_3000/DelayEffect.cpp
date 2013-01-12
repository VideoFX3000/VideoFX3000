// Fertig

#include "DelayEffect.h"
#include "Backgroundsubstraction.h"
#include <iostream>
#include <math.h>
using namespace std;
using namespace cv;

// Maximale Gr��e des Delayfensters
const int MAX_DELAY_WINDOW = 200;
const string windowName = "Delayed";
const string frameTrackbarName = "Frames";
const string windowTrackbarName = "Windows";

DelayEffect::DelayEffect(void)
	// Initialisierung der Member-Variablen
	: frameNumber(0)
	, delayWindow(0)
	, numberOfDelayedFrames(0)
	, frameDistance(1)
{
	setTool(new Backgroundsubstraction());// Auswahl des Tools f�r die Verarbeitung
}

DelayEffect::~DelayEffect(void)
{
}

// Grundlegende Methode um das notwendige Tool der Basisklasse ToolInterface zu definieren, welches
// verwendet werden soll
void DelayEffect::setTool(ToolInterface *tool){
	this->tool = tool;
}

// Methode um die Framebreite und -h�he sowie die Gr��e des Delays und des Buffers in der Klasse
// zuzuweisen
void DelayEffect::initialize(int frameWidth, int frameHeight){
	namedWindow(windowName);
	this->delayWindow = 20; // vom Benutzer steuerbar
	this->numberOfDelayedFrames = 6; // vom Benutzer steuerbar
	// Slider um die Anzahl der verz�gerten Frames einzustellen
	createTrackbar(frameTrackbarName, windowName, 0, delayWindow);
	setTrackbarPos(frameTrackbarName, windowName, numberOfDelayedFrames);
	// Slider um die Fenstergr��e einzustellen
	createTrackbar(windowTrackbarName, windowName, 0, MAX_DELAY_WINDOW);
	setTrackbarPos(windowTrackbarName, windowName, delayWindow);
	buffer.resizeBuffer(MAX_DELAY_WINDOW); // Gr��e des Buffers setzen
}

// Methode, in der die Verarbeitungen durchgef�hrt werden
Mat DelayEffect::processFrame(Mat currentFrame){
	Mat binaryMask;
	Mat originalFrame;

	frameNumber++;
	buffer.writeBuffer(currentFrame); // schreibt aktuelles Frame in den Buffer

	// Zum Abfangen des ersten Frames (Hintergrund) notwendiger Aufruf von BackSub
	if (frameNumber <= 2){
		binaryMask = tool->process(currentFrame, 0); // erzeugt Bin�rmaske des Hintergrundes (Dient zur Synchronisation von frameNumber)
	}

	//----------Konfiguration der Regler, damit nur sinnvolle Werte eingestellt werden k�nnen---------------
	// Einstellung der gew�nschten Zeit-Fenstergr��e
	delayWindow = getTrackbarPos(windowTrackbarName, windowName);
	if(delayWindow <= numberOfDelayedFrames && numberOfDelayedFrames > 0){
		delayWindow = numberOfDelayedFrames;
		setTrackbarPos(windowTrackbarName, windowName, delayWindow);
	}
	// erst wenn der Buffer komplett gef�llt ist k�nnen daraus verz�gerte Frames ausgelesen werden
	if(frameNumber >= delayWindow)
	{
		// Einstellung der gew�nschten Frameanzahl
		numberOfDelayedFrames = getTrackbarPos(frameTrackbarName, windowName); // alternativ frameDistance einstellen
		if (numberOfDelayedFrames >= delayWindow){
			numberOfDelayedFrames = delayWindow;
			setTrackbarPos(frameTrackbarName, windowName, numberOfDelayedFrames);
		}

		if(numberOfDelayedFrames > 0){
			// Berechnung des notwendigen Frameabstandes
			frameDistance = (float) delayWindow / (float) numberOfDelayedFrames;

			for(int i = 0; i < delayWindow; i+=frameDistance){
				Mat processedFrame;
				buffer.readWithDelay(delayWindow-i).copyTo(processedFrame); //liest Frame ab delayWindow Frames zuvor aus und kopiert in processedFrame
				binaryMask = tool->process(processedFrame, 0); // erzeugt Bin�rmaske des verz�gert ausgelesenen Frames
				processedFrame.copyTo(currentFrame, binaryMask); // kopiert bestimmten Bereich des verz�gerten Frames in das aktuelle Frame
			}
		}
		
		imshow(windowName, currentFrame);
	}
	return currentFrame;
}
