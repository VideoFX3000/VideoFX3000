#include "VideoEngine.h"
using namespace cv;
using namespace std;

int main()
{
	VideoEngine app;
	//Pfade für Videodatei und Webcam
	const string videoPath = "C:/Users/Public/Videos/Micro-dance_2_.AVI";
	const string camPath = "0";

	//-----Konsolenausgabe
	char inputPrg;
	char inputSrc;

	do{
		system("cls");
		cout << "Herzlich Willkommen beim VideoFX 3000" << endl;
		cout << "Welchen Effekt?" << endl;
		cout << "Delay: '1 + Enter' druecken" << endl;
		cout << "Looper: '2 + Enter' druecken" << endl;

		cin >> inputPrg;
		switch(inputPrg){
		case '1': cout << "-----Delay" << endl;
			cout << "Welche Quelle?" << endl;
			cout << "Videodatei: '1 + Enter'" << endl;
			cout << "Webcam: '2 + Enter'" << endl;
			cout << "Korregieren: 'c + Enter' druecken" << endl;

			cin >> inputSrc;
			switch(inputSrc){
			case '1': cout << "-----Delay und Videodatei" << endl;
				if (app.openVideo(videoPath,1))
				{
					app.runVideo();
				}
				break;
			case '2': cout << "-----Delay und Webcam" << endl;
				if (app.openVideo(camPath,2))
				{
					app.runVideo();
				}
				break;
			}
			break;
		case '2': cout << "-----Loop" << endl;
			cout << "Welche Quelle?" << endl;
			cout << "Videodatei: '1 + Enter'" << endl;
			cout << "Webcam: '2 + Enter'" << endl;
			cout << "Korregieren: 'c + Enter' druecken" << endl;
			cin >> inputSrc;
			switch(inputSrc){
			case '1': cout << "-----Loop und Videodatei" << endl;
				if (app.openVideo(videoPath,2))
				{
					app.runVideo();
				}
				break;
			case '2': cout << "-----Loop und Webcam" << endl;
				if (app.openVideo(camPath,2))
				{
					app.runVideo();
				}
				break;
			}
			break;
		default: cout << "Fehler: Ungültige Eingabe!" << endl;
			break;
		}
	}while(inputSrc == 'c');

	waitKey();

	//ALTER STAND
	/*
	const string videoPath = "C:/Users/Public/Videos/Micro-dance_2_.AVI";
	//const string videoPath = "C:\\Users\\Public\\Videos\\Micro-dance.AVI";

	VideoEngine app;

	if (app.openVideo(videoPath,1))
	{
	app.runVideo();
	}
	*/
}
