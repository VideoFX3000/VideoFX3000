#include "VideoEngine.h"
using namespace cv;
using namespace std;

int main()
{
	const string videoPath = "C:/Users/Public/Videos/Micro-dance_2_.AVI";
	//const string videoPath = "C:\\Users\\Public\\Videos\\Micro-dance.AVI";
	//const string videoPath = "C:/Users/Green/Videos/_FUSSBALL/Bayern/St. Pauli - Fc Bayern München (1-8) Highlights & Tore 07.05.2011.mp4";
	
	VideoEngine app;

	if (app.openVideo(videoPath,1))
	{
		app.runVideo();
	}
}
