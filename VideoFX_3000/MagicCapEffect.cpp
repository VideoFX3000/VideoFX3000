#include "MagicCapEffect.h"
#include "Backgroundsubstraction.h"
#include <iostream>
using namespace std;
using namespace cv;

//---------ACHTUNG: teilweise aus DelayEffect kopiert und einige Kommentare noch nicht angepasst
const string window_MagicCapEffect = "Tarnkappen-Effekt";
const string trackbar_capIntensityR = "R";
const string trackbar_capIntensityG = "G";
const string trackbar_capIntensityB = "B";
//const string trackbar_capIntensityRGB = "R+G+B";

MagicCapEffect::MagicCapEffect(void)
	// Initialisierung der Member-Variablen
	: frameWidth(0)
	, frameHeight(0)
	, frameNumber(0)
	, capIntensityR(4)
	, capIntensityG(4)
	, capIntensityB(4)
//	, capIntensityRGB(4)
{
	setTool(new Backgroundsubstraction());// Auswahl des Tools für die Verarbeitung
}


MagicCapEffect::~MagicCapEffect(void)
{
}

// Grundlegende Methode um das notwendige Tool der Basisklasse ToolInterface zu definieren, welches
// verwendet werden soll
void MagicCapEffect::setTool(ToolInterface *tool){
	this->tool = tool;
}

// Methode um die Framebreite und -höhe der Klasse zuzuweisen und die Trackbars einzufügen
void MagicCapEffect::initialize(int frameWidth, int frameHeight){
	namedWindow(window_MagicCapEffect);
	this->frameWidth = frameWidth;
	this->frameHeight = frameHeight;

	// Trackbars zum Testen
	createTrackbar(trackbar_capIntensityR, window_MagicCapEffect, 0, 255);
	setTrackbarPos(trackbar_capIntensityR, window_MagicCapEffect, capIntensityR);
	createTrackbar(trackbar_capIntensityG, window_MagicCapEffect, 0, 255);
	setTrackbarPos(trackbar_capIntensityG, window_MagicCapEffect, capIntensityG);
	createTrackbar(trackbar_capIntensityB, window_MagicCapEffect, 0, 255);
	setTrackbarPos(trackbar_capIntensityB, window_MagicCapEffect, capIntensityB);
/*	createTrackbar(trackbar_capIntensityRGB, window_MagicCapEffect, 0, 255);
	setTrackbarPos(trackbar_capIntensityRGB, window_MagicCapEffect, capIntensityRGB);
*/
}
// Methode, in der die Verarbeitungen durchgeführt werden
Mat MagicCapEffect::processFrame(Mat currentFrame){
	Mat binaryMask;
	Mat copyOfFirstFrame;
	Mat processedFrame;

	frameNumber++;

	if(frameNumber == 2){
		currentFrame.copyTo(firstFrame);
	}

	// Trackbars zum Testen
	capIntensityR = getTrackbarPos(trackbar_capIntensityR, window_MagicCapEffect);
	capIntensityG = getTrackbarPos(trackbar_capIntensityG, window_MagicCapEffect);
	capIntensityB = getTrackbarPos(trackbar_capIntensityB, window_MagicCapEffect);
	//capIntensityRGB = getTrackbarPos(trackbar_capIntensityRGB, window_MagicCapEffect);


	if (frameNumber > 2){
		firstFrame.copyTo(copyOfFirstFrame);

		add(copyOfFirstFrame, Scalar(capIntensityB, capIntensityG, capIntensityR), processedFrame);
		binaryMask = tool->process(currentFrame); // erzeugt Binärmaske des original Bildes (currentFrame)
		processedFrame.copyTo(copyOfFirstFrame, binaryMask);// kopiert einen bestimmten Bereich des verarbeiteten Frames in das erste Frame
		imshow(window_MagicCapEffect, copyOfFirstFrame);
	}

	return currentFrame;
}
