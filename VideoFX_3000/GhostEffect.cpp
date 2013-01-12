#include "GhostEffect.h"
#include "Backgroundsubstraction.h"
#include <iostream>
#include <math.h>
using namespace std;
using namespace cv;

// Maximale Gr��e des Delayfensters vom Ghosteffekt
const int MAX_GHOST_WINDOW = 200;
GhostEffect::GhostEffect(void)
	// Initialisierung der Member-Variablen
	: frameNumber(0)
	, ghostWindow(0)
	, numberOfDelayedFrames(0)
	, frameDistance(1)
{
	setTool(new Backgroundsubstraction());// Auswahl des Tools f�r die Verarbeitung
}

GhostEffect::~GhostEffect(void)
{
}

// Grundlegende Methode um das notwendige Tool der Basisklasse ToolInterface zu definieren, welches verwendet werden soll
void GhostEffect::setTool(ToolInterface *tool){
	this->tool = tool;
}

// Methode um die Framebreite und -h�he sowie die Gr��e des Delays und des Buffers in der Klasse zuzuweisen
void GhostEffect::initialize(int frameWidth, int frameHeight){
	namedWindow("Ghost");
	this->ghostWindow = 20; // vom Benutzer steuerbar
	this->numberOfDelayedFrames = 6; // vom Benutzer steuerbar
	// Slider um die Anzahl der verz�gerten Frames einzustellen
	createTrackbar("Frames", "Ghost", 0, ghostWindow);
	setTrackbarPos("Frames", "Ghost", numberOfDelayedFrames);
	// Slider um die Fenstergr��e einzustellen
	createTrackbar("Window", "Ghost", 0, MAX_GHOST_WINDOW);
	setTrackbarPos("Window", "Ghost", ghostWindow);
	buffer.resizeBuffer(MAX_GHOST_WINDOW); // Gr��e des Buffers setzen
}

// Methode, in der die Verarbeitungen durchgef�hrt werden
Mat GhostEffect::processFrame(Mat currentFrame){
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
	ghostWindow = getTrackbarPos("Window", "Ghost");
	if(ghostWindow <= numberOfDelayedFrames && numberOfDelayedFrames > 0){
		ghostWindow = numberOfDelayedFrames;
		setTrackbarPos("Window", "Ghost", ghostWindow);
	}
	// erst wenn der Buffer komplett gef�llt ist k�nnen daraus verz�gerte Frames ausgelesen werden
	if(frameNumber >= ghostWindow)
	{
		// Einstellung der gew�nschten Frameanzahl
		numberOfDelayedFrames = getTrackbarPos("Frames", "Ghost"); // alternativ frameDistance einstellen
		if (numberOfDelayedFrames >= ghostWindow){
			numberOfDelayedFrames = ghostWindow;
			setTrackbarPos("Frames", "Ghost", numberOfDelayedFrames);
		}

		if(numberOfDelayedFrames > 0){
			// Berechnung des notwendigen Frameabstandes
			frameDistance = (float) ghostWindow / (float) numberOfDelayedFrames;

			// Kan�le, die notwendig sind um Frames nach und nach verblassen zu lassen
			float alpha = 1; // Alpha-Kanal
			float beta; // Beta-Kanal
			float alphaFactor = 0.8 / numberOfDelayedFrames;
			
			currentFrame.copyTo(originalFrame); // kopiert das unbearbeitete aktuelle Frame um es sp�ter dem bearbeiteten aktuellen Frame hinzuf�gen zu k�nnen (Alpha = 100 %)
			int count = 1;

			for(int i = 0; i < (numberOfDelayedFrames*frameDistance); i+=frameDistance){
				alpha = 1;
				alpha -= alphaFactor*count;
				count++;
				Mat processedFrame;
				buffer.readWithDelay(ghostWindow-i).copyTo(processedFrame); //liest Frame ab delayWindow Frames zuvor aus und kopiert in processedFrame				
				multiply(processedFrame, alpha, processedFrame); // die Frames werden blasser, je �lter sie sind (Person)
				beta = 1-alpha;
				multiply(currentFrame, beta, currentFrame); // die Berechnung in processedFrame muss in currentFrame gegens�tzlich erfolgen damit der Frame korrekt aussieht
				add(processedFrame, currentFrame, currentFrame); // beide Frames werden nun addiert	
				
			}
			binaryMask = tool->process(originalFrame, 0); // erzeugt Bin�rmaske des original Bildes (currentFrame)
			originalFrame.copyTo(currentFrame, binaryMask); // kopiert nachdem die Schleife durchlaufen wurde einen bestimmten Bereich des originalen Frames in das aktuelle Frame
		}
		
		imshow("Ghost", currentFrame);// �BERGANGSWEISE zum Testen, im fertigen Programm muss nur in VideoEngine.cpp das videoFrame NACH der process-Funktion angezeigt werden
	}
	return currentFrame;
}
