#include "VideoEngine.h"
using namespace cv;
using namespace std;

VideoEngine::VideoEngine(void)
	// Initialisierung der Member-Variablen
	: frameWidth (0)
	, frameHeight(0)
	, input('0')
	, delayTime(0)
	, bufferSize(2)
	, fileName ("0")
	, fileNameCounter('0')
	, writerCheck(false)
	, recorderCheck(false)
{ 
}

VideoEngine::~VideoEngine(void)
{
}

void VideoEngine::setEffect(Effect *effect){
	this->effect = effect;
}

// **************** Wiedergabefunktionen ********************
bool VideoEngine::openVideo(const string& path, string effectType){
	this->effectType = effectType;

	// Abfrage notwendig, da ansonsten die WebCam nicht gestartet wird weil path eine char-Variable ist
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

	while(stopThisEffect == false){
		Mat videoFrame (frameHeight, frameWidth, CV_8UC3);
		if (!videoCapture.read(videoFrame))
			break;
		frameNumber++;

		showVideoFrame(videoFrame);
		Mat processedFrame = effect->processFrame(videoFrame);

		// prüft, ob eine Taste gedrück wurde und weist den entsprechenden Buchstaben input zu
		if (kbhit()){
			input = getch();
		}
		if(input == 'w' || writerCheck == true)
			writeVideo(processedFrame);
		if(input == 's'){
			stopVideo(processedFrame);
		}

		input = loopInputCheck(input, delayTime);
		if (input == 'q'){
			delayTime = 0;
			writerCheck = false;
		}

		if(input == 'c' || input == 'e'){
			stopThisEffect = true;
			videoCapture.release();
		}

		waitKey(frameRate);
	}

	delayTime = 0;
	bufferSize = 2;
	fileName = "0";
	fileNameCounter = '0';
	// der writeIndex des Buffers muss zurückgesetzt werden
	bufferLoopedVideo.setWriteIndex();

	return input;
}

// ********** Grundlegende Verarbeitungsfunktionen **********
//schreibt Video in den Puffer
void VideoEngine::writeVideo(const Mat& videoFrame){
	if(!writerCheck){
		cout << "---writing" << endl;	
		writerCheck = true;
	}
	bufferLoopedVideo.resizeBuffer(bufferSize);
	bufferLoopedVideo.writeBuffer(videoFrame);
	bufferSize++;
	delayTime++;
}
//stoppt Schreiben des Videos in den Puffer
void VideoEngine::stopVideo(const Mat& videoFrame){	
	if (writerCheck){
		cout << "---stop" << endl;
		writerCheck = false;
	}
}

// ******************* Loop-Funktionen **********************
char VideoEngine::loopInputCheck(char input, int delayTime){
	if(input == 'l')
		input = loopVideo(delayTime);
	
	return input;
}

// loopt das Video, das sich im Puffer befindet
char VideoEngine::loopVideo(int delayTime){

	cout << "---looping" << endl;
	char keyRequest = '0';
	
	cout << "--------Speicher-Funktionen-------" << endl;
	cout << "'r': Dateiaufnahme starten: " << endl;
	cout << "'f': Dateiaufnahme beenden: " << endl;

	// solange nicht "q" (Videoloop beenden) oder "c" (Effekt beenden) gedrückt wird läuft diese Schleife
	while(keyRequest != 'q' && keyRequest != 'c'){
		// Diese Schleife läuft zusätzlich zu den Bedingungen im for, solange nicht "q" oder "c" gedrückt wird
		for (int i = 0; i < delayTime; i++){
			Mat videoFrame (frameHeight, frameWidth, CV_8UC3);
			
			bufferLoopedVideo.readWithDelay(delayTime-i).copyTo(videoFrame);

			imshow("Video", videoFrame);

			if(kbhit()){
				keyRequest = getch();
				if(keyRequest == 'q' || keyRequest == 'c'){
					if (recorderCheck == true){
						videoWriter.release();
						recorderCheck == false;
						if (fileNameCounter == '9')
							fileNameCounter = '1';						
					}
					break;
				}
			}

			if (keyRequest == 'r' && recorderCheck == false){
				fileName = effectType;
				fileNameCounter++;
				fileName += fileNameCounter;
				fileName += ".avi";
				videoWriter.open(fileName, videoCapture.get(CV_CAP_PROP_FOURCC), frameRate, Size(frameWidth, frameHeight), true/*"true" = Farbe*/);
				recorderCheck = true;
				cout << "\a"; // Piepton signalisiert dem Benutzer zusätzlich akustisch, dass das Video in eine Datei geschrieben wird
				cout << "Video " << fileNameCounter << " Dateiaufnahme gestartet" << endl;
			}

			if (recorderCheck == true){
				videoWriter.write(videoFrame);
				if (keyRequest == 'f'){
					videoWriter.release();
					recorderCheck = false;
					cout << "\a"; // erneuter Piepton signalisiert dem Benutzer zusätzlich akustisch, dass das Video in eine Datei gespeichert wurde
					cout << "Video " << fileNameCounter << " Dateiaufnahme beendet" << endl;
				}
			}
			waitKey(frameRate);
		}
	}
	return keyRequest;
}

void VideoEngine::showVideoFrame(const Mat&videoFrame){
	imshow("Video", videoFrame);
}