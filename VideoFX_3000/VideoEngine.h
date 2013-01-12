// FERTIG

#ifndef __VIDEOENGINE_H
#define __VIDEOENGINE_H

#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <conio.h> //für kbhit()
#include <stdlib.h>
// Basisklasse aller Effekte
#include "Effect.h"
// Klassen der Effekte
#include "LooperEffect.h"
#include "DelayEffect.h"
#include "MagicCapEffect.h"
#include "GhostEffect.h"
#include "HighPassEffect.h"
#include "TransparencyEffect.h"

// Die Klasse VideoEngine ist die grundlegende Klasse, die alle Effekte beinhaltet
// und die Videowiedergabe ausführt. In dieser Klasse werden die Videoschreib-
// funktionen sowie nach dem Loopen auch die Speicherung des gewünschten Videos
// durchgeführt. Diese Klasse wird von der Main-Funktion des gesamten Programms
// (innerhalb von VideoFX_3000.cpp) aufgerufen.

class VideoEngine
{
public:
	VideoEngine();
	virtual ~VideoEngine(void);
	void setEffect(Effect *effect);
	// **************** Wiedergabefunktionen ********************
	bool openVideo(const std::string& path, std::string effectType);
	char runVideo();
	// ********** Grundlegende Verarbeitungsfunktionen **********
	void writeVideo(const cv::Mat& videoFrame);
	void stopVideo(const cv::Mat& videoFrame);
	// ******************* Loop-Funktionen **********************
	char loopInputCheck(char input, int delayTime);
	char loopVideo(int delayTime);
	// ******************* Anzeige-Funktion *********************
	void showVideoFrame(const cv::Mat& videoFrame);
private:
	// Pointer für jeweiligen Effekt
	Effect *effect;
	cv::VideoCapture videoCapture;
	int frameWidth;
	int frameHeight;
	int frameNumber;
	float frameRate;
	std::string effectType;
	char input;
	// Länge (bezogen auf VideoRingBuffer soz. Delaydauer) des Loops
	int delayTime;
	int bufferSize;
	VideoRingBuffer bufferLoopedVideo;
	// Dateiname des jeweiligen Effekts, falls ein Video gespeichert wird
	std::string fileName;
	// Zählvariable für Dateinamen
	char fileNameCounter;
	int videoCodec;	
	cv::VideoWriter videoWriter;
	bool writerCheck;
	bool recorderCheck;
};

#endif