#include "VideoEngine.h"
using namespace cv;
using namespace std;

int main()
{
	const string videoPath = "C:/Users/Public/Videos/Micro-dance_2_.AVI";
	//const string videoPath = "C:\\Users\\Public\\Videos\\Micro-dance.AVI";
	
	VideoEngine app;

	if (app.openVideo(videoPath,1))
	{
		app.runVideo();
	}
}
