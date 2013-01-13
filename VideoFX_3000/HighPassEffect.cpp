// NICHT FERTIG

#include "HighPassEffect.h"
#include "HighPass.h"
using namespace std;
using namespace cv;

// Namendefinition
const string sliderName = "Thresh";
const string windowName = "Hochpasseffekt";

HighPassEffect::HighPassEffect(void)
	: delta(1)
{
	setTool(new HighPass());// Auswahl des Tools f�r die Verarbeitung
}


HighPassEffect::~HighPassEffect(void)
{
	delete tool;
}

// Grundlegende Methode um das notwendige Tool der Basisklasse ToolInterface zu definieren, welches
// verwendet werden soll
void HighPassEffect::setTool(ToolInterface *tool){
	this->tool = tool;
}

void HighPassEffect::initialize(int frameWidth, int frameHeight){
	namedWindow(windowName);
	// Slider um den Schwellwert f�r den Hochpass einzustellen
	createTrackbar(sliderName, windowName, 0, 255);
	setTrackbarPos(sliderName, windowName, delta);
}

// Methode, in der die Verarbeitungen durchgef�hrt werden
Mat HighPassEffect::processFrame(Mat currentFrame){
	Mat processedFrame;

	// Einstellung des gesw�nschten Schwellwert
	delta = getTrackbarPos(sliderName, windowName);

	//Hochpass wird von der Klasse HighPass durchgef�hrt
	processedFrame = tool->process(currentFrame, delta);
	imshow(windowName, processedFrame);
	waitKey(30);

	// aktuelles Bild wird im Fenster "Video" wiedergegeben
	return processedFrame;
}