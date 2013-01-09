#include "HighPassEffect.h"
#include "HighPass.h"
using namespace std;
using namespace cv;


HighPassEffect::HighPassEffect(void)
	: delta(1)
{
	setTool(new HighPass());// Auswahl des Tools für die Verarbeitung
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
	// Slider um den Schwellwert für den Hochpass einzustellen
	createTrackbar("Differenz", "Hochpasseffekt", 0, 255);
	setTrackbarPos("Differenz", "Hochpasseffekt", delta);
}

// Methode, in der die Verarbeitungen durchgeführt werden
Mat HighPassEffect::processFrame(Mat currentFrame){
	Mat processedFrame;

	// Einstellung der gewünschten Zeit-Fenstergröße
	delta = getTrackbarPos("Differenz", "Hochpasseffekt");

	//Hochpass wird von der Klasse HighPass durchgeführt
	processedFrame = tool->process(currentFrame, delta);
	imshow("Hochpasseffekt", processedFrame);// ÜBERGANGSWEISE zum Testen, im fertigen Programm muss nur in VideoEngine.cpp das videoFrame NACH der process-Funktion angezeigt werden
	waitKey(30);

	// aktuelles Bild wird im Fenster "Video" wiedergegeben
	return currentFrame;
}