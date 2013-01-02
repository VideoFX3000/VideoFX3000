#include "DelayEffect.h"
#include "Backgroundsubstraction.h"
#include <iostream>
using namespace std;
using namespace cv;

// Maximale Größe des Delayfensters
const int MAX_DELAY_WINDOW = 200;
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
	this->delayWindow = 20; // vom Benutzer steuerbar
	this->numberOfDelayedFrames = 6; // vom Benutzer steuerbar
	// Slider um die Anzahl der verzögerten Frames einzustellen
	createTrackbar("Frames", "Delayed", 0, delayWindow);
	setTrackbarPos("Frames", "Delayed", numberOfDelayedFrames);
	// Slider um die Fenstergröße einzustellen
	createTrackbar("Window", "Delayed", 0, MAX_DELAY_WINDOW);
	setTrackbarPos("Window", "Delayed", delayWindow);
	buffer.resizeBuffer(MAX_DELAY_WINDOW); // Größe des Buffers setzen
}

// Methode, in der die Verarbeitungen durchgeführt werden
Mat DelayEffect::processFrame(Mat currentFrame){
	Mat binaryMask;
	Mat originalFrame;

	frameNumber++;
	buffer.writeBuffer(currentFrame); // schreibt aktuelles Frame in den Buffer

	// Zum Abfangen des ersten Frames (Hintergrund) notwendiger Aufruf von BackSub
	if (frameNumber <= 2){
		binaryMask = tool->process(currentFrame); // erzeugt Binärmaske des Hintergrundes (Dient zur Synchronisation von frameNumber)
	}

	// Einstellung der gewünschten Zeit-Fenstergröße
	delayWindow = getTrackbarPos("Window", "Delayed");
	// erst wenn der Buffer komplett gefüllt ist können daraus verzögerte Frames ausgelesen werden
	if(frameNumber >= delayWindow)
	{
		// Einstellung der gewünschten Frameanzahl
		numberOfDelayedFrames = getTrackbarPos("Frames", "Delayed"); // alternativ frameDistance einstellen

		if(numberOfDelayedFrames != 0){
			// Berechnung des notwendigen Frameabstandes
			frameDistance = (float) delayWindow / (float) numberOfDelayedFrames;
			tolower(frameDistance);// Abrunden um in der for-Schleife mit ganzzahligen Werten rechnen zu können

			// Hinzufügen der gewünschten Anzahl an verzögerten Frames (FUNKTIONIERT JETZT SCHEINBAR KORREKT)
/*
	//----------BEGINN VARIANTE 1-------------

			for(int i = 0; i < delayWindow; i+=frameDistance){
				Mat processedFrame;
				buffer.readWithDelay(delayWindow-i).copyTo(processedFrame); //liest Frame ab delayWindow Frames zuvor aus und kopiert in processedFrame
				binaryMask = tool->process(processedFrame); // erzeugt Binärmaske des verzögert ausgelesenen Frames
				processedFrame.copyTo(currentFrame, binaryMask); // kopiert bestimmten Bereich des verzögerten Frames in das aktuelle Frame
			}
		}

	//----------ENDE VARIANTE 1---------------
*/



	
	//---------------neue Variante mit verblassenden Frames (könnte man zum Beispiel nach Drücken einer bestimmten Taste aktivieren)--------------
		




	//------BEGINN VARIANTE 2-----------

			// Kanäle, die notwendig sind um Frames nach und nach verblassen zu lassen
			float alpha = 1; // Alpha-Kanal
			float beta; // Beta-Kanal
			float alphaFactor = alpha / (2 * frameDistance); //könnte auch über einen Slider eingestellt werden, müsste dann aber begrenzt werden
			
			currentFrame.copyTo(originalFrame); // kopiert das unbearbeitete aktuelle Frame um es später dem bearbeiteten aktuellen Frame hinzufügen zu können (Alpha = 100 %)

			for(int i = 0; i < delayWindow; i+=frameDistance, alpha-=alphaFactor){
				Mat processedFrame;
				buffer.readWithDelay(delayWindow-i).copyTo(processedFrame); //liest Frame ab delayWindow Frames zuvor aus und kopiert in processedFrame				
				multiply(processedFrame, alpha, processedFrame); // die Frames werden blasser, je älter sie sind
				beta = 1-alpha;
				multiply(currentFrame, beta, currentFrame); // die Berechnung in processedFrame muss in currentFrame gegensätzlich erfolgen damit der Frame korrekt aussieht
				add(processedFrame, currentFrame, currentFrame); // beide Frames werden nun addiert
			}
		}
		binaryMask = tool->process(originalFrame); // erzeugt Binärmaske des original Bildes (currentFrame)
		originalFrame.copyTo(currentFrame, binaryMask); // kopiert nachdem die Schleife durchlaufen wurde einen bestimmten Bereich des originalen Frames in das aktuelle Frame
	
	// --------------ENDE VARIANTE 2------------
		
		imshow("Delayed", currentFrame);// ÜBERGANGSWEISE zum Testen, im fertigen Programm muss nur in VideoEngine.cpp das videoFrame NACH der process-Funktion angezeigt werden
	}
	return currentFrame;
}

/*void DelayEffect::process(float* input, float*output, int numberOfSamples){
for(int i = 0; i < numberOfSamples; i++){
output[i] = processFrame(input[i]);
}
}*/


