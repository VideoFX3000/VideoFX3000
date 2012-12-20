#include "VideoEngine.h"
using namespace cv;
using namespace std;

VideoEngine::VideoEngine(void)
	: frameWidth (0)
	, frameHeight(0)
	, input(0)
	, effectType(0)
	, writerCheck(false)
	//Buffer-Variablen
	, size(0)
	, writeIndex(0)
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

		loop.processFrame(videoFrame);//HIER WEITER
		//HIER aufruf von process(videoFrame)

/*		Mat processedFrame (frameHeight, frameWidth, CV_8UC1);
		showProcessedFrame(processedFrame);
*/		

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

//-------------------------Ring Buffer
//schreibt aktuelles Videoframe in den Buffer; erhöht den Index
void VideoEngine::write(const cv::Mat& videoFrame){
	buffer[writeIndex] = videoFrame;
	writeIndex++;
	if(writeIndex == size){
		writeIndex = 0;
	}
}
//liest Videoframe verzögert aus Buffer
Mat VideoEngine::readWithDelay(int delay){
	int readIndex = writeIndex - delay;
	if( readIndex < 0){
		readIndex += size;
	}
	return buffer[readIndex];
}
//Verändert die Größe des Buffers
void VideoEngine::resize(int size){
	this->size = size;
	buffer.resize(size);
}