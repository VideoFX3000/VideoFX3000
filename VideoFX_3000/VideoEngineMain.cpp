#include "VideoEngine.h"
using namespace cv;
using namespace std;

int main()
{
	VideoEngine app;
	//Pfade f�r Videodatei und Webcam
	const string videoPath = "C:/Users/Public/Videos/Micro-dance_2_.AVI";
	const string camPath = "0";
	GhostEffect *ghost;
	DelayEffect *delay;
	LooperEffect *loop;
	MagicCapEffect *magic;
	HighPassEffect *high;
	TransparencyEffect *transparency;

	//-----Konsolenausgabe
	char inputPrg;

	do{
		system("cls");
		cout << "Herzlich Willkommen beim VideoFX 3000" << endl;
		cout << "Welchen Effekt?" << endl;
		cout << "Delay: '1 + Enter' druecken" << endl;
		cout << "Ghost: '2 + Enter' druecken" << endl;
		cout << "Looper: '3 + Enter' druecken" << endl;
		cout << "Tarnkappe: '4 + Enter' druecken" << endl;
		cout << "Hochpass: '5 + Enter' druecken" << endl;
		cout << "Transparenz: '6 + Enter' druecken" << endl;

		cin >> inputPrg;

		switch(inputPrg){
		case '1':	cout << "-----Delay" << endl;
			cout << "Effekt abbrechen und zum Hauptmenue: 'c' druecken" << endl;

			delay = new DelayEffect();
			app.setEffect(delay);
			if (app.openVideo(videoPath))
			{
				inputPrg = app.runVideo();
				destroyAllWindows();
				delete delay;
			}
			break;
		case '2':	cout << "-----Ghost" << endl;
			cout << "Effekt abbrechen und zum Hauptmenue: 'c' druecken" << endl;

			ghost = new GhostEffect();
			app.setEffect(ghost);
			if (app.openVideo(videoPath))
			{
				inputPrg = app.runVideo();
				destroyAllWindows();
				delete ghost;
			}
			break;

		case '3':	cout << "-----Loop" << endl;
			cout << "Aufzeichnen: 'r' druecken" << endl;
			cout << "Aufzeichnung stoppen: 's' druecken" << endl;
			cout << "Aufzeichnung loopen: 'l' druecken" << endl;
			cout << "Loopwiedergabe beenden: 'q' druecken" << endl;
			cout << "Effekt abbrechen und zum Hauptmenue: 'c' druecken" << endl;

			loop = new LooperEffect();
			app.setEffect(loop);
			if (app.openVideo(camPath))
			{
				inputPrg = app.runVideo();
				destroyAllWindows();
				delete loop;
			}
			break;

		case '4':	cout << "-----Tarnkappeneffekt" << endl;
			cout << "Effekt abbrechen und zum Hauptmenue: 'c' druecken" << endl;

			magic = new MagicCapEffect();
			app.setEffect(magic);
			if (app.openVideo(camPath))
			{
				inputPrg = app.runVideo();
				destroyAllWindows();
				delete magic;
			}
			break;
		case '5':	cout << "-----Hochpass" << endl;
			cout << "Effekt abbrechen und zum Hauptmenue: 'c' druecken" << endl;

			high = new HighPassEffect();
			app.setEffect(high);
			if (app.openVideo(videoPath))
			{
				inputPrg = app.runVideo();
				destroyAllWindows();
			}
			break;
		case '6':	cout << "-----Transparenzeffekt" << endl;
			cout << "Effekt abbrechen und zum Hauptmenue: 'c' druecken" << endl;

			transparency = new TransparencyEffect();
			app.setEffect(transparency);
			if (app.openVideo(videoPath))
			{
				inputPrg = app.runVideo();
				destroyAllWindows();
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
