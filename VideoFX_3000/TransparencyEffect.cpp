#include "TransparencyEffect.h"
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
}

TransparencyEffect::~TransparencyEffect(void)
{
}

// Grundlegende Methode um das notwendige Tool der Basisklasse ToolInterface zu definieren, welches
// verwendet werden soll
void TransparencyEffect::setTool(ToolInterface *tool){
}

// Methode um die Framebreite und -höhe der Klasse zuzuweisen und die Trackbar einzufügen
void TransparencyEffect::initialize(int frameWidth, int frameHeight){
	namedWindow(windowTransparencyEffect);
	createTrackbar(trackbarAlpha, windowTransparencyEffect, 0, 100);
	setTrackbarPos(trackbarAlpha, windowTransparencyEffect, alpha);
}

// Methode, in der die Verarbeitungen durchgeführt werden
Mat TransparencyEffect::processFrame(Mat currentFrame){
	Mat copyOfFirstFrame;
	Mat processedFrame;

	frameNumber++;
	if(frameNumber == 2){
		currentFrame.copyTo(firstFrame); // Kopiert ersten Frame für Backgroundsubstraction
	}

	alpha = getTrackbarPos(trackbarAlpha, windowTransparencyEffect)/100.;

	if (frameNumber > 2){
		firstFrame.copyTo(copyOfFirstFrame);

		float beta; // Beta-Kanal

		beta = 1-alpha;

		multiply(currentFrame, alpha, currentFrame); // Blasses Vordergrundbild
		multiply(copyOfFirstFrame, beta, copyOfFirstFrame); // die Berechnung in currentFrame muss in copyOfFirstFrame gegensätzlich erfolgen damit der Frame korrekt aussieht
		add(currentFrame, copyOfFirstFrame, processedFrame); // beide Frames werden nun addiert
		imshow(windowTransparencyEffect, processedFrame);
	}
	return processedFrame;
}
