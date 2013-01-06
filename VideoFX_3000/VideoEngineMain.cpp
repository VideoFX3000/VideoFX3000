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
	//char inputSrc;

	do{
		system("cls");
		cout << "Herzlich Willkommen beim VideoFX 3000" << endl;
		cout << "Welchen Effekt?" << endl;
		cout << "Delay: '1 + Enter' druecken" << endl;
		cout << "Looper: '2 + Enter' druecken" << endl;
		cout << "Tarnkappeneffekt: '3 + Enter' druecken" << endl;

		cin >> inputPrg;

		switch(inputPrg){
		case '1':	cout << "-----Delay" << endl;
					cout << "Korregieren: 'c + Enter' druecken" << endl;
					if (app.openVideo(videoPath,'1'))
					{
						app.runVideo();
						destroyAllWindows();
					}
			break;

		case '2':	cout << "-----Loop" << endl;
					cout << "Korregieren: 'c + Enter' druecken" << endl;

					if (app.openVideo(videoPath,'2'))
					{
						app.runVideo();
						destroyAllWindows();
					}
			break;

		case '3':	cout << "-----Tarnkappeneffekt" << endl;
					cout << "Korregieren: 'c + Enter' druecken" << endl;

					if (app.openVideo(videoPath,'3'))
					{
						app.runVideo();
						destroyAllWindows();
					}
			break;

		default: cout << "Fehler: Ungueltige Eingabe!" << endl;
			break;
		}

		cin >> inputPrg;

	}while(inputPrg == 'c');

	waitKey(0);

	//ALTER STAND
	/*
	const string videoPath = "C:/Users/Public/Videos/Micro-dance_2_.AVI";
	//const string videoPath = "C:\\Users\\Public\\Videos\\Micro-dance.AVI";

	VideoEngine app;

	if (app.openVideo(videoPath,'2'))
	{
	app.runVideo();
	}
	*/}
