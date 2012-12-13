#include "VideoEngine.h"
using namespace cv;
using namespace std;

VideoEngine::VideoEngine(void)
: frameWidth (0)
, frameHeight(0)
, input(0)
{
}

VideoEngine::~VideoEngine(void)
{
}
bool VideoEngine::openVideo(const std::string& path){
	videoCapture.open(path);
	if (videoCapture.isOpened()){
		frameNumber = 0;
		frameWidth = videoCapture.get(CV_CAP_PROP_FRAME_WIDTH);
		frameHeight = videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT);
		frameRate = videoCapture.get(CV_CAP_PROP_FPS);
		return true;
	}
	else {
		return false;
	}
}

void VideoEngine::runVideo(){

	createTrackbar("Thresh", "Video", 0, 255);
	setTrackbarPos("Thresh", "Video", 20);

	VideoWriter videoWriter;
	videoWriter.open("Video.avi", CV_FOURCC('D', 'I', 'V', 'X'), frameRate, Size(frameWidth, frameHeight), true);
	bool writerCheck = false;

	while(true){
		Mat videoFrame (frameHeight, frameWidth, CV_16UC3);
		if (videoCapture.read(videoFrame) == false){
			break;
		}
		frameNumber++;
		showVideoFrame(videoFrame);
		Mat processedFrame (frameHeight, frameWidth, CV_16UC1);
		processFrame(videoFrame, processedFrame);
		showProcessedFrame(processedFrame);
		
		if(kbhit()){
			input = getch();
		}
		if(input == 'r'){
			videoWriter.write(videoFrame);
			cout << "r" << endl;
		}
		waitKey(30);
	}
}

void VideoEngine::showVideoFrame(const Mat&videoFrame){
	
}
void VideoEngine::processFrame(const Mat&videoFrame, Mat& processedFrame){
	
}
void VideoEngine::showProcessedFrame(const Mat&processedFrame){
	
}