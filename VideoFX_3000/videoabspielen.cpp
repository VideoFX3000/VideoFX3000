#include <opencv2/opencv.hpp>
using namespace cv;

int main(){
	namedWindow("Video");
	VideoCapture videoCapture;
	videoCapture.open("C:/Users/Public/Videos/Micro-dance.AVI");	
	int width = videoCapture.get(CV_CAP_PROP_FRAME_WIDTH);
	int height = videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT);
	int frameRate = videoCapture.get(CV_CAP_PROP_FPS);

	//>>>>>>>>>> VideoWriter Objekt initialisieren
	VideoWriter videoWriter;
	//>>>>>>>>>> VideoWriter Datei öffnen
	videoWriter.open("Video.avi", CV_FOURCC('D', 'I', 'V', 'X'), frameRate, Size(width, height), true);

	while(true){
		Mat videoFrame;
		if (false == videoCapture.read(videoFrame)){
			break;
		}
		//>>>>>>>>>> VideoWriter Frame schreiben
		videoWriter.write(videoFrame);
		
		imshow("Video", videoFrame);
		waitKey(30);
	}
}

		

