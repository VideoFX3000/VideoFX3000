// FERTIG

#ifndef VIDEORINGBUFFER_H
#define VIDEORINGBUFFER_H

#include <vector>
#include <opencv2/opencv.hpp>

// Die Klasse VideoRingBuffer dient dazu Frames in einen Vektor von Mat-Objekten einzulesen und diese
// anschließend verzögert auszulesen und wiederzugeben

// Die Buffergröße und die Delayzeit sind variable Werte, die vom Benutzer angepasst werden können

class VideoRingBuffer
{
public:
	VideoRingBuffer(void);
	~VideoRingBuffer(void);
	void setWriteIndex(void);
	// größe des Buffers anpassen
	void resizeBuffer(int size);
	// aktuelles Videoframe in den Buffer (Vektor) schreiben und Index erhöhen
	void writeBuffer(const cv::Mat& videoFrame);
	// verzögerte Frames aus dem Vektor auslesen
	cv::Mat readWithDelay(int delay);
private:
	// Vektor von Mat-Objekten (Buffer)
	std::vector<cv::Mat> buffer;
	// Zählvariable für den Index des Buffers
	int writeIndex;
	// Größe des Buffers
	int size;
};

#endif

