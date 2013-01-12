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
		case '1':	system("cls");
			cout << "********************* VideoFX_3000 ********************" << endl << endl;
			cout << "             *** D E L A Y E F F E K T ***" << endl << endl << endl;
			cout << "--------------------Loop-Funktionen--------------------" << endl << endl;
			cout << "Video in Puffer schreiben: 'w' druecken" << endl;
			cout << "Schreiben anhalten: 's' druecken" << endl;
			cout << "Puffer auslesen und gelooped wiedergeben: 'l' druecken" << endl;
			cout << "Loopwiedergabe beenden: 'q' druecken" << endl;
			cout << "Effekt abbrechen und zum Hauptmenue: 'c' druecken" << endl;

			delay = new DelayEffect();
			app.setEffect(delay);
			if (app.openVideo(videoPath, "Delayeffekt"))
			{
				inputPrg = app.runVideo();
				destroyAllWindows();
				delete delay;
			}
			break;
		case '2':	system("cls");
			cout << "-----Ghosteffekt" << endl;
			cout << "----------Loop-Funktionen----------" << endl;
			cout << "Video in Puffer schreiben: 'w' druecken" << endl;
			cout << "Schreiben anhalten: 's' druecken" << endl;
			cout << "Puffer auslesen und gelooped wiedergeben: 'l' druecken" << endl;
			cout << "Loopwiedergabe beenden: 'q' druecken" << endl;
			cout << "Effekt abbrechen und zum Hauptmenue: 'c' druecken" << endl;

			ghost = new GhostEffect();
			app.setEffect(ghost);
			if (app.openVideo(videoPath, "Ghosteffekt"))
			{
				inputPrg = app.runVideo();
				destroyAllWindows();
				delete ghost;
			}
			break;

		case '3':	system("cls");
			cout << "-----Loopeffekt" << endl;
			cout << "----------Loop-Funktionen----------" << endl;
			cout << "Video in Puffer schreiben: 'w' druecken" << endl;
			cout << "Schreiben anhalten: 's' druecken" << endl;
			cout << "Puffer auslesen und gelooped wiedergeben: 'l' druecken" << endl;
			cout << "Loopwiedergabe beenden: 'q' druecken" << endl;
			cout << "Effekt abbrechen und zum Hauptmenue: 'c' druecken" << endl;

			loop = new LooperEffect();
			app.setEffect(loop);
			if (app.openVideo(camPath, "Loopeffekt"))
			{
				inputPrg = app.runVideo();
				destroyAllWindows();
				delete loop;
			}
			break;

		case '4':	system("cls");
			cout << "-----Tarnkappeneffekt" << endl;
			cout << "----------Loop-Funktionen----------" << endl;
			cout << "Video in Puffer schreiben: 'w' druecken" << endl;
			cout << "Schreiben anhalten: 's' druecken" << endl;
			cout << "Puffer auslesen und gelooped wiedergeben: 'l' druecken" << endl;
			cout << "Loopwiedergabe beenden: 'q' druecken" << endl;
			cout << "Effekt abbrechen und zum Hauptmenue: 'c' druecken" << endl;

			magic = new MagicCapEffect();
			app.setEffect(magic);
			if (app.openVideo(camPath, "Tarnkappeneffekt"))
			{
				inputPrg = app.runVideo();
				destroyAllWindows();
				delete magic;
			}
			break;
		case '5':	system("cls");
			cout << "-----Hochpasseffekt" << endl;
			cout << "----------Loop-Funktionen----------" << endl;
			cout << "Video in Puffer schreiben: 'w' druecken" << endl;
			cout << "Schreiben anhalten: 's' druecken" << endl;
			cout << "Puffer auslesen und gelooped wiedergeben: 'l' druecken" << endl;
			cout << "Loopwiedergabe beenden: 'q' druecken" << endl;
			cout << "Effekt abbrechen und zum Hauptmenue: 'c' druecken" << endl;

			high = new HighPassEffect();
			app.setEffect(high);
			if (app.openVideo(videoPath, "Hochpasseffekt"))
			{
				inputPrg = app.runVideo();
				destroyAllWindows();
				delete high;
			}
			break;
		case '6':	system("cls");
			cout << "-----Transparenzeffekt" << endl;
			cout << "----------Loop-Funktionen----------" << endl;
			cout << "Video in Puffer schreiben: 'w' druecken" << endl;
			cout << "Schreiben anhalten: 's' druecken" << endl;
			cout << "Puffer auslesen und gelooped wiedergeben: 'l' druecken" << endl;
			cout << "Loopwiedergabe beenden: 'q' druecken" << endl;
			cout << "Effekt abbrechen und zum Hauptmenue: 'c' druecken" << endl;

			transparency = new TransparencyEffect();
			app.setEffect(transparency);
			if (app.openVideo(videoPath, "Transparenzeffekt"))
			{
				inputPrg = app.runVideo();
				destroyAllWindows();
				delete transparency;
			}
			break;
		case 'e': 
			break;

		default: cout << "Fehler: Ungueltige Eingabe!" << endl;
		}

		if (kbhit())
			inputPrg = getch();

	}while(inputPrg == 'c');

	system("cls");
	cout << endl << "VideoFX_3000 wird beendet. Auf Wiedersehen! (bitte 'ENTER' druecken)" << endl;
	getchar();
	getchar();
}
