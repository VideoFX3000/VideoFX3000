//#include "VideoEngine.h"
#include "Backgroundsubstraction.h"
using namespace cv;
using namespace std;

int main()
{
	const string videoPath = "C:/Users/Public/Videos/Micro-dance_2_.AVI";
	//const string videoPath = "C:\\Users\\Public\\Videos\\Micro-dance.AVI";
	/*
	VideoEngine videoDelay;
	if(videoDelay.openVideo(videoPath, 1)){
		videoDelay.runVideo();
	}*/
	
	Backgroundsubstraction app;

	if (app.openVideo(videoPath,1))
	{
		app.runVideo();
	}
}
