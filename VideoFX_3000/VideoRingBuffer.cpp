#include "VideoRingBuffer.h"
using namespace cv;


VideoRingBuffer::VideoRingBuffer(void)
	// Initialisierung der Member-Variablen
	: size(0)
	, writeIndex(0)
	, readIndex(0)
{
}

VideoRingBuffer::~VideoRingBuffer(void)
{
}

// Allgemeine Verarbeitungsmethode, die die anderen Member-Funktionen aufruft und die gleichnamige
// abstrakte Methode in der Basisklasse ToolInterface überschreibt
// WIRD AKTUELL NICHT VERWENDET
Mat VideoRingBuffer::process(cv::Mat& input){
	resizeBuffer(100); //delay.bufferSize
	writeBuffer(input);
	input = readWithDelay(100); //delay.delaySize
	return input;
}

// größe des Buffers anpassen
void VideoRingBuffer::resizeBuffer(int size){
	this->size = size;
	buffer.resize(size);
}

// aktuelles Videoframe in den Buffer (Vektor) schreiben und Index erhöhen
void VideoRingBuffer::writeBuffer(cv::Mat& videoFrame){
	videoFrame.copyTo(buffer[writeIndex]);
	writeIndex++;
	if(writeIndex == size){
		writeIndex = 0;
	}
}

// verzögerte Frames aus dem Vektor auslesen
Mat VideoRingBuffer::readWithDelay(int delay){
	readIndex = writeIndex - delay;
	if( readIndex < 0){
		readIndex += size;
	}
	return buffer[readIndex];
}
