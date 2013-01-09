#include "HighPassEffect.h"
#include "HighPass.h"
using namespace std;
using namespace cv;


HighPassEffect::HighPassEffect(void)
	: delta(1)
{
	setTool(new HighPass());// Auswahl des Tools f�r die Verarbeitung
}


HighPassEffect::~HighPassEffect(void)
{
}

// Grundlegende Methode um das notwendige Tool der Basisklasse ToolInterface zu definieren, welches
// verwendet werden soll
void HighPassEffect::setTool(ToolInterface *tool){
	this->tool = tool;
}

void HighPassEffect::initialize(int frameWidth, int frameHeight){
	namedWindow("Hochpasseffekt");
	// Slider um den Schwellwert f�r den Hochpass einzustellen
	createTrackbar("Differenz", "Hochpasseffekt", 0, 255);
	setTrackbarPos("Differenz", "Hochpasseffekt", delta);
}

// Methode, in der die Verarbeitungen durchgef�hrt werden
Mat HighPassEffect::processFrame(Mat currentFrame){
	Mat processedFrame;

	// Einstellung der gew�nschten Zeit-Fenstergr��e
	delta = getTrackbarPos("Differenz", "Hochpasseffekt");

	//Hochpass wird von der Klasse HighPass durchgef�hrt
	processedFrame = tool->process(currentFrame, delta);
	imshow("Hochpasseffekt", processedFrame);// �BERGANGSWEISE zum Testen, im fertigen Programm muss nur in VideoEngine.cpp das videoFrame NACH der process-Funktion angezeigt werden
	waitKey(30);

	// aktuelles Bild wird im Fenster "Video" wiedergegeben
	return currentFrame;
}