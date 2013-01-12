// FERTIG

#ifndef VIDEORINGBUFFER_H
#define VIDEORINGBUFFER_H

#include <vector>
#include <opencv2/opencv.hpp>

// Die Klasse VideoRingBuffer dient dazu Frames in einen Vektor von Mat-Objekten einzulesen und diese
// anschlie�end verz�gert auszulesen und wiederzugeben

// Die Buffergr��e und die Delayzeit sind variable Werte, die vom Benutzer angepasst werden k�nnen

class VideoRingBuffer
{
public:
	VideoRingBuffer(void);
	~VideoRingBuffer(void);
	void setWriteIndex(void);
	// gr��e des Buffers anpassen
	void resizeBuffer(int size);
	// aktuelles Videoframe in den Buffer (Vektor) schreiben und Index erh�hen
	void writeBuffer(const cv::Mat& videoFrame);
	// verz�gerte Frames aus dem Vektor auslesen
	cv::Mat readWithDelay(int delay);
private:
	// Vektor von Mat-Objekten (Buffer)
	std::vector<cv::Mat> buffer;
	// Z�hlvariable f�r den Index des Buffers
	int writeIndex;
	// Gr��e des Buffers
	int size;
};

#endif

