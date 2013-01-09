#include "VideoEngine.h"
using namespace cv;
using namespace std;

VideoEngine::VideoEngine(void)
	: frameWidth (0)
	, frameHeight(0)
	, input(0)
	, writerCheck(false)
	, delayTime(0)
	, bufferSize(2)
{ 
}

VideoEngine::~VideoEngine(void)
{
}

void VideoEngine::setEffect(Effect *effect){
	this->effect = effect;
}

bool VideoEngine::openVideo(const string& path){
	if (path == "0"){
		videoCapture.open(0);
	}
	else{
	videoCapture.open(path);
	}

	if (videoCapture.isOpened()){
		frameNumber = 0;
		frameWidth = videoCapture.get(CV_CAP_PROP_FRAME_WIDTH);
		frameHeight = videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT);
		frameRate = videoCapture.get(CV_CAP_PROP_FPS);

		namedWindow("Video");

		effect->initialize(frameWidth, frameHeight);

		return true;
	}
	else {
		return false;
	}
}

char VideoEngine::runVideo(){
	createTrackbar("Thresh", "Video", 0, 255);
	setTrackbarPos("Thresh", "Video", 20);
	input = '0';
	bool stopEffect = false;

	while(true && input != 'c' || stopEffect == false){
		Mat videoFrame (frameHeight, frameWidth, CV_8UC3);
		if (!videoCapture.read(videoFrame))
			break;
		frameNumber++;
		
		Mat processedFrame = effect->processFrame(videoFrame);
		showVideoFrame(processedFrame);

		if (kbhit()){
			input = getch();
		}
		if(input == 'r' || writerCheck == true)
			writeVideo(processedFrame);
		if(input == 's'){
			stopVideo(processedFrame);
		}

		loopInputCheck(input, delayTime);
		if (input == 'l'){
			delayTime = 0;
			writerCheck = false;
			input = 'q';
		}

		if(input == 'c'){
			stopEffect = true;
			videoCapture.release();
		}

		waitKey(30);
	}

	return input;
}
//schreibt aktuelle Videodatei
void VideoEngine::writeVideo(const Mat& videoFrame){
	if(!writerCheck){
		cout << "---writing" << endl;	
		//videoWriter.open("Video.avi", CV_FOURCC('D', 'I', 'V', 'X'), frameRate, Size(frameWidth, frameHeight), true);
		writerCheck = true;
	}
	//videoWriter.write(videoFrame);
	bufferLooper.resizeBuffer(bufferSize);
	bufferLooper.writeBuffer(videoFrame);
	bufferSize++;
	delayTime++;
}
//stoppt Videoschreiben
void VideoEngine::stopVideo(const Mat& videoFrame){	
	if (writerCheck){
		cout << "---stop" << endl;
		writerCheck = false;
	}
	//videoWriter.release();
}

void VideoEngine::loopInputCheck(int input, int delayTime){
	if(input == 'l')
		loopVideo(delayTime);

	//waitKey(30);
}

void VideoEngine::loopVideo(int delayTime){

	cout << "---looping" << endl;
	char abfrage = '0';
	//VideoCapture loopedVideo;
	//loopedVideo.open("Video.avi");
	//cout << loopedVideo.isOpened() << endl;

	while(abfrage != 'q'){
		bool looping = true;
		for (int i = 0; i < delayTime && looping == true; i++){
			Mat videoFrame (frameHeight, frameWidth, CV_8UC3);
			//if (loopedVideo.read(videoFrame) == false)
			//break;
			bufferLooper.readWithDelay(delayTime-i).copyTo(videoFrame);
			imshow("Video", videoFrame);
			if(kbhit()){
				abfrage = getch();
				if(abfrage == 'q')
					break;
			}
			waitKey(30);
		}

	}
}

void VideoEngine::showVideoFrame(const Mat&videoFrame){
	imshow("Video", videoFrame);
}

//Kann ggf. gelöscht werden
void VideoEngine::showProcessedFrame(const Mat&processedFrame){
	imshow("Result", processedFrame);

}