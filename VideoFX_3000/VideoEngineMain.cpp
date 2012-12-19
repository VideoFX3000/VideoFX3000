#include "VideoEngine.h"
using namespace cv;
using namespace std;
//Bearbeitung
/* Ivonnes Änderung */

int main()
{
	const string videoPath = "C:/Users/Public/Videos/Micro-dance.AVI";
	//const string videoPath = "c:/Entwicklung/micro-dance.mpeg";
	/*
	VideoEngine videoDelay;
	if(videoDelay.openVideo(videoPath, 1)){
		videoDelay.runVideo();
	}*/

	VideoCapture videoCap;

	videoCap.open(0);
	if(videoCap.isOpened())
		cout << "open";

	getchar();
	getchar();



	
	/*
	Backgroundsubstraction app;

	if (app.openVideo(videoPath))
	{
		app.runVideo();
	}*/
}
