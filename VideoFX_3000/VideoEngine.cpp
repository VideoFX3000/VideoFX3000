#include "VideoEngine.h"
using namespace cv;
using namespace std;

VideoEngine::VideoEngine(void)
	: frameWidth (0)
	, frameHeight(0)
	, input(0)
	, effectType(0)
	, writerCheck(false)
{ 
	namedWindow("Video");
}

VideoEngine::~VideoEngine(void)
{
}

bool VideoEngine::openVideo(const std::string& path, const int& effectType){
	videoCapture.open(path);
	this->effectType = effectType;
	if (videoCapture.isOpened()){
		frameNumber = 0;
		frameWidth = videoCapture.get(CV_CAP_PROP_FRAME_WIDTH);
		frameHeight = videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT);
		frameRate = videoCapture.get(CV_CAP_PROP_FPS);
		loop.initialize(frameWidth, frameHeight);
		delay.initialize(frameWidth, frameHeight);
		return true;
	}
	else {
		return false;
	}
}

void VideoEngine::runVideo(){

	createTrackbar("Thresh", "Video", 0, 255);
	setTrackbarPos("Thresh", "Video", 20);

	firstCall = true;
	

	while(true){
		Mat videoFrame (frameHeight, frameWidth, CV_8UC3);
		if (videoCapture.read(videoFrame) == false)
			break;

		frameNumber++;
		showVideoFrame(videoFrame);

		videoFrame = delay.processFrame(videoFrame);//HIER jeweiligen effect (loop/delay) einsetzen
		//HIER später evtl. Aufruf von process(videoFrame)
		
		if(kbhit())
			input = getch();
		if(input == 'r' || writerCheck == true)
			writeVideo(videoFrame);
		if(input == 's')
			stopVideo(videoFrame);
			
		loop.loopInputCheck(input);
		waitKey(30);
	}
}
//schreibt aktuellen Videodatei
void VideoEngine::writeVideo(const Mat& videoFrame){
	cout << "---writing" << endl;
	if(firstCall == true){
		videoWriter.open("Video.avi", CV_FOURCC('D', 'I', 'V', 'X'), frameRate, Size(frameWidth, frameHeight), true);
		cout << videoWriter.isOpened() << endl;//scheinbar kann das Video nicht mehr geschrieben werden
		firstCall = false;
	}
	videoWriter.write(videoFrame);
	writerCheck = true;
}
//stoppt Videoschreiben
void VideoEngine::stopVideo(const Mat& videoFrame){	
	cout << "---stop" << endl;
	writerCheck = false;
	videoWriter.release();
	firstCall = true;
}

void VideoEngine::showVideoFrame(const Mat&videoFrame){
	imshow("Video", videoFrame);
}

void VideoEngine::showProcessedFrame(const Mat&processedFrame){
	imshow("Result", processedFrame);

}