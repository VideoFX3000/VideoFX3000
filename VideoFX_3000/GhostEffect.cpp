#include "GhostEffect.h"
#include "Backgroundsubstraction.h"
#include <iostream>
#include <math.h>
using namespace std;
using namespace cv;

// Maximale Größe des Delayfensters vom Ghosteffekt
const int MAX_GHOST_WINDOW = 200;
const string windowGhost = "Ghosteffekt";
const string sliderFrames = "Frames";
const string sliderWindow = "Window";

GhostEffect::GhostEffect(void)
	// Initialisierung der Member-Variablen
	: frameNumber(0)
	, ghostWindow(0)
	, numberOfDelayedFrames(0)
	, frameDistance(1)
{
	setTool(new Backgroundsubstraction());// Auswahl des Tools für die Verarbeitung
}

GhostEffect::~GhostEffect(void)
{
	delete tool;
}

// Grundlegende Methode um das notwendige Tool der Basisklasse ToolInterface zu definieren, welches verwendet werden soll
void GhostEffect::setTool(ToolInterface *tool){
	this->tool = tool;
}

// Methode um die Framebreite und -höhe sowie die Größe des Delays und des Buffers in der Klasse zuzuweisen
void GhostEffect::initialize(int frameWidth, int frameHeight){
	namedWindow(windowGhost);
	this->ghostWindow = 20; // vom Benutzer steuerbar
	this->numberOfDelayedFrames = 6; // vom Benutzer steuerbar
	// Slider um die Anzahl der verzögerten Frames einzustellen
	createTrackbar(sliderFrames, windowGhost, 0, ghostWindow);
	setTrackbarPos(sliderFrames, windowGhost, numberOfDelayedFrames);
	// Slider um die Fenstergröße einzustellen
	createTrackbar(sliderWindow, windowGhost, 0, MAX_GHOST_WINDOW);
	setTrackbarPos(sliderWindow, windowGhost, ghostWindow);
	buffer.resizeBuffer(MAX_GHOST_WINDOW); // Größe des Buffers setzen
}

// Methode, in der die Verarbeitungen durchgeführt werden
Mat GhostEffect::processFrame(Mat currentFrame){
	Mat binaryMask;
	Mat originalFrame;

	frameNumber++;
	buffer.writeBuffer(currentFrame); // schreibt aktuelles Frame in den Buffer

	// Zum Abfangen des ersten Frames (Hintergrund) notwendiger Aufruf von BackSub
	if (frameNumber <= 2){
		binaryMask = tool->process(currentFrame, 0); // erzeugt Binärmaske des Hintergrundes (Dient zur Synchronisation von frameNumber)
	}

	//----------Konfiguration der Regler, damit nur sinnvolle Werte eingestellt werden können---------------
	// Einstellung der gewünschten Zeit-Fenstergröße
	ghostWindow = getTrackbarPos(sliderWindow, windowGhost);
	if(ghostWindow <= numberOfDelayedFrames && numberOfDelayedFrames > 0){
		ghostWindow = numberOfDelayedFrames;
		setTrackbarPos(sliderWindow, windowGhost, ghostWindow);
	}
	// erst wenn der Buffer komplett gefüllt ist können daraus verzögerte Frames ausgelesen werden
	if(frameNumber >= ghostWindow)
	{
		// Einstellung der gewünschten Frameanzahl
		numberOfDelayedFrames = getTrackbarPos(sliderFrames, windowGhost); // alternativ frameDistance einstellen
		if (numberOfDelayedFrames >= ghostWindow){
			numberOfDelayedFrames = ghostWindow;
			setTrackbarPos(sliderFrames, windowGhost, numberOfDelayedFrames);
		}

		if(numberOfDelayedFrames > 0){
			// Berechnung des notwendigen Frameabstandes
			frameDistance = (float) ghostWindow / (float) numberOfDelayedFrames;

			// Kanäle, die notwendig sind um Frames nach und nach verblassen zu lassen
			float alpha = 1; // Alpha-Kanal
			float beta; // Beta-Kanal
			float alphaFactor = 0.8 / numberOfDelayedFrames;
			
			currentFrame.copyTo(originalFrame); // kopiert das unbearbeitete aktuelle Frame um es später dem bearbeiteten aktuellen Frame hinzufügen zu können (Alpha = 100 %)
			int count = 1;

			for(int i = 0; i < (numberOfDelayedFrames*frameDistance); i+=frameDistance){
				alpha = 1;
				alpha -= alphaFactor*count;
				count++;
				Mat processedFrame;
				buffer.readWithDelay(ghostWindow-i).copyTo(processedFrame); //liest Frame ab delayWindow Frames zuvor aus und kopiert in processedFrame				
				multiply(processedFrame, alpha, processedFrame); // die Frames werden blasser, je älter sie sind (Person)
				beta = 1-alpha;
				multiply(currentFrame, beta, currentFrame); // die Berechnung in processedFrame muss in currentFrame gegensätzlich erfolgen damit der Frame korrekt aussieht
				add(processedFrame, currentFrame, currentFrame); // beide Frames werden nun addiert	
				
			}
			binaryMask = tool->process(originalFrame, 0); // erzeugt Binärmaske des original Bildes (currentFrame)
			originalFrame.copyTo(currentFrame, binaryMask); // kopiert nachdem die Schleife durchlaufen wurde einen bestimmten Bereich des originalen Frames in das aktuelle Frame
		}
		//imshow(windowGhost, currentFrame);
	}
	// verarbeitetes Bild wird in der Klasse VideoEngine wiedergegeben
	return currentFrame;
}