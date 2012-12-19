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
	videoCapture.open(0);
	this->effectType = effectType;
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

	firstCall = true;

	while(true){
		Mat videoFrame (frameHeight, frameWidth, CV_8UC3);
		if (videoCapture.read(videoFrame) == false)
			break;

		frameNumber++;
		showVideoFrame(videoFrame);
		
/*		Mat processedFrame (frameHeight, frameWidth, CV_8UC1);
		processFrame(videoFrame, processedFrame);
		showProcessedFrame(processedFrame);
*/
		if(kbhit())
			input = getch();
		if(input == 'r' || writerCheck == true)
			writeVideo(videoFrame);
		if(input == 's')
			stopVideo(videoFrame);
		if(input == 'l')
			loopVideo();
		waitKey(30);
	}
}
//schreibt aktuellen Videodatei
void VideoEngine::writeVideo(const Mat& videoFrame){
	cout << "---writing" << endl;
	if(firstCall == true){
		videoWriter.open("Video.avi", CV_FOURCC('D', 'I', 'V', 'X'), frameRate, Size(frameWidth, frameHeight), true);
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
void VideoEngine::loopVideo(){
	cout << "---looping" << endl;
	char abfrage = '0';
	VideoCapture loopedVideo;
	loopedVideo.open("Video.avi");
	do{
		if(kbhit()){
			abfrage = getch();
			input = abfrage;
		}
		Mat videoFrame (frameHeight, frameWidth, CV_8UC3);
		if (loopedVideo.read(videoFrame) == false)
			break;
		showVideoFrame(videoFrame);
		waitKey(30);
	}while(abfrage != 'q');
}
void VideoEngine::showVideoFrame(const Mat&videoFrame){
	//imshow("Video", videoFrame);
}
void VideoEngine::processFrame(const Mat&videoFrame, Mat& processedFrame){

}
void VideoEngine::showProcessedFrame(const Mat&processedFrame){

}
//-------------------------Ring Buffer
//schreibt aktuelles Videoframe in den Buffer; erh�ht den Index
void VideoEngine::write(const cv::Mat& videoFrame){
	buffer[writeIndex] = videoFrame;
	writeIndex++;
	if(writeIndex == size){
		writeIndex = 0;
	}
}
//liest Videoframe verz�gert aus Buffer
Mat VideoEngine::readWithDelay(int delay){
	int readIndex = writeIndex - delay;
	if( readIndex < 0){
		readIndex += size;
	}
	return buffer[readIndex];
}
//Ver�ndert die Gr��e des Buffers
void VideoEngine::resize(int size){
	this->size = size;
	buffer.resize(size);
}