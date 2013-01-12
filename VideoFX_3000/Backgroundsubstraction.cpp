// Fertig

#include "Backgroundsubstraction.h"
#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;
using namespace std;

// Namendefinition
const string windowNameVideo = "Video";
const string sliderNameThresh = "Thresh";

Backgroundsubstraction::Backgroundsubstraction(void)
	// Initialisierung der Member-Variablen
	: frameNumber(0)
{
}

Backgroundsubstraction::~Backgroundsubstraction(void)
{
}

// diese Funktion erkennt die größte sich bewegende Fläche
// die Ausgabe erfolgt im Mat-Objekt "processedFrame"
// dabei sind sich bewegende Pixel weiß gefärbt und alle restlichen Pixel schwarz
Mat Backgroundsubstraction::process(Mat& input, int delta)
{
	Mat processedFrame;
	Mat grayFrame (input.rows, input.cols, CV_8UC1);
	Mat originalGray;

	//wandelt eingegebenes Matobjekt in Graustufenbild um
	cvtColor(input, grayFrame, CV_BGR2GRAY);
		
	grayFrame.copyTo(originalGray);
	
	//kopiert nicht das erste Frame, falls Kamera Zeit zum Starten benötigt
	frameNumber++;
	if (frameNumber == 2)
	{
		grayFrame.copyTo(firstFrame);
	}	

	// solange die Framenummer kleiner als 6 ist, wird das Graustufenbild nach processedFrame kopiert
	// damit processedFrame nicht leer ist und eine Fehlermeldung erscheint
	if (frameNumber < 6)
	{
		grayFrame.copyTo(processedFrame);
	}else{
		//Berechnet Unterschied von grayFrame und firstFrame; hier: Unterschied = Bewegung
		absdiff(grayFrame, firstFrame, grayFrame);

		int thresh = getTrackbarPos(sliderNameThresh, windowNameVideo); //Namen sind in VideoEngine.cpp definiert
		threshold(grayFrame, processedFrame, thresh, 255, THRESH_BINARY);
	}

	medianBlur(processedFrame, processedFrame, 3);	//verhindert Pixellöcher
	// Opening (entfernt Rauschen im Hintergrund / schließt Löcher im Hintergrund) --> erode, dilate
	// Closing (schließt Löcher im Vordergrund) --> dilate, erode
	dilate(processedFrame, processedFrame, Mat(3, 3, CV_8UC1));
	erode(processedFrame, processedFrame, Mat(3, 3, CV_8UC1));

	//findet Flächen im Binärbild und schreibt Größe der Fläche in Array contours[]
	Mat copyOfFrame;
	vector<vector<Point> > contours;
	processedFrame.copyTo(copyOfFrame);
	findContours(copyOfFrame, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	
	//findet die größte Fläche im Array contours[]
	int area;
	int maxArea = 0;
	int maxAreaIndex = 0;
	for(int indexOfRegion = 0; indexOfRegion < contours.size(); indexOfRegion++)
	{
		vector<Point> contour = contours[indexOfRegion];
		area = contourArea(contour);

		if(area > maxArea)
		{
			maxArea = area;
			maxAreaIndex = indexOfRegion;
		}
	}

	// färbt alle kleineren Flächen als die größte schwarz; die größte wird innerhalb der Kontur weiß gefärbt
	for(int indexOfRegion = 0; indexOfRegion < contours.size(); indexOfRegion++)
	{
		if(indexOfRegion == maxAreaIndex)
		{
			drawContours(processedFrame, contours, indexOfRegion, 255, CV_FILLED);
		}
		else
		{
			drawContours(processedFrame, contours, indexOfRegion, 0, CV_FILLED);
		}
	}
	return processedFrame;
}