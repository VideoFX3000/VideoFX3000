#include "VideoEngine.h"
using namespace cv;
using namespace std;

int main()
{
	VideoEngine app;
	//Pfade für Videodatei und Webcam
	const string videoPath = "C:/Users/Public/Videos/Micro-dance_2_.AVI";
	const string camPath = "0";
	GhostEffect *ghost;
	DelayEffect *delay;
	LooperEffect *loop;
	MagicCapEffect *magic;

	//-----Konsolenausgabe
	char inputPrg;
	char inputReturn;

	//char inputSrc;

	do{
		system("cls");
		cout << "Herzlich Willkommen beim VideoFX 3000" << endl;
		cout << "Welchen Effekt?" << endl;
		cout << "Delay: '1 + Enter' druecken" << endl;
		cout << "Ghost: '2 + Enter' druecken" << endl;
		cout << "Looper: '3 + Enter' druecken" << endl;
		cout << "Tarnkappen: '4 + Enter' druecken" << endl;

		cin >> inputPrg;

		switch(inputPrg){
		case '1':	cout << "-----Delay" << endl;
			cout << "Effekt Abbrechen: 'c + Enter' druecken" << endl;

			delay = new DelayEffect();
			app.setEffect(delay);
			if (app.openVideo(videoPath))
			{
				app.runVideo();
				destroyAllWindows();
				delete delay;
			}
			break;
		case '2':	cout << "-----Ghost" << endl;
			cout << "Effekt Abbrechen: 'c + Enter' druecken" << endl;

			ghost = new GhostEffect();
			app.setEffect(ghost);
			if (app.openVideo(videoPath))
			{
				app.runVideo();
				destroyAllWindows();
				delete ghost;
			}
			break;

		case '3':	cout << "-----Loop" << endl;
			cout << "Aufzeichnen: 'r' drücken" << endl;
			cout << "Aufzeichnung stoppen: 's' drücken" << endl;
			cout << "Aufzeichnung loopen: 'l' drücken" << endl;
			cout << "Loopwiedergabe beenden: 'q' drücken" << endl;
			cout << "Effekt Abbrechen: 'c + Enter' druecken" << endl;

			loop = new LooperEffect();
			app.setEffect(loop);
			if (app.openVideo(videoPath))
			{
				app.runVideo();
				destroyAllWindows();
				delete loop;
			}
			break;

		case '4':	cout << "-----Tarnkappeneffekt" << endl;
			cout << "Effekt Abbrechen: 'c + Enter' druecken" << endl;

			magic = new MagicCapEffect();
			app.setEffect(magic);
			if (app.openVideo(videoPath))
			{
				inputReturn = app.runVideo();
				inputPrg = inputReturn;
				destroyAllWindows();
				delete magic;
			}
			break;

		default: cout << "Fehler: Ungueltige Eingabe!" << endl;
			break;
		}

		if (kbhit())
			inputPrg = getch();
		

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
