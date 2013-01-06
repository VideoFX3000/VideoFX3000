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
	, capIntensityAlpha(2.)
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
	createTrackbar("Alpha", "Cap-Intensity", 0, 100);
	setTrackbarPos("Alpha", "Cap-Intensity", capIntensityAlpha);

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
	capIntensityAlpha = getTrackbarPos("Alpha", "Cap-Intensity")/100.;

	if (frameNumber > 2){
		firstFrame.copyTo(copyOfFirstFrame);
 
//------VARIANTE 1 (ADDITION EINES SKALARS ANSTELLE DER BEWEGUNG)----------



	//----------BEGINN VARIANTE 1------------
/*
		add(copyOfFirstFrame, Scalar(capIntensityB, capIntensityG, capIntensityR), processedFrame);
		binaryMask = tool->process(currentFrame);
		processedFrame.copyTo(copyOfFirstFrame, binaryMask);
		imshow("Cap-Intensity", copyOfFirstFrame);
*/
	//---------ENDE VARIANTE 1------------


//-----VARIANTE 2 (MIT ALPHAKANAL)------------



	//---------BEGINN VARIANTE 2---------------

		// Kanäle, die notwendig sind um Frames nach und nach verblassen zu lassen
		//float alpha = 0.025; // Alpha-Kanal
		float beta; // Beta-Kanal

		copyOfFirstFrame.copyTo(processedFrame);
		beta = 1-capIntensityAlpha;
		binaryMask = tool->process(currentFrame); // erzeugt Binärmaske des original Bildes (currentFrame)
		multiply(currentFrame, capIntensityAlpha, currentFrame); // Blasses Vordergrundbild
		multiply(copyOfFirstFrame, beta, copyOfFirstFrame); // die Berechnung in currentFrame muss in copyOfFirstFrame gegensätzlich erfolgen damit der Frame korrekt aussieht
		add(currentFrame, copyOfFirstFrame, currentFrame); // beide Frames werden nun addiert
		currentFrame.copyTo(processedFrame, binaryMask); // kopiert nachdem die Schleife durchlaufen wurde einen bestimmten Bereich des originalen Frames in das aktuelle Frame
		imshow("Cap-Intensity", processedFrame);

	//-------ENEDE VARIANTE 2-------------
	}

	return currentFrame;
}
