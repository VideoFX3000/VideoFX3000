#include "BackgroundSubstraction.h"
using namespace cv;
using namespace std;

/* Hallo Ham ham ham */
/* Ivonnes �nderung*/

int main()
{
	const string videoPath = "C:/Users/Public/Videos/Micro-dance.AVI";
	//const string videoPath = "c:/Entwicklung/micro-dance.mpeg";
	Backgroundsubstraction app;

	if (app.openVideo(videoPath))
	{
		app.runVideo();
	}
}
