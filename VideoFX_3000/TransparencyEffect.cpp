//Fertig

#include "TransparencyEffect.h"
#include "Backgroundsubstraction.h"
#include <iostream>
using namespace std;
using namespace cv;

// Namendefinition
const string windowTransparencyEffect = "Transparenzeffekt";
const string trackbarAlpha = "Alpha";

TransparencyEffect::TransparencyEffect(void)
	// Initialisierung der Member-Variablen
	: frameNumber(0)
	, alpha(2.)
{
	setTool(new Backgroundsubstraction());// Auswahl des Tools f�r die Verarbeitung
}

TransparencyEffect::~TransparencyEffect(void)
{
}

// Grundlegende Methode um das notwendige Tool der Basisklasse ToolInterface zu definieren, welches
// verwendet werden soll
void TransparencyEffect::setTool(ToolInterface *tool){
	this->tool = tool;
}

// Methode um die Framebreite und -h�he der Klasse zuzuweisen und die Trackbar einzuf�gen
void TransparencyEffect::initialize(int frameWidth, int frameHeight){
	namedWindow(windowTransparencyEffect);
	createTrackbar(trackbarAlpha, windowTransparencyEffect, 0, 100);
	setTrackbarPos(trackbarAlpha, windowTransparencyEffect, alpha);
}

// Methode, in der die Verarbeitungen durchgef�hrt werden
Mat TransparencyEffect::processFrame(Mat currentFrame){
	Mat binaryMask;
	Mat copyOfFirstFrame;
	Mat processedFrame;

	frameNumber++;
	if(frameNumber == 2){
		currentFrame.copyTo(firstFrame); // Kopiert ersten Frame f�r Backgroundsubstraction
	}

	alpha = getTrackbarPos(trackbarAlpha, windowTransparencyEffect)/100.;

	if (frameNumber > 2){
		firstFrame.copyTo(copyOfFirstFrame);

		float beta; // Beta-Kanal

		copyOfFirstFrame.copyTo(processedFrame);
		beta = 1-alpha;

		binaryMask = tool->process(currentFrame, 0); // erzeugt Bin�rmaske des original Bildes (currentFrame)
		multiply(currentFrame, alpha, currentFrame); // Blasses Vordergrundbild
		multiply(copyOfFirstFrame, beta, copyOfFirstFrame); // die Berechnung in currentFrame muss in copyOfFirstFrame gegens�tzlich erfolgen damit der Frame korrekt aussieht
		add(currentFrame, copyOfFirstFrame, currentFrame); // beide Frames werden nun addiert
		currentFrame.copyTo(processedFrame, binaryMask); // kopiert nachdem die Schleife durchlaufen wurde einen bestimmten Bereich des originalen Frames in das aktuelle Frame
		imshow(windowTransparencyEffect, processedFrame);
	}
	return currentFrame;
}
