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
	setTool(new HighPass());// Auswahl des Tools für die Verarbeitung
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
	// Slider um den Schwellwert für den Hochpass einzustellen
	createTrackbar(sliderName, windowName, 0, 255);
	setTrackbarPos(sliderName, windowName, delta);
}

// Methode, in der die Verarbeitungen durchgeführt werden
Mat HighPassEffect::processFrame(Mat currentFrame){
	Mat processedFrame;

	// Einstellung des geswünschten Schwellwert
	delta = getTrackbarPos(sliderName, windowName);

	//Hochpass wird von der Klasse HighPass durchgeführt
	processedFrame = tool->process(currentFrame, delta);
	imshow(windowName, processedFrame);
	waitKey(30);

	// aktuelles Bild wird im Fenster "Video" wiedergegeben
	return processedFrame;
}