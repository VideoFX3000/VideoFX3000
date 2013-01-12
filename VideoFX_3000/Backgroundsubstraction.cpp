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

// diese Funktion erkennt die gr��te sich bewegende Fl�che
// die Ausgabe erfolgt im Mat-Objekt "processedFrame"
// dabei sind sich bewegende Pixel wei� gef�rbt und alle restlichen Pixel schwarz
Mat Backgroundsubstraction::process(Mat& input, int delta)
{
	Mat processedFrame;
	Mat grayFrame (input.rows, input.cols, CV_8UC1);
	Mat originalGray;

	//wandelt eingegebenes Matobjekt in Graustufenbild um
	cvtColor(input, grayFrame, CV_BGR2GRAY);
		
	grayFrame.copyTo(originalGray);
	
	//kopiert nicht das erste Frame, falls Kamera Zeit zum Starten ben�tigt
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

	medianBlur(processedFrame, processedFrame, 3);	//verhindert Pixell�cher
	// Opening (entfernt Rauschen im Hintergrund / schlie�t L�cher im Hintergrund) --> erode, dilate
	// Closing (schlie�t L�cher im Vordergrund) --> dilate, erode
	dilate(processedFrame, processedFrame, Mat(3, 3, CV_8UC1));
	erode(processedFrame, processedFrame, Mat(3, 3, CV_8UC1));

	//findet Fl�chen im Bin�rbild und schreibt Gr��e der Fl�che in Array contours[]
	Mat copyOfFrame;
	vector<vector<Point> > contours;
	processedFrame.copyTo(copyOfFrame);
	findContours(copyOfFrame, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	
	//findet die gr��te Fl�che im Array contours[]
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

	// f�rbt alle kleineren Fl�chen als die gr��te schwarz; die gr��te wird innerhalb der Kontur wei� gef�rbt
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