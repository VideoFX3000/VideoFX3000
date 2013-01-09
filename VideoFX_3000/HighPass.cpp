#include "HighPass.h"

using namespace cv;


HighPass::HighPass(void)
	// Initialisierung der Member-Variablen
{
}


HighPass::~HighPass(void)
{
}

Mat HighPass::process(cv::Mat& input){
	Mat src, src_gray;
	Mat grad;
	char* window_name = "Sobel Demo - Simple Edge Detector";

	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	int c;

	while(true){
		Mat processedFrame;
		Mat processedFrame_gray;
		//Bild verwischen
		GaussianBlur( input, processedFrame, Size(3,3), 0, 0, BORDER_DEFAULT );
		// Graustufenbild erzeugen
		cvtColor( processedFrame, processedFrame_gray, CV_RGB2GRAY );
		// benötigte Mat-Obj erzeugen
		Mat grad_x, grad_y;
		Mat abs_grad_x, abs_grad_y;

		/// Gradient X ausrechnen
		Sobel( processedFrame_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
		convertScaleAbs( grad_x, abs_grad_x );

		/// Gradient Y ausrechnen
		Sobel( processedFrame_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
		convertScaleAbs( grad_y, abs_grad_y );

		/// Beide Gradienten zusammenführen
		addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );

		//Mat grad_bunt;
		//cvtColor( grad, grad_bunt, CV_GRAY2RGB);
		//imshow( window_name, grad_bunt );

		waitKey(30);
		return grad;
	}
}