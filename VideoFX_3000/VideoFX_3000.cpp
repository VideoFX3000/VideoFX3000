#include "VideoEngine.h"
using namespace cv;
using namespace std;

void looperAusgabe(){
	cout << "--------------------Loop-Funktionen--------------------" << endl << endl;
	cout << "'w': Video in Puffer schreiben" << endl;
	cout << "'s': Schreiben anhalten" << endl;
	cout << "'l': Puffer auslesen und gelooped wiedergeben" << endl;
	cout << "'q': Loopwiedergabe beenden" << endl;
	cout << "'c': Effekt abbrechen und zum Hauptmenue zurueckkehren" << endl;
	cout << "'e': Programm beenden"<< endl;
}

void headerAusgabe(){
	system("cls");
	cout << "********************* VideoFX_3000 ********************" << endl << endl;
}

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
		headerAusgabe();
		cout << "Herzlich Willkommen beim VideoFX 3000" << endl;
		cout << "Welchen Effekt waehlen Sie?" << endl << endl;
		cout << "Delay: '1 + Enter'" << endl;
		cout << "Ghost: '2 + Enter'" << endl;
		cout << "Looper: '3 + Enter'" << endl;
		cout << "Tarnkappe: '4 + Enter'" << endl;
		cout << "Hochpass: '5 + Enter'" << endl;
		cout << "Transparenz: '6 + Enter'" << endl;
		cout << "Programm beenden: 'e + Enter'" << endl;

		cin >> inputPrg;

		switch(inputPrg){
		case '1':	headerAusgabe();

			cout << "             *** D E L A Y E F F E K T ***" << endl << endl << endl;
			looperAusgabe();

			delay = new DelayEffect();
			app.setEffect(delay);
			if (app.openVideo(videoPath, "Delayeffekt"))
			{
				inputPrg = app.runVideo();
				destroyAllWindows();
				delete delay;
			}
			break;
		case '2':	headerAusgabe();
			cout << "             *** G H O S T E F F E K T ***" << endl << endl << endl;
			looperAusgabe();

			ghost = new GhostEffect();
			app.setEffect(ghost);
			if (app.openVideo(videoPath, "Ghosteffekt"))
			{
				inputPrg = app.runVideo();
				destroyAllWindows();
				delete ghost;
			}
			break;

		case '3':	headerAusgabe();
			cout << "             *** L O O P E R E F F E K T ***" << endl << endl << endl;
			looperAusgabe();

			loop = new LooperEffect();
			app.setEffect(loop);
			if (app.openVideo(camPath, "Loopereffekt"))
			{
				inputPrg = app.runVideo();
				destroyAllWindows();
				delete loop;
			}
			break;

		case '4':	headerAusgabe();
			cout << "       *** T A R N K A P P E N E F F E K T ***" << endl << endl << endl;
			looperAusgabe();

			magic = new MagicCapEffect();
			app.setEffect(magic);
			if (app.openVideo(camPath, "Tarnkappeneffekt"))
			{
				inputPrg = app.runVideo();
				destroyAllWindows();
				delete magic;
			}
			break;
		case '5':	headerAusgabe();
			cout << "          *** H O C H P A S S E F F E K T ***" << endl << endl << endl;
			looperAusgabe();

			high = new HighPassEffect();
			app.setEffect(high);
			if (app.openVideo(videoPath, "Hochpasseffekt"))
			{
				inputPrg = app.runVideo();
				destroyAllWindows();
				delete high;
			}
			break;
		case '6':	headerAusgabe();
			cout << "       *** T R A N S P A R E N Z E F F E K T ***" << endl << endl << endl;
			looperAusgabe();

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

		default:cout << "\a"; 
				cout << "Fehler: Ungueltige Eingabe!" << endl;
				cout << "Bitte Enter druecken" << endl;
				getchar();
				getchar();
				inputPrg ='c';
		}

		if (kbhit())
			inputPrg = getch();

	}while(inputPrg == 'c');

	system("cls");
	cout << endl << "VideoFX_3000 wird beendet." << endl << endl << endl;
	cout << "*       *  ********  *     *           *******    ******    ******    ******" << endl;
	cout << " *     *   *          *   *                   *  *      *  *      *  *      *" << endl;
	cout << "  *   *    *****        *                  ****  *      *  *      *  *      *" << endl;
	cout << "   * *     *          *   *                   *  *      *  *      *  *      *" << endl;
	cout << "    *      *         *     * ********  *******    ******    ******    ******" << endl << endl << endl << endl << endl<< endl << endl << endl << endl << endl;
	cout << "Auf Wiedersehen sagen Danny Kern und Ivonne Kubitza!" << endl;
	cout << "Bitte Enter druecken" << endl;
	getchar();
	getchar();
}


