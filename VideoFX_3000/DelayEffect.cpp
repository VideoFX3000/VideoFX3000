#include "DelayEffect.h"
#include "Backgroundsubstraction.h"
#include <iostream>
using namespace std;
using namespace cv;

// Maximale Größe des Delayfensters
const int MAX_DELAY_WINDOW = 100;
DelayEffect::DelayEffect(void)
	// Initialisierung der Member-Variablen
	: frameWidth(0)
	, frameHeight(0)
	, frameNumber(0)
	, delayWindow(0)
	, numberOfDelayedFrames(0)
	, frameDistance(1)
{
	setTool(new Backgroundsubstraction());// Auswahl des Tools für die Verarbeitung
}


DelayEffect::~DelayEffect(void)
{
}

// Grundlegende Methode um das notwendige Tool der Basisklasse ToolInterface zu definieren, welches
// verwendet werden soll
void DelayEffect::setTool(ToolInterface *tool){
	this->tool = tool;
}

// Methode um die Framebreite und -höhe sowie die Größe des Delays und des Buffers in der Klasse
// zuzuweisen
void DelayEffect::initialize(int frameWidth, int frameHeight){
	namedWindow("Delayed");
	this->frameWidth = frameWidth;
	this->frameHeight = frameHeight;
	this->delayWindow = 20; // später vom Benutzer steuerbar
	this->numberOfDelayedFrames = 6; // vom Benutzer steuerbar
	// vorübergehend Slider um die Frameanzahl einzustellen
	createTrackbar("Frames", "Delayed", 0, delayWindow);
	setTrackbarPos("Frames", "Delayed", numberOfDelayedFrames);
	// vorübergehend Slider um die Fenstergröße einzustellen
	createTrackbar("Window", "Delayed", 0, MAX_DELAY_WINDOW);
	setTrackbarPos("Window", "Delayed", delayWindow);
	buffer.resizeBuffer(MAX_DELAY_WINDOW); // Größe des Buffers setzen
}

// Methode, in der die Verarbeitungen durchgeführt werden
Mat DelayEffect::processFrame(Mat currentFrame){
	Mat binaryMask;

	frameNumber++;
	buffer.writeBuffer(currentFrame); // schreibt aktuelles Frame in den Buffer

	// Zum Abfangen des ersten Frames (Hintergrund) notwendiger Aufruf von BackSub
	if (frameNumber <= 2){
		binaryMask = tool->process(currentFrame); // erzeugt Binärmaske des Hintergrundes
	}

	// Einstellung der gewünschten Fenstergröße
	delayWindow = getTrackbarPos("Window", "Delayed");
	// erst wenn der Buffer komplett gefüllt ist können daraus verzögerte Frames ausgelesen werden
	if(frameNumber >= delayWindow)
	{
		// Einstellung der gewünschten Frameanzahl
		numberOfDelayedFrames = getTrackbarPos("Frames", "Delayed"); // alternativ frameDistance einstellen

		if(numberOfDelayedFrames != 0){
			// Berechnung des notwendigen Frameabstandes
			frameDistance = (float) delayWindow / (float) numberOfDelayedFrames;
			// Hinzufügen der gewünschten Anzahl an verzögerten Frames (FUNKTIONIERT NUR BEI NIEDRIGER ANZAHL VON VERZÖGERTEN FRAMES KORREKT)
			for(int i = 0; i < delayWindow; i+=frameDistance){
				Mat processedFrame = buffer.readWithDelay(delayWindow-i); //liest Frame ab delayWindow Frames zuvor aus
				binaryMask = tool->process(processedFrame); // erzeugt Binärmaske des verzögert ausgelesenen Frames
				processedFrame.copyTo(currentFrame, binaryMask); // kopiert bestimmten Bereich des verzögerten Frames in das aktuelle Frame
			}}

		imshow("Delayed", currentFrame);// ÜBERGANGSWEISE zum Testen, im fertigen Programm muss nur in VideoEngine.cpp das videoFrame NACH der process-Funktion angezeigt werden
	}
	return currentFrame;
}

/*void DelayEffect::process(float* input, float*output, int numberOfSamples){
for(int i = 0; i < numberOfSamples; i++){
output[i] = processFrame(input[i]);
}
}*/


