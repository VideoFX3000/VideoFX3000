#include "VideoEngine.h"
using namespace cv;
using namespace std;

VideoEngine::VideoEngine(void)
	: frameWidth (0)
	, frameHeight(0)
	, input(0)
	, writerCheck(false)
	, recorderCheck(false)
	, delayTime(0)
	, bufferSize(2)
	, loopRecordedVideoName ("0")
	, loopRecordedVideoNameCounter('0')
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
		if (path == "0"){
			frameRate = 60.; // muss momentan noch je System angepasst werden, da bei videoCapture.get(FPS) bei der WebCam 0 als Rückgabewert
		}
		else{
			frameRate = videoCapture.get(CV_CAP_PROP_FPS);
		}
		frameNumber = 0;
		frameWidth = videoCapture.get(CV_CAP_PROP_FRAME_WIDTH);
		frameHeight = videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT);
		//videoCodec = videoCapture.get(CV_CAP_PROP_FOURCC);

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
	bool stopThisEffect = false;

	while(true && input != 'c' || stopThisEffect == false){
		Mat videoFrame (frameHeight, frameWidth, CV_8UC3);
		if (!videoCapture.read(videoFrame))
			break;
		frameNumber++;

		Mat processedFrame = effect->processFrame(videoFrame);
		showVideoFrame(processedFrame);

		if (kbhit()){
			input = getch();
		}
		if(input == 'w' || writerCheck == true)
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
			stopThisEffect = true;
			videoCapture.release();
		}

		waitKey(frameRate);
	}

	return input;
}
//schreibt aktuelle Videodatei
void VideoEngine::writeVideo(const Mat& videoFrame){
	if(!writerCheck){
		cout << "---writing" << endl;	
		writerCheck = true;
	}
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
}

void VideoEngine::loopInputCheck(int input, int delayTime){
	if(input == 'l')
		loopVideo(delayTime);
}

void VideoEngine::loopVideo(int delayTime){

	cout << "---looping" << endl;
	char abfrage = '0';
	//VideoCapture loopedVideo;
	//loopedVideo.open("Video.avi");
	//cout << loopedVideo.isOpened() << endl;
	cout << "Video in Datei schreiben: r druecken" << endl;
	cout << "Video in Datei speichern: s druecken" << endl;

	while(abfrage != 'q' && abfrage != 'c'){
		for (int i = 0; i < delayTime; i++){
			string recordedVideoName;
			Mat videoFrame (frameHeight, frameWidth, CV_8UC3);
			//if (loopedVideo.read(videoFrame) == false)
			//break;
			bufferLooper.readWithDelay(delayTime-i).copyTo(videoFrame);

			imshow("Video", videoFrame);

			if(kbhit()){
				abfrage = getch();
				if(abfrage == 'q' || abfrage == 'c' || abfrage == 's'){
					if (recorderCheck == true){
						videoWriter.release();
						recorderCheck == false;
						if (loopRecordedVideoNameCounter == '9')
							loopRecordedVideoNameCounter = '1';						
					}
					break;
				}
			}

			if (abfrage == 'r' && recorderCheck == false){
				loopRecordedVideoName = "LoopedVideo";
				loopRecordedVideoNameCounter++;
				loopRecordedVideoName += loopRecordedVideoNameCounter;
				loopRecordedVideoName += ".avi";
				videoWriter.open(loopRecordedVideoName, videoCapture.get(CV_CAP_PROP_FOURCC), frameRate, Size(frameWidth, frameHeight), true/*"true" = Farbe*/);
				recorderCheck = true;
				cout << "\a"; // Piepton signalisiert dem Benutzer zusätzlich akustisch, dass das Video in eine Datei geschrieben wird
				cout << "Video " << loopRecordedVideoNameCounter << " wird in Datei geschrieben" << endl;
			}

			if (recorderCheck == true){
				videoWriter.write(videoFrame);
				if (abfrage == 's'){
					videoWriter.release();
					recorderCheck = false;
					cout << "\a"; // erneuter Piepton signalisiert dem Benutzer zusätzlich akustisch, dass das Video in eine Datei gespeichert wurde
					cout << "Video " << loopRecordedVideoNameCounter << " wurde gespeichert" << endl;
				}
			}
			waitKey(frameRate);
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