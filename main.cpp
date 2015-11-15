#include <QApplication>
#include <QDesktopWidget>

#include "window.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QPixmap pixmap("splscr.png");
	QSplashScreen *splash = new QSplashScreen(pixmap);


	splash->show();
	splash->showMessage("version 22");


	Window window;
	//window.resize(window.sizeHint());
	//int desktopArea = QApplication::desktop()->width() *
	//QApplication::desktop()->height();
	/*int widgetArea = window.width() * window.height();

	if (((float)widgetArea / (float)desktopArea) < 0.750f)
		window.show();
	else
		//window.showMaximized();
		window.show();*/

	window.show();
	return app.exec();
}
