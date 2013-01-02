#include "DelayEffect.h"
#include "Backgroundsubstraction.h"
#include <iostream>
using namespace std;
using namespace cv;

// Maximale Gr��e des Delayfensters
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
	namedWindow("Delayed");
	this->frameWidth = frameWidth;
	this->frameHeight = frameHeight;
	this->delayWindow = 20; // vom Benutzer steuerbar
	this->numberOfDelayedFrames = 6; // vom Benutzer steuerbar
	// Slider um die Anzahl der verz�gerten Frames einzustellen
	createTrackbar("Frames", "Delayed", 0, delayWindow);
	setTrackbarPos("Frames", "Delayed", numberOfDelayedFrames);
	// Slider um die Fenstergr��e einzustellen
	createTrackbar("Window", "Delayed", 0, MAX_DELAY_WINDOW);
	setTrackbarPos("Window", "Delayed", delayWindow);
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
		binaryMask = tool->process(currentFrame); // erzeugt Bin�rmaske des Hintergrundes (Dient zur Synchronisation von frameNumber)
	}

	// Einstellung der gew�nschten Zeit-Fenstergr��e
	delayWindow = getTrackbarPos("Window", "Delayed");
	// erst wenn der Buffer komplett gef�llt ist k�nnen daraus verz�gerte Frames ausgelesen werden
	if(frameNumber >= delayWindow)
	{
		// Einstellung der gew�nschten Frameanzahl
		numberOfDelayedFrames = getTrackbarPos("Frames", "Delayed"); // alternativ frameDistance einstellen

		if(numberOfDelayedFrames != 0){
			// Berechnung des notwendigen Frameabstandes
			frameDistance = (float) delayWindow / (float) numberOfDelayedFrames;
			tolower(frameDistance);// Abrunden um in der for-Schleife mit ganzzahligen Werten rechnen zu k�nnen

			// Hinzuf�gen der gew�nschten Anzahl an verz�gerten Frames (FUNKTIONIERT JETZT SCHEINBAR KORREKT)
/*
	//----------BEGINN VARIANTE 1-------------

			for(int i = 0; i < delayWindow; i+=frameDistance){
				Mat processedFrame;
				buffer.readWithDelay(delayWindow-i).copyTo(processedFrame); //liest Frame ab delayWindow Frames zuvor aus und kopiert in processedFrame
				binaryMask = tool->process(processedFrame); // erzeugt Bin�rmaske des verz�gert ausgelesenen Frames
				processedFrame.copyTo(currentFrame, binaryMask); // kopiert bestimmten Bereich des verz�gerten Frames in das aktuelle Frame
			}
		}

	//----------ENDE VARIANTE 1---------------
*/



	
	//---------------neue Variante mit verblassenden Frames (k�nnte man zum Beispiel nach Dr�cken einer bestimmten Taste aktivieren)--------------
		




	//------BEGINN VARIANTE 2-----------

			// Kan�le, die notwendig sind um Frames nach und nach verblassen zu lassen
			float alpha = 1; // Alpha-Kanal
			float beta; // Beta-Kanal
			float alphaFactor = alpha / (2 * frameDistance); //k�nnte auch �ber einen Slider eingestellt werden, m�sste dann aber begrenzt werden
			
			currentFrame.copyTo(originalFrame); // kopiert das unbearbeitete aktuelle Frame um es sp�ter dem bearbeiteten aktuellen Frame hinzuf�gen zu k�nnen (Alpha = 100 %)

			for(int i = 0; i < delayWindow; i+=frameDistance, alpha-=alphaFactor){
				Mat processedFrame;
				buffer.readWithDelay(delayWindow-i).copyTo(processedFrame); //liest Frame ab delayWindow Frames zuvor aus und kopiert in processedFrame				
				multiply(processedFrame, alpha, processedFrame); // die Frames werden blasser, je �lter sie sind
				beta = 1-alpha;
				multiply(currentFrame, beta, currentFrame); // die Berechnung in processedFrame muss in currentFrame gegens�tzlich erfolgen damit der Frame korrekt aussieht
				add(processedFrame, currentFrame, currentFrame); // beide Frames werden nun addiert
			}
		}
		binaryMask = tool->process(originalFrame); // erzeugt Bin�rmaske des original Bildes (currentFrame)
		originalFrame.copyTo(currentFrame, binaryMask); // kopiert nachdem die Schleife durchlaufen wurde einen bestimmten Bereich des originalen Frames in das aktuelle Frame
	
	// --------------ENDE VARIANTE 2------------
		
		imshow("Delayed", currentFrame);// �BERGANGSWEISE zum Testen, im fertigen Programm muss nur in VideoEngine.cpp das videoFrame NACH der process-Funktion angezeigt werden
	}
	return currentFrame;
}

/*void DelayEffect::process(float* input, float*output, int numberOfSamples){
for(int i = 0; i < numberOfSamples; i++){
output[i] = processFrame(input[i]);
}
}*/


