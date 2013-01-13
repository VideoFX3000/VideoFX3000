#include "VideoRingBuffer.h"
using namespace cv;


VideoRingBuffer::VideoRingBuffer(void)
	// Initialisierung der Member-Variablen
	: size(0)
	, writeIndex(0)
{
}

VideoRingBuffer::~VideoRingBuffer(void)
{
}

// writeIndex auf 0 setzen
void VideoRingBuffer::setWriteIndex(void){
	writeIndex = 0;
}

// gr��e des Buffers anpassen
void VideoRingBuffer::resizeBuffer(int size){
	this->size = size;
	buffer.resize(size);
}

// aktuelles Videoframe in den Buffer (Vektor) schreiben und Index erh�hen
void VideoRingBuffer::writeBuffer(const cv::Mat& videoFrame){
	videoFrame.copyTo(buffer[writeIndex]);
	writeIndex++;
	if(writeIndex == size){
		writeIndex = 0;
	}
}

// verz�gerte Frames aus dem Vektor auslesen
Mat VideoRingBuffer::readWithDelay(int delay){
	int readIndex = writeIndex - delay;
	if( readIndex < 0){
		readIndex += size;
	}
	return buffer[readIndex];
}
