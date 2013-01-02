#include "MagicCapEffect.h"
#include "Backgroundsubstraction.h"
#include <iostream>
using namespace std;
using namespace cv;

//---------ACHTUNG: teilweise aus DelayEffect kopiert und einige Kommentare noch nicht angepasst


MagicCapEffect::MagicCapEffect(void)
	// Initialisierung der Member-Variablen
	: frameWidth(0)
	, frameHeight(0)
	, frameNumber(0)
	, capIntensityR(4)
	, capIntensityG(4)
	, capIntensityB(4)
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

// Methode um die Framebreite und -höhe sowie die Größe des Delays und des Buffers in der Klasse
// zuzuweisen
void MagicCapEffect::initialize(int frameWidth, int frameHeight){
	namedWindow("Cap-Intensity");
	this->frameWidth = frameWidth;
	this->frameHeight = frameHeight;

	// Trackbars zum Testen
	createTrackbar("R", "Cap-Intensity", 0, 255);
	setTrackbarPos("R", "Cap-Intensity", capIntensityR);
	createTrackbar("G", "Cap-Intensity", 0, 255);
	setTrackbarPos("G", "Cap-Intensity", capIntensityG);
	createTrackbar("B", "Cap-Intensity", 0, 255);
	setTrackbarPos("B", "Cap-Intensity", capIntensityB);
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
	capIntensityR = getTrackbarPos("R", "Cap-Intensity");
	capIntensityG = getTrackbarPos("G", "Cap-Intensity");
	capIntensityB = getTrackbarPos("B", "Cap-Intensity");

	if (frameNumber > 2){
	firstFrame.copyTo(copyOfFirstFrame);
	add(copyOfFirstFrame, Scalar(capIntensityB, capIntensityG, capIntensityR), processedFrame);
	binaryMask = tool->process(currentFrame);
	processedFrame.copyTo(copyOfFirstFrame, binaryMask);
	imshow("Cap-Intensity", copyOfFirstFrame);
	}

	return currentFrame;
}
