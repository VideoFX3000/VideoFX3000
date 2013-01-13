#include "MagicCapEffect.h"
#include "Backgroundsubstraction.h"
#include <iostream>
using namespace std;
using namespace cv;

// Namendefinition
const string windowMagicCapEffect = "Tarnkappeneffekt";
const string trackbarCapIntensityR = "R";
const string trackbarCapIntensityG = "G";
const string trackbarCapIntensityB = "B";

MagicCapEffect::MagicCapEffect(void)
	// Initialisierung der Member-Variablen
	: frameNumber(0)
	, capIntensityR(4)
	, capIntensityG(4)
	, capIntensityB(4)
{
	setTool(new Backgroundsubstraction());// Auswahl des Tools f¸r die Verarbeitung
}

MagicCapEffect::~MagicCapEffect(void)
{
	delete tool;
}

// Grundlegende Methode um das notwendige Tool der Basisklasse ToolInterface zu definieren, welches
// verwendet werden soll
void MagicCapEffect::setTool(ToolInterface *tool){
	this->tool = tool;
}

// Methode um die Trackbars einzuf¸gen
void MagicCapEffect::initialize(int frameWidth, int frameHeight){
	namedWindow(windowMagicCapEffect);
	createTrackbar(trackbarCapIntensityR, windowMagicCapEffect, 0, 255);
	setTrackbarPos(trackbarCapIntensityR, windowMagicCapEffect, capIntensityR);
	createTrackbar(trackbarCapIntensityG, windowMagicCapEffect, 0, 255);
	setTrackbarPos(trackbarCapIntensityG, windowMagicCapEffect, capIntensityG);
	createTrackbar(trackbarCapIntensityB, windowMagicCapEffect, 0, 255);
	setTrackbarPos(trackbarCapIntensityB, windowMagicCapEffect, capIntensityB);
}

// Methode, in der die Verarbeitungen durchgef¸hrt werden
Mat MagicCapEffect::processFrame(Mat currentFrame){
	Mat binaryMask;
	Mat copyOfFirstFrame;
	Mat processedFrame;

	frameNumber++;
	if(frameNumber == 2){
		currentFrame.copyTo(firstFrame);	// Kopiert ersten Frame f¸r Backgroundsubstraction
	}

	// Wert der Trackbars wird in Variablen geschrieben
	capIntensityR = getTrackbarPos(trackbarCapIntensityR, windowMagicCapEffect);
	capIntensityG = getTrackbarPos(trackbarCapIntensityG, windowMagicCapEffect);
	capIntensityB = getTrackbarPos(trackbarCapIntensityB, windowMagicCapEffect);

	if (frameNumber > 2){
		firstFrame.copyTo(copyOfFirstFrame); 
		add(copyOfFirstFrame, Scalar(capIntensityB, capIntensityG, capIntensityR), processedFrame); // rechnet Werte der Trackbars zum Frame und speichert den Frame in processedFrame
		binaryMask = tool->process(currentFrame, 0); // erzeugt Bin‰rmaske des original Bildes (currentFrame)
		processedFrame.copyTo(copyOfFirstFrame, binaryMask);// kopiert alles des verarbeiteten Frames, auﬂer dem maskierten Bereich, in das erste Frame
		imshow(windowMagicCapEffect, copyOfFirstFrame);
	}
	return copyOfFirstFrame;
}
