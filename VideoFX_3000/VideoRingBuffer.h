#ifndef VIDEORINGBUFFER_H
#define VIDEORINGBUFFER_H

#include <vector>
#include <opencv2/opencv.hpp>

// Die Klasse VideoRingBuffer dient dazu Frames in einen Vektor von Mat-Objekten einzulesen und diese
// anschließend verzögert auszulesen und wiederzugeben

// Im Moment werden für Buffergröße und Delay feste Werte verwendet, dies muss noch angepasst werden
// da variable Werte, die vom Benutzer eingeben werden vorgesehen sind

class VideoRingBuffer
{
public:
	VideoRingBuffer(void);
	~VideoRingBuffer(void);
	// größe des Buffers anpassen
	void resizeBuffer(int size);
	// aktuelles Videoframe in den Buffer (Vektor) schreiben und Index erhöhen
	void writeBuffer(const cv::Mat& videoFrame);
	// verzögerte Frames aus dem Vektor auslesen
	cv::Mat readWithDelay(int delay);
	// ggf. Übergabefunktion für die delaySize (falls das in der aktuellen Objektstruktur möglich ist
	// void getInputParameters(int delaySize)
private:
	// Vektor von Mat-Objekten (Buffer)
	std::vector<cv::Mat> buffer;
	// Zählvariable für den Index des Buffers
	int writeIndex;
	int readIndex; // wird nur zu Testzwecken benötigt und kann im fertigen Programm entfernt werden
	// Größe des Buffers
	int size;
	//DelayEffect delay;// wird evtl. für Übergabe der delaySize benötigt (Evtl. ist die Definition einer Klasse nur zur Übergabe des Delays notwendig --> uebergabeklasse.delaySize)
};

#endif

