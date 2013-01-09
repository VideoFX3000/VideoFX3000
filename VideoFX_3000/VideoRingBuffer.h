#ifndef VIDEORINGBUFFER_H
#define VIDEORINGBUFFER_H

#include <vector>
#include <opencv2/opencv.hpp>

// Die Klasse VideoRingBuffer dient dazu Frames in einen Vektor von Mat-Objekten einzulesen und diese
// anschlie�end verz�gert auszulesen und wiederzugeben

// Im Moment werden f�r Buffergr��e und Delay feste Werte verwendet, dies muss noch angepasst werden
// da variable Werte, die vom Benutzer eingeben werden vorgesehen sind

class VideoRingBuffer
{
public:
	VideoRingBuffer(void);
	~VideoRingBuffer(void);
	// gr��e des Buffers anpassen
	void resizeBuffer(int size);
	// aktuelles Videoframe in den Buffer (Vektor) schreiben und Index erh�hen
	void writeBuffer(const cv::Mat& videoFrame);
	// verz�gerte Frames aus dem Vektor auslesen
	cv::Mat readWithDelay(int delay);
	// ggf. �bergabefunktion f�r die delaySize (falls das in der aktuellen Objektstruktur m�glich ist
	// void getInputParameters(int delaySize)
private:
	// Vektor von Mat-Objekten (Buffer)
	std::vector<cv::Mat> buffer;
	// Z�hlvariable f�r den Index des Buffers
	int writeIndex;
	int readIndex; // wird nur zu Testzwecken ben�tigt und kann im fertigen Programm entfernt werden
	// Gr��e des Buffers
	int size;
	//DelayEffect delay;// wird evtl. f�r �bergabe der delaySize ben�tigt (Evtl. ist die Definition einer Klasse nur zur �bergabe des Delays notwendig --> uebergabeklasse.delaySize)
};

#endif

